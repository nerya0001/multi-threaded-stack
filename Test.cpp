#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.hpp"
#include "queue.hpp"
#include "memory.hpp"
#include <pthread.h>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;
stack *head = NULL;

pthread_t pid;

TEST_CASE("Good")
{
//    SUBCASE("1")
//    {
//        char word[10] = "hello";
//        push(word, &head);
//        CHECK(strcmp(word, peek(&head))==0);
//    }
    SUBCASE("2") {
        char word[5] = "nana";
        push(word,&head);
//        sleep(2);
        if (pthread_create(&pid, NULL, &popTest,&head) != 0) {
            printf("Failed to create thread\n");
        }
        void* nana;
        pthread_join(pid,&nana);

//        char secondWord[5] = "gaga";
//        push(secondWord,&head);
//        printf("%s", peek(&head));
//        CHECK(!strcmp("ERROR: Stack is empty!", peek(&head)));
        CHECK_EQ(false,(bool)nana);
    }



}
