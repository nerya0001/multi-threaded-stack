#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "util.hpp"

stack* head = NULL;

int main()
{
    char buffer[BUF_SIZE] = {0}; // buffer for the input
    int check; // var to check the there was actualy input

    // printPrompt();
    check = scanf("%[^\n]%*c", buffer); 
    
    // if nothing was received we need to flush the stdin, so we don't enter an infinite loop
    if (check == 0) {
        while ( getchar() != '\n' );
        // printPrompt();
    }
        
    while (strcmp(buffer, "EXIT")) {
        char str[1024];
        bzero(str, 1024);
        
        // if nothing was received we need to flush the stdin, so we don't enter an infinite loop
        if (check == 0) {
            while ( getchar() != '\n' );
            // printPrompt();
        }

        else if (strncmp(buffer, "PUSH", 4) == 0) {
            for (int i = 5, j = 0; i < strlen(buffer); i++, j++)
            {
                str[j] = buffer[i];
            }
            push(str, &head);
            // printPrompt();
        }
        else if (strncmp(buffer, "POP", 3) == 0) {
            pop(&head);
            // printPrompt();
        }
        else if (strncmp(buffer, "TOP", 3) == 0) {
            peek(&head);
            // printPrompt();
        } 
        else if (strncmp(buffer, "PRINT", 5) == 0) {  
            displayStack(&head); 
            // printPrompt();
        }
        
        bzero(buffer, BUF_SIZE);
        check = scanf("%[^\n]%*c", buffer);  
    }

    return 0;
}
