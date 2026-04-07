#include "../include/ring_buffer.h"
#include <stddef.h>
void Ring_Buffer_init(Ring_Buffer_t* q){
    q -> head = 0;
    q -> tail = 0;
    q -> count =0;
}

uint8_t isBufferFull(Ring_Buffer_t* q){
    return q -> count == QUEUE_SIZE;
}

uint8_t isBufferEmpty(Ring_Buffer_t* q){
    return q -> count == 0;
}
uint8_t writeBuffer(Ring_Buffer_t* q, uint8_t* data){
    if(q -> count == QUEUE_SIZE) return 0;
    q -> buffer[q -> head] = *data;
    q -> head = (q->head + 1) % QUEUE_SIZE;
    q -> count ++;
    return 1;
}

uint8_t readBuffer(Ring_Buffer_t* q ,uint8_t* data){
    if(q-> count == 0) return 0;
    *data = q -> buffer[q->tail];
    q -> tail = (q->tail + 1) % QUEUE_SIZE;
    q -> count --;
    return 1;
}
