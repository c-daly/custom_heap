#include "heap/pm_heap.h"
#include "linkedlist/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // init pm_heap
  // pm_malloc (a few different times)
  // pm_free
  void* tempPtr1;
  void* tempPtr2;
  void* tempPtr3;
  void* tempPtr4;
  void* tempPtr5;
  printf("Starting with %d bytes available for allocation\n", NALLOC);
  printf("Allocate 8\n");
  tempPtr1 = pm_malloc(8);
  print_free_list();
  printf("Allocate 8\n");
  tempPtr2 = pm_malloc(8);
  print_free_list();
  printf("Allocate 8\n");
  tempPtr3 = pm_malloc(8);
  printf("Allocate 8\n");
  tempPtr4 = pm_malloc(8);
  printf("Free ptr2\n");
  pm_free(tempPtr2);
  printf("Free 8\n");
  pm_free(tempPtr3);
  printf("Allocate 8\n");
  tempPtr2 = pm_malloc(8);
  printf("Free ptr4\n");
  pm_free(tempPtr4);
  printf("Free ptr1\n");
  pm_free(tempPtr1);
  printf("Allocate 100\n");
  tempPtr1 = pm_malloc(100);
  printf("Allocate 100\n");
  tempPtr1 = pm_malloc(100);
  printf("Allocate 100\n");
  tempPtr1 = pm_malloc(100);
  printf("Allocate 100\n");
  tempPtr1 = pm_malloc(100);
  printf("Allocate 100\n");
  tempPtr1 = pm_malloc(100);
  printf("Allocate 100\n");
  tempPtr1 = pm_malloc(100);
  print_free_list();
  printf("Free ptr1\n");
  pm_free(tempPtr1);
  print_free_list();
  return 0;
}
