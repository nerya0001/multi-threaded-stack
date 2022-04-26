#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstddef>

#ifndef MULTI_THREADED_LOCK_FREE_STACK_QUEUE_HPP
#define MULTI_THREADED_LOCK_FREE_STACK_QUEUE_HPP

typedef struct Node {
    char data[1024];
    Node *next, *prev;
} *pnode, node;

typedef struct Queue {
    Node *front;
    Node *rear;
    int size;
} *pqueue, queue;

void initQ(pqueue *q);

char *topRear(pqueue q);

void enqueue(pqueue q, char *data); // insert to tail (same as PUSH)

void dequeue(pqueue q);// delete from tail (same as POP)

int isEmpty();

int size();

#endif //MULTI_THREADED_LOCK_FREE_STACK_QUEUE_HPP
