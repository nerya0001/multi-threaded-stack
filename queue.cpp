#include "queue.hpp"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>


Node *getnode(char *data) {
    pnode newNode = (pnode) malloc(sizeof(node));
    bzero(newNode->data, 1024);
    strcpy(newNode->data, data);
    return newNode;
}

void initQ(pqueue q) {
    q->rear = q->front = NULL;
    q->size = 0;
}


int isEmpty(pqueue q) {
    return (q->front == NULL);
}

int size(pqueue q) {
    return q->size;
}

void Enqueue(pqueue q, pnode *head, char *data) {
    pnode newNode = getnode(data);
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        q->front->next = NULL;
        q->rear->next = NULL;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

void Dequeue(pqueue q) {
    if (isEmpty()) {
        printf("UnderFlow\n");
    } else {
        if (q->rear == NULL) {
            q->front = NULL;
        } else {
            q->rear->next = NULL;
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
