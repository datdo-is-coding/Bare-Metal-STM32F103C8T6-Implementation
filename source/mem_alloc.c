#include "../include/mem_alloc.h"
#include "sysmem.c"

volatile void* heap_start = NULL;

// CHUNK SIZE is 12 bytes
// size 4 bytes
// free 1 byte
// next 4 bytes
void* malloc(size_t size){
    size = ALIGN(size);
    if(heap_start == NULL){
        malloc_chunk* new = (malloc_chunk*)sbrk(CHUNK_SIZE + size);
        if(new == (void*)-1) return NULL;
        heap_start = new;
        new -> size = size;
        new -> free = 0;
        new -> next = NULL;
        return new+1;
    }
    malloc_chunk* current = heap_start;
    malloc_chunk* best = NULL;
    while(current != NULL){
        if(current -> free && current ->size >= size){
            if(best == NULL || current -> size < best -> size){
                best = current;
            }
        }
        if(current -> next == NULL) break;
        current = current -> next;
    }
    if(best == NULL){
        malloc_chunk* new = (malloc_chunk*)sbrk(CHUNK_SIZE + size);
        if(new == (void*)-1) return NULL;
        current -> next  = new;
        new -> size =  size;
        new -> free = 0;
        new -> next = NULL;
        return new+1;
    }
    else{
        if(best -> size >= CHUNK_SIZE +size + 4){
            malloc_chunk* new = (malloc_chunk*)((char*)(best+1)+size);
            new -> next = best -> next;
            best -> next = new;
            new -> size = best -> size - CHUNK_SIZE -size;
            best -> size = size;
            
        }
        best -> free = 0;
        return best+1;  
    }
}


void free(void* ptr){
    if(ptr == NULL) return;
    malloc_chunk* block = (malloc_chunk*) ptr - 1;
    block -> free = 1;
    malloc_chunk* current = heap_start;
    while(current != NULL && current -> next != NULL){
        if(current -> free && current -> next -> free){
            current -> size += CHUNK_SIZE + current -> next -> size;
            current -> next = current -> next -> next;
        }
        else{
            current =  current -> next;
        }
        
    }
}
