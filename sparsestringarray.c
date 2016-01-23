#include "sparsestringarray.h"

void vectorFreeFunc(void * elem){
  free(elem);
}
void SSANew(sparsestringarray *ssa, int arrayLength, int groupSize){
  ssa->arrayLength = arrayLength;
  ssa->groupSize = groupSize;
  int numberOfGroups = arrayLength/groupSize;
  ssa->numGroups  = numberOfGroups;
  group *groups = malloc(sizeof(group)* numberOfGroups);
  ssa->groups = groups;
  for(int i = 0; i < numberOfGroups; i++){
    group currentGroup = ssa->groups[i];
    currentGroup.bitmap = malloc(sizeof(bool));
    VectorNew(&currentGroup.strings, sizeof(char *), vectorFreeFunc, 0);
  }
}


void SSADispose(sparsestringarray *ssa){
  //for each group
  for(int i = 0; i < ssa->numGroups; i++){
    group currentGroup = ssa->groups[i];
    free(currentGroup.bitmap);
    VectorDispose(&currentGroup.strings);
  }
  free(ssa);
}

bool SSAInsert(sparsestringarray *ssa, int index, const char *str){
  int groupIndex = index / ssa->groupSize;
  group stringGroup = ssa->groups[groupIndex];
  int indexInGroup = index / ssa->numGroups;
  int vectorIndex = 0;
  //calculate the vectorIndex
  for(int i = 0; i < indexInGroup; i++)
    if(stringGroup.bitmap[i])
      vectorIndex++;
  bool * stringBool = &stringGroup.bitmap[indexInGroup];
  if( *stringBool){
  VectorInsert(&stringGroup.strings, str, vectorIndex);
  *stringBool = true;
  return true;
  }  else {
    VectorReplace(&stringGroup.strings,str,indexInGroup);
    return false;
  }
}
void SSAMap(sparsestringarray *ssa, SSAMapFunction mapfn, void *auxData){
  // loop on each group
  for(int i = 0; i < ssa->numGroups; i++){
    group currentGroup = ssa->groups[i];
    for(int j = 0; j < ssa->groupSize; j++){
      int index = j * ssa->numGroups;
      if(currentGroup.bitmap[j]){
	mapfn(index,"",auxData);
      } else {
	int vectorindex = getvectorindex(currentGroup.bitmap, j);
	mapfn(index,VectorNth(&currentGroup.strings, vectorindex), auxData);
	      
      }
    }     
  }
  }
int getvectorindex(bool * bitmap, int stopIndex){
  int index = 0;
  for(int i = 0; i < stopIndex; i ++)
    if(bitmap[i])
      index++;
  return index;
}
    
