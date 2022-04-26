#include "queue.hpp"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <tbb/mutex.h>
#include "memory.hpp"

tbb::mutex qLock;

Node *getnode(char *data) {
    pnode newNode = (pnode) my_malloc(sizeof(node));
    bzero(newNode->data, 1024);
    strcpy(newNode->data, data);
    return newNode;
}

void initQ(pqueue *q) {
    *q = (pqueue) my_malloc(sizeof(queue));
    (*q)->rear = (*q)->front = NULL;
    (*q)->size = 0;
}


int isEmpty(pqueue q) {
    return (q->front == NULL);
}

int size(pqueue q) {
    return q->size;
}

char *topRear(pqueue q) {
    qLock.lock();
    if (!isEmpty(q)) {
        qLock.unlock();
        return q->rear->data;
    }
    char *errorMsg = (char *) my_malloc(13 * sizeof(char));
    strcpy(errorMsg, "ERROR: Empty!");
    qLock.unlock();
    return errorMsg;
}

void enqueue(pqueue q, char *data) {
    qLock.lock();
    pnode newNode = getnode(data);
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
//        q->front->next = NULL;
//        q->rear->next = NULL;
    } else {
        newNode->prev = q->rear;
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
    qLock.unlock();
}

void dequeue(pqueue q) {
    qLock.lock();
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
    } else {
        if (q->rear == NULL) {
            q->front = NULL;
        } else {
            q->rear = q->rear->prev;
        }
        q->size--;
    }
    qLock.unlock();
}

