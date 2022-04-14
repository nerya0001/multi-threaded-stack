#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "util.hpp"
#include <tbb/mutex.h>


char afterParsing[1024]; // parsed input

// three locks - one for each function
tbb::mutex pushLock;
tbb::mutex popLock;
tbb::mutex peekLock;

/**
 * @brief print parsed input
 * 
 */
// void print_parsed() {
//     int i = 0;
//     while (afterParsing[i] != NULL) {
//         printf("%s ", afterParsing[i]);
//         i++;
//     }
//     printf("\n");
// }

/**
 * @brief parse input into strings array
 * 
 * @param buffer 
 */
// void Parse(char* buffer) {
//     char* parbuff[1024];
//     char* pbuff;
//     int k = 0;
//     pbuff = strtok(buffer, " ");
//     while (pbuff != NULL) {
//         parbuff[k++] = pbuff;
//         pbuff = strtok(NULL, " ");
//     }
//     for (size_t i = 1; i < k; i++)
//     {
//         for (uint j = 0; j < strlen(parbuff[i]); j++)
//             {
//                 afterParsing[j] = parbuff[i][j];
//             }
//     }
// }

/**
 * @brief push newly allocated element into the stack
 * 
 * @param str 
 * @param head 
 */
void push(char* str, p_stack* head) {

    pushLock.lock();
  
    // Parse(str);

    stack* n = (stack*)malloc(sizeof(stack)); 

    bzero(n->str,1024);
    // strcpy(n->str, afterParsing);
    strcpy(n->str, str);
    n->next = *head;
    *head = n;

    pushLock.unlock();
}

/**
 * @brief pop the top element from the stack, and free the memory
 * 
 * @param head 
 */
void pop(p_stack* head) {

    popLock.lock();

    if (*head == NULL) {
        printf("%sERROR: Stack is empty!\n", RED);
        printf("%s", NORMAL); 
    } else {
        stack* temp = *head;
        *head = (*head)->next;
        printf("%s%s has Poped successfully\n\n", temp->str, GREEN);
        printf("%s", NORMAL); 
        free(temp);
    }

    popLock.unlock();
}

/**
 * @brief peek on the top element in the stack
 * 
 * @param head 
 */
void peek(p_stack* head) {

    peekLock.lock();

    if (*head == NULL) {
        printf("%sERROR: Stack is empty!\n\n", RED);
        printf("%s", NORMAL); 
    } else {
        printf("OUTPUT: ");
        for (uint i = 0; i < strlen((*head)->str); i++) {
            printf("%c", (*head)->str[i]);
        }
        printf("\n");
    }

    peekLock.unlock();
}

/**
 * @brief print stack content
 * 
 * @param head 
 */
void displayStack(p_stack* head) {
    stack* temp = *head;

    if (*head == NULL) {
        printf("\n%sERROR: Stack is empty!\n", RED);
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
    
}

/**
 * @brief maybe a prompt function
 * 
 */
void printPrompt() {
    printf("%senter command: ", GREEN);
    printf("%s", NORMAL);  
}
