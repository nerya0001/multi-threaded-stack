#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "util.hpp"


char* parbuff[1024];

void print_parsed() {
    int i = 0;
    while (parbuff[i] != NULL) {
        printf("%s ", parbuff[i]);
        i++;
    }
    printf("\n");
}

void Parse(char* buffer) {
    // char* parbuff[1024];
    char* pbuff;
    int i = 0;
    pbuff = strtok(buffer, " ");
    while (pbuff != NULL) {
        parbuff[i++] = pbuff;
        pbuff = strtok(NULL, " ");
    }
    // print_parsed();
    // return parbuff;
}

void push(char* str, p_stack* head) {
    // printf("str: %s\n", str);
    // Parse(str);
    // char** parsed = parbuff;
    stack* n = (stack*)malloc(sizeof(stack)); 
    // n->str = str + 5;
    n->str = str;
    // bzero(n->str,1024);
    // strcpy(n->str, str);
    n->next = *head;
    *head = n;
    for (int i = 0; i < strlen(str); i++)
    {
        printf("%c",str[i]);
    }
}

void pop(p_stack* head) {
    if (head == NULL) {
        printf("%sStack is empty!\n\n", RED);
        printf("%s", NORMAL); 
    } else {
        stack* temp = *head;
        *head = (*head)->next;
        printf("%s%sdeleted successfully\n\n", temp->str, GREEN);
        printf("%s", NORMAL); 
        free(temp);
    }
}

void peek(p_stack* head) {
    if (head == NULL) {
        printf("%sStack is empty!\n\n", RED);
        printf("%s", NORMAL); 
    } else {
        printf("head->str: %s\n", (*head)->str);
        
        // char* temp;
        // strcpy(temp, head->str);
        // printf("%s\n", temp);
    }
}


void displayStack(p_stack* head) {
    stack* temp = *head;
    if (head == NULL) {
        printf("\n%sStack is empty!\n\n", RED);
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


void printPrompt() {
    printf("%senter command: ", GREEN);
    printf("%s", NORMAL);  
}


// int sysReplacement(char* buffer) {
    
//     // parse the input by " "
//     char** parsed = parse(buffer);
 
//     // fork a child process
//     int pid = fork();
    
//     if (pid < 0) {

//         // error  
//         return 1;
        
//     } else if (pid == 0) {

//         execvp(parsed[0], parsed); 

//     } else {

//         /* parent process */
//         /* parent will wait for the child to complete */
//         wait(NULL);
//     }
//     return 0;
// }

