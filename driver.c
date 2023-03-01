#include "linkedlist/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "heap/pm_heap.h"

typedef struct thread_params_t {
  int size;
} thread_params_t;

void* allocateAndFreePointer(void* data) {
  
  void* tempPtr1;
  void* tempPtr2;
  void* tempPtr3;

  thread_params_t* params = (thread_params_t*) data;

  tempPtr1 = pm_malloc(params->size);
  printf("tempPtr1: %p\n", tempPtr1);
  tempPtr2 = pm_malloc(params->size);
  printf("tempPtr2: %p\n", tempPtr2);
  pm_free(tempPtr1);
  pm_free(tempPtr2);
  tempPtr3 = pm_malloc(params->size);
  printf("tempPtr3: %p\n", tempPtr3);
  pm_free(tempPtr3);
  return data;
}

void singleThreadedTest() {
  void* tempPtr1;
  void* tempPtr2;
  void* tempPtr3;

  tempPtr1 = pm_malloc(32);
  pm_free(tempPtr1);
  tempPtr3 = pm_malloc(32);
  tempPtr2 = pm_malloc(32);
  pm_free(tempPtr2);
  printf("tempPtr1: %p\n", tempPtr1);
}

void multiThreadedTest() {
  thread_params_t params;
  params.size = 16;
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;
  pthread_create(&thread1, NULL, allocateAndFreePointer, &params);
  pthread_create(&thread2, NULL, allocateAndFreePointer, &params);
  pthread_create(&thread3, NULL, allocateAndFreePointer, &params);
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
 
}

/*
 * Potential test cases:
 * check free_list is the correct size after successive frees, using qsize
 */
int main() {
  multiThreadedTest();
  print_free_list();
  
  return 0;
}
