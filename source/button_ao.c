#include "../include/button_ao.h"
#include "../include/led_ao.h"
#include "../include/queue.h"
#include "../include/SysTick_Timer.h"
AO Button_AO;

void Button_Dispatcher(Event* e){

    static uint32_t last_press = 0;

    if(e->sig == BUTTON_PRESSED){

        if(millis - last_press < 50){
            return;   
        }

        last_press = millis;
        Event ev = {BUTTON_PRESSED};
        enqueue(&LED_AO.q, &ev);
    }
}