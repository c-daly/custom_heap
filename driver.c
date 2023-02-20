#include "heap/pm_heap.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // init pm_heap
  // pm_malloc (a few different times)
  // pm_free
  void* res = pm_malloc(8);
  res = "AAAAAAAAAA";
  printf("%s",(char*)res);
  printf("%ld", sizeof(res));
  return 0;
}
