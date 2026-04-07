#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

#define QUEUE_SIZE 20



typedef struct{
    uint8_t buffer[QUEUE_SIZE];
    int head;
    int tail;
}Ring_Buffer_t;

void Ring_Buffer_init(Ring_Buffer_t* q);
uint8_t writeBuffer(Ring_Buffer_t* q, uint8_t data);
uint8_t readBuffer(Ring_Buffer_t* q, uint8_t data);
uint8_t isBufferEmpty(Ring_Buffer_t* q);
uint8_t isBufferFull(Ring_Buffer_t* q);
#endif
