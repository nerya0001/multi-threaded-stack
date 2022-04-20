#ifndef _UTIL_H_
#define _UTIL_H_

#define NORMAL  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"

#define BUF_SIZE 1024


typedef struct stack {
    char str[1024];
    struct stack *next;
} stack, *p_stack;


// push
void push(char *str, p_stack *head);


// pop the top element from the stack
void pop(p_stack *head);

void *popTest(void *head);

bool testLock();

// peek but not pop
char *peek(p_stack *head);

// display stack
void displayStack(p_stack *head);

#endif