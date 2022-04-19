#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <tbb/mutex.h>

#ifndef MULTI_THREADED_LOCK_FREE_STACK_MEMORY_HPP
#define MULTI_THREADED_LOCK_FREE_STACK_MEMORY_HPP


// my malloc implementation
void *my_malloc(size_t size);

// my free implementation
void my_free(void *ptr);

//my calloc implementation
void *my_calloc(size_t nmemb, size_t size);

#endif //MULTI_THREADED_LOCK_FREE_STACK_MEMORY_HPP
