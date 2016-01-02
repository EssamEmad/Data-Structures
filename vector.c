#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
  v->elemSize = elemSize;
  v->count = 0;
  v->capacity = initialAllocation;
  v->elems = malloc(elemSize * 4);
  assert(v->elems != NULL);
  v->freeFunc = freeFn;
}

void VectorDispose(vector *v)
{
  if(v->freeFunc != NULL){
    for(int i = 0; i < v->count; i++){
      char *element = (char*) v->elems + i*v->elemSize;
      v->freeFunc(element);
    }
  }
  free(v);
}

int VectorLength(const vector *v)
{ return v->count; }

void *VectorNth(const vector *v, int position)
{
  // assert(position < 0 || position > v->count);
  void * element = (char*) v->elems + position * v->elemSize;
  assert(element != NULL);
  return element;
 }

void VectorReplace(vector *v, const void *elemAddr, int position)
{
  void  * element = (char*) v->elems + position * v->elemSize;
  assert(element != NULL);
  memcpy(element, elemAddr, v->elemSize);
}

void VectorInsert(vector *v, const void *elemAddr, int position)
{
  //we first check if there is a space to add an element
  if(v->count == v->capacity)
    expand(v);
  void * moveFrom = (char *) v->elems + position * v->elemSize;
  void *moveTo = (char*) moveFrom + v->elemSize;
  int size = (v->count - position) * v->elemSize;
  memmove(moveTo, moveFrom, size);
  memcpy(moveFrom, elemAddr, v->elemSize);
  int *from = (int*) moveFrom;
  int *to = (int*) moveTo;
  v->count++;
}

void VectorAppend(vector *v, const void *elemAddr)
{
  if(v->count == v->capacity)
    expand(v);
  void *end = (char*) v->elems + v->count * v->elemSize;
  memcpy(end,elemAddr, v->elemSize);
  v->count++;
}

void VectorDelete(vector *v, int position)
{
  assert(position > 0 && position < v->count);
  void *indexToDelete = (char*) v-> elems + v->elemSize * position;
  void *elementAfter = (char*) indexToDelete + v->elemSize;
  int sizeToBeMoved = v->count - position - 1;
  sizeToBeMoved *= v->elemSize;
  memmove(indexToDelete,elementAfter,sizeToBeMoved);
  v->count--;
}

void VectorSort(vector *v, VectorCompareFunction compare)
{
  assert(compare != NULL);
  qsort(v->elems, v->count, v->elemSize, compare);
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData)
{
  assert(mapFn != NULL);
  for(int i = 0; i < v->count; i++){
    void * elem = (char*) v->elems + i*v->elemSize;
    mapFn(elem,auxData);
  }
}
void expand(vector *v){
  v->capacity += 4;
  v->elems = realloc(v->elems, (v->capacity) * v->elemSize);
  assert(v->elems != NULL);
}
static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted)
{
  assert(startIndex>=0 && startIndex < v->count && searchFn != NULL);
  void *base = (char*) v-> elems + startIndex * v->elemSize;
  //perform a binary search using c function bsearch if the data is sorted
  if(isSorted){
   void *found =  bsearch(key, base,v->count - startIndex, v->elemSize, searchFn);
   if(found == NULL)
     return -1;
   else{
     int diff =  found - v->elems;
     return diff/ v->elemSize;
   }
  } else{
    //if not sorted
    for(int i = startIndex; i < v->count; i++){
      base = (char*) v->elems + i * v->elemSize;
      if(searchFn(base, key) == 0)
	return i;
    }

 return -1;
  }

 } 
