#include "../include/queue.h"
#include <stddef.h>
void queue_init(Queue* q){
    q -> head = 0;
    q -> tail = 0;
    q -> count =0;
}

uint8_t isFull(Queue *q){
    return q -> count == QUEUE_SIZE;
}

uint8_t isEmpty(Queue *q){
    return q -> count == 0;
}
uint8_t enqueue(Queue* q,Event *e){
    if(q -> count == QUEUE_SIZE) return 0;
    q -> buffer[q -> head] = *e;
    q -> head = (q->head + 1) % QUEUE_SIZE;
    q -> count ++;
    return 1;
}

uint8_t dequeue(Queue* q,Event *e){
    if(q-> count == 0) return 0;
    *e = q -> buffer[q->tail];
    q -> tail = (q->tail + 1) % QUEUE_SIZE;
    q -> count --;
    return 1;
}
