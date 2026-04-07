#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#define QUEUE_SIZE 20

typedef enum{
    BUTTON_PRESSED,
    TIME_OUT,
    QUEUE_OVERFLOW
}Signal;

typedef struct{
    Signal sig;
}Event;
typedef struct{
    Event buffer[QUEUE_SIZE];
    int head;
    int tail;
    int count;
}Queue;

void queue_init(Queue *q);
uint8_t enqueue(Queue *q, Event *e);
uint8_t dequeue(Queue *q, Event *e);
uint8_t isEmpty(Queue *q);
uint8_t isFull(Queue *q);
#endif
