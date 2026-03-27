#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H
#include <stdint.h>
#include <stddef.h>

typedef struct malloc_chunk{
    size_t size;
    char free;
    struct malloc_chunk* next;
}malloc_chunk ;

#define ALIGN(size) (((size) + 3) & ~3) 
#define CHUNK_SIZE sizeof(malloc_chunk)

void* malloc(size_t size);
 
#endif
