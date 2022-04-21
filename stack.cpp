#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "stack.hpp"
#include <tbb/mutex.h>
#include "memory.hpp"


char afterParsing[1024]; // parsed input

tbb::mutex stackMutex;

/**
 * @brief push newly allocated element into the stack
 * 
 * @param str 
 * @param head 
 */


void push(char *str, p_stack *head) {
    stackMutex.lock();
    // Parse(str);
    stack *n = (stack *) my_malloc(sizeof(stack));
    bzero(n->str, 1024);
    // strcpy(n->str, afterParsing);
    strcpy(n->str, str);
    n->next = *head;
    *head = n;
    printf("%s%s has pushed successfully\n", n->str, GREEN);
    printf("%s", NORMAL);
    stackMutex.unlock();
}


/**
 * @brief pop the top element from the stack, and free the memory
 * 
 * @param head 
 */
void pop(p_stack *head) {
    stackMutex.lock();
    sleep(1);
    if (*head == NULL) {
        printf("%sERROR: Stack is empty!\n", RED);
        printf("%s", NORMAL);
    } else {
        stack *temp = *head;
        *head = (*head)->next;
        printf("%s%s has Poped successfully\n", temp->str, GREEN);
        printf("%s", NORMAL);
        my_free(temp);
    }
    stackMutex.unlock();
}

/**
 * @brief peek on the top element in the stack
 * 
 * @param head 
 */
char *peek(p_stack *head) {
    stackMutex.lock();
    if (*head == NULL) {
        char *errorMsg = (char *) my_malloc(24 * sizeof(char));
        strcpy(errorMsg, "ERROR: Stack is empty!");
        printf("%s ERROR: Stack is empty!\n", RED);
        printf("%s", NORMAL);
        stackMutex.unlock();
        return errorMsg;
    } else {
        printf("%s%s Top has successfully sent to client\n", (*head)->str, GREEN);
        printf("%s", NORMAL);
        char *ans = (char *) my_malloc(sizeof((*head)->str));
        strcpy(ans, (*head)->str);
        stackMutex.unlock();
        return ans;
    }
}

/**
 * @brief print stack content
 * 
 * @param head 
 */
void displayStack(p_stack *head) {

    stackMutex.lock();

    stack *temp = *head;

    if (*head == NULL) {
        printf("%sERROR: Stack is empty!\n", RED);
        printf("%s", NORMAL);
    } else {
        printf("%s ", temp->str);
        temp = temp->next;
        while (temp != NULL) {
            printf("-> ");
            printf("%s ", temp->str);
            temp = temp->next;
        }
        printf("\n");
    }

    stackMutex.unlock();
}


/**
 * functions for testing
 * @param head
 * @return
 */

void *popTest(void *head) {
    p_stack newHead = *(p_stack *) head;
    stackMutex.lock();
    bool isUnlocked = stackMutex.try_lock();
    if (newHead == NULL) {
        printf("%sERROR: Stack is empty!\n", RED);
        printf("%s", NORMAL);
    } else {
        stack *temp = newHead;
        newHead = (newHead)->next;
        printf("%s%s has Poped successfully\n", temp->str, GREEN);
        printf("%s", NORMAL);
        my_free(temp);
    }
    sleep(2);
    stackMutex.unlock();
    return (void *) isUnlocked;
}

void *testLock(void *head) {
    return (void *) stackMutex.try_lock();
}

void *testLockSleep(void *head) {
    sleep(5);
    return (void *) stackMutex.try_lock();
}

