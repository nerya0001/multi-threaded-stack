#include "queue.hpp"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "memory.hpp"


Node *getnode(char *data) {
    pnode newNode = (pnode) my_malloc(sizeof(node));
    bzero(newNode->data, 1024);
    strcpy(newNode->data, data);
    return newNode;
}

void initQ(pqueue *q) {
    *q = (pqueue) malloc(sizeof(queue));
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
    if (!isEmpty(q)) {
        return q->rear->data;
    }
    char *errorMsg = (char *) my_malloc(24 * sizeof(char));
    strcpy(errorMsg, "ERROR: Empty!");
    return errorMsg;
}

void enqueue(pqueue q, char *data) {
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
}

void dequeue(pqueue q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        if (q->rear == NULL) {
            q->front = NULL;
        } else {
            Node *temp = q->rear;
            q->rear = q->rear->prev;
            q->rear->next= NULL;
//            free(temp);
        }
        q->size--;
    }
}

void erase(pqueue q) {
    q->rear = NULL;
    while (q->front != NULL) {
        pnode temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->size = 0;
}
