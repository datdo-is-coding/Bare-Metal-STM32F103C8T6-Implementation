#ifndef LED_AO_H
#define LED_AO_H

#include "Active_Object.h"

extern AO LED_AO;

typedef enum{
    LED_BLINKING,
    LED_ON,
    LED_OFF
}state;

void LED_Dispatcher(Event* e);

#endif