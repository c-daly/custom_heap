/*
 * queue.h / Process Queue
 * Christopher Daly / CS5600 / Northeastern University
 * Spring 2023 / Jan 25
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

/* Foundational element for the queue 
   structure. */
typedef struct node_t {
  void* data;
  struct node_t* next;
  struct node_t* prev;
} node_t;

/* The data element for the process_t priority
   queue */
typedef struct process_t {
  int identifier, priority;
  char* name;
} process_t;

/* see queue.c for documentation */
node_t* add_node_to_tail(node_t* list, node_t* new_node);
node_t* enqueue(node_t* list, void* element);
void* delist(node_t* list);
process_t* dequeueProcess(node_t* list);
int qsize(node_t* list);
node_t* getNextPriorityElement(node_t* list);
node_t* getLastElement(node_t* list);
node_t* getFirstElement(node_t* list);
void freeQueue(node_t* list);
#endif
