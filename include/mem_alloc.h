#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H
#include <stdint.h>

typedef struct {
    size_t size;
    struct malloc_chunk* next;
}malloc_chunk ;

#define CHUNK_SIZE sizeof(malloc_chunk)
void* malloc(size_t size);
void free(void* ptr);
#endif