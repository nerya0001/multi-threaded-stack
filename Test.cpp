#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.hpp"
#include "queue.hpp"
#include "memory.hpp"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;
stack *head = NULL;

TEST_CASE("Good")
{
    SUBCASE("1")
    {
        char word[10] = "hello";
        push(word, &head); 
       
        CHECK(strcmp(word, peek(&head))==0);
    }


}
