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


/**
 * Note: Please wait at least 7 seconds for the test to finish.
 */
TEST_CASE ("Good")
{

    stack *head = NULL;
    pthread_t pid;
    pthread_t pid2;
    pthread_t pid3;

    /**
    * Trivial Test Case
    */
            SUBCASE("1") {
        char word[10] = "hello";
        push(word, &head);
                CHECK(strcmp(word, peek(&head)) == 0);
    }

    /**
     * Non Trivial Test Case
     * In this sub test case we try to lock twice with the mutex function (stackMutex.try_lock())
     * therefore we should get false if the mutex did lock in the first time
     */
            SUBCASE("Mutex lock test case") {
        char word[5] = "nana";
        push(word, &head); // pushing a random word
        void *isUnlocked = popTest(&head); // popping the word
                CHECK_EQ(false, (bool) isUnlocked);
    }
    /**
     * Non Trivial Test Case
     * In this sub case we try to lock twice with the mutex function (stackMutex.try_lock())
     * But this time we test the mutex on different functions with different threads.
     * This test demonstrates multi threading with different functions.
     * Because each client has its own thread and uses different functions.
     */
            SUBCASE("Mutex lock test case for multiple functions") {
        char word[5] = "nana";
        push(word, &head);// pushing a random word

        // Opens a thread for popTest functions which uses mutex.lock and has a time sleep for 2 seconds.
        if (pthread_create(&pid, NULL, &popTest, &head) != 0) {
            printf("Failed to create thread\n");
        }

        // Opens a thread for testLock function which tries to lock while the mutex is already locked.
        // Should return false.
        if (pthread_create(&pid2, NULL, &testLock, &head) != 0) {
            printf("Failed to create thread\n");
        }

        // Opens a thread for the testLockSleep function which sleeps for 5 seconds and then tries to lock
        // We should succeed locking because we wait 5 seconds for the popTest function to unlock.
        // Should return true.
        if (pthread_create(&pid3, NULL, &testLockSleep, &head) != 0) {
            printf("Failed to create thread\n");
        }
        void *isUnlocked;
        void *isUnlockedSleep;
        pthread_join(pid, NULL);
        pthread_join(pid2, &isUnlocked);
        pthread_join(pid3, &isUnlockedSleep);
                CHECK_EQ(false, (bool) isUnlocked);
                CHECK_EQ(true, (bool) isUnlockedSleep);
    }


}
