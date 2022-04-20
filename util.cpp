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

// locks - one for each function
tbb::mutex pushLock;
tbb::mutex popLock;
tbb::mutex peekLock;
tbb::mutex printLock;

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
void push(char *str, p_stack *head) {

    pushLock.lock();
    // Parse(str);
    stack *n = (stack *) my_malloc(sizeof(stack));
    bzero(n->str, 1024);
    // strcpy(n->str, afterParsing);
    strcpy(n->str, str);
    n->next = *head;
    *head = n;
    printf("%s%s has pushed successfully\n", n->str, GREEN);
    printf("%s", NORMAL);
    pushLock.unlock();
}

/**
 * @brief pop the top element from the stack, and free the memory
 * 
 * @param head 
 */
void pop(p_stack *head) {

    popLock.lock();

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
    popLock.unlock();
}

/**
 * @brief peek on the top element in the stack
 * 
 * @param head 
 */
const char *peek(p_stack *head) {
    peekLock.lock();
    if (*head == NULL) {
        char *errorMsg = (char *) malloc(24 * sizeof(char));
        strcpy(errorMsg, "ERROR: Stack is empty!");
        printf("%s ERROR: Stack is empty!\n", RED);
        printf("%s", NORMAL);
        peekLock.unlock();
        return errorMsg;
    } else {
        printf("%s%s Top has successfully sent to client\n", (*head)->str, GREEN);
        printf("%s", NORMAL);
        peekLock.unlock();
        return (*head)->str;
    }
}

/**
 * @brief print stack content
 * 
 * @param head 
 */
void displayStack(p_stack *head) {

    printLock.lock();

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

    printLock.unlock();

}

/**
 * @brief maybe a prompt function
 * 
 */
void printPrompt() {
    printf("%senter command: ", GREEN);
    printf("%s", NORMAL);
}


typedef struct free_block {
    size_t size;
    struct free_block *next;
} free_block;

static free_block free_block_list_head = {0, 0};

// static const size_t overhead = sizeof(size_t);

static const size_t align_to = 16;

void *my_malloc(size_t size) {
    size = (size + sizeof(free_block) + (align_to - 1)) & ~(align_to - 1);
    free_block *block = free_block_list_head.next;
    free_block **head = &(free_block_list_head.next);
    while (block != 0) {
        if (block->size >= size) {
            *head = block->next;
            return ((char *) block) + sizeof(free_block);
        }
        head = &(block->next);
        block = block->next;
    }

    block = (free_block *) sbrk(size);
    block->size = size;

    return ((char *) block) + sizeof(free_block);
}

void my_free(void *ptr) {
    free_block *block = (free_block *) (((char *) ptr) - sizeof(free_block));
    block->next = free_block_list_head.next;
    free_block_list_head.next = block;
}

//untested
void *my_calloc(size_t nmemb, size_t size) {
    char *p;
    if (nmemb == 0 || size == 0) {
        return nullptr;
    } else {
        p = static_cast<char *>(my_malloc(nmemb * size));
        bzero(p, nmemb * size);
        return p;
    }
}
