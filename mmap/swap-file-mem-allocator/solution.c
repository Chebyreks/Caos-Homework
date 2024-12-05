#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>
#include <sys/stat.h>
#include <sys/mman.h>

int size_swap_file;
static struct chunkheader* start;

struct chunkheader {
    int size;
    int free; // 0 - свободна
    struct chunkheader* next;
};

void myalloc_initialize(int fd) {
    struct stat st;
    fstat(fd, &st);
    int size_swap_file = st.st_size;
    start = mmap(NULL, size_swap_file, PROT_WRITE, MAP_PRIVATE, fd, 0);
    start = (struct chunkheader*)start;
    start->size = size_swap_file - sizeof(struct chunkheader);
    start->free = 0;
    start->next = NULL;
}

void myalloc_finalize() {
    munmap(start, size_swap_file);
    start = NULL;
}

void* my_malloc(size_t size) {
    struct chunkheader* cur = start; 
    while(1) {
        if (cur != NULL) {
            if (cur->free == 0 && cur->size >= size) {

                int left = cur->size - size - sizeof(struct chunkheader);
                cur->free = 1;
                if (left >= sizeof(struct chunkheader)) {
                    struct chunkheader* new = (struct chunkheader*)((char*)cur + size + sizeof(struct chunkheader));
                    new->free = 0;
                    new->size = left;
                    new->next = cur->next;
                    cur->next = new;
                    cur->size = size;
                }
                return (void*)((char*)cur + sizeof(struct chunkheader));
            }
            cur = cur->next;
        }
        return NULL;
    }
}

void my_free(void *ptr) {
    struct chunkheader* ptr_chunk = (struct chunkheader*)((char*)ptr - sizeof(struct chunkheader));
    ptr_chunk->free = 0;
    struct chunkheader* ptr_= start;
    while (ptr_ != NULL) {
        if (ptr_->free == 0 && ptr_->next != NULL && ptr_->next->free == 0) {
            ptr_->size += sizeof(struct chunkheader) + ptr_->next->size;
            ptr_->next = ptr_->next->next;
        }
        ptr_ = ptr_->next;
    }
}
