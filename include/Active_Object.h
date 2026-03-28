#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <stdint.h>
#include "queue.h"

typedef struct{
    Queue q;
    void (*dispatcher)(Event*);
}AO;

#endif