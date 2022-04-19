#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <tbb/mutex.h>

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