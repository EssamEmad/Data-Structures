#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn)
{
  h->elemSize = elemSize;
  h->numBuckets = numBuckets;
  h->buckets = malloc(sizeof(vector) * numBuckets);
  h->compareFunc = comparefn;
  h->freeFunc = freefn;
  h->hashFunc = hashfn;
  //now initalize everysingle bucket
  for(int i = 0; i < numBuckets; i++){
    VectorNew(&h->buckets[i],elemSize,freefn,1);
  }
}

void HashSetDispose(hashset *h)
{
  for(int i = 0; i < h->numBuckets; i++){
    vector *v = &h->buckets[i];
    VectorDispose(v);
  }
}

int HashSetCount(const hashset *h)
{ return h->numBuckets; }

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData)
{
  for(int i = 0; i < h->numBuckets; i++){
    vector *v = &h->buckets[i];
    for(int j = 0; j < VectorLength(v); j++)
      mapfn(VectorNth(v,j),auxData);
  }
}

void HashSetEnter(hashset *h, const void *elemAddr)
{
  int index = h->hashFunc(elemAddr,h->numBuckets);
  vector *v = &h->buckets[index];
  for(int i = 0; i < VectorLength(v); i++){
    void * elem = VectorNth(v,i);
    if(h->compareFunc(elem,elemAddr) == 0){
      VectorReplace(v,elemAddr,i);
      return;
    }
  }
  VectorAppend(v,elemAddr);
}

void *HashSetLookup(const hashset *h, const void *elemAddr)
{ 
  int elemAddress = h->hashFunc(elemAddr, h->numBuckets);
  vector elems = h->buckets[elemAddress];
  int length = VectorLength(&elems);
  if(length == 0)
    return NULL;
  for(int i = 0; i < length; i++){
    void * element = VectorNth(&elems,i);
    if(h->compareFunc(element, elemAddr)== 0)
       return element;
  }
    return NULL;
 }
