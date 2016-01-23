#include<stdlib.h>
#include "sparsestringarray.h"

static void CountEmptyPrintNonEmpty(int index, const char *str, void *auxData) {
  if (strcmp(str, "") != 0) {
    printf("Oooo! Nonempty string at index %d: \"%s\"\n", index, str);
  } else {
    (*(int *)auxData)++;
  } }
int main(int argc, char **argv) {
  sparsestringarray ssa; SparseStringArrayNew(&ssa, 70000, 35);
  SparseStringArrayInsert(&ssa, 33001, "need"); SparseStringArrayInsert(&ssa, 58291, "more"); SparseStringArrayInsert(&ssa, 33000, "Eye"); SparseStringArrayInsert(&ssa, 33000, "I"); SparseStringArrayInsert(&ssa, 67899, "cowbell");
  int numEmptyStrings = 0;
  SparseStringArrayMap(&ssa, CountEmptyPrintNonEmpty, &numEmptyStrings); printf("%d of the strings were empty strings.\n", numEmptyStrings);
  SparseStringArrayDispose(&ssa);
  return 0; }
