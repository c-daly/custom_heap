#include "heap/pm_heap.h"
#include "linkedlist/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // init pm_heap
  // pm_malloc (a few different times)
  // pm_free
  void* tempPtr;
  void* tempPtr2;
  tempPtr = pm_malloc(16);
  tempPtr = pm_malloc(16);
  tempPtr = pm_malloc(16);
  pm_free(tempPtr);
  tempPtr2 = pm_malloc(16);
  pm_free(tempPtr2);
  return 0;
}
