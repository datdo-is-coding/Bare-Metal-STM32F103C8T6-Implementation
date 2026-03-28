#include "../include/led_ao.h"
#include "../include/GPIO_driver.h"
AO LED_AO;

state led_state = LED_OFF;

void LED_Dispatcher(Event* e){
    switch (led_state)
    {
    case LED_OFF:
        if(e->sig ==  BUTTON_PRESSED){
            led_state = LED_BLINKING;
        }
        break;
    case LED_BLINKING:
        if(e->sig == BUTTON_PRESSED){
            led_state = LED_OFF;
            GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        }
        else if(e->sig == TIME_OUT){
            GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        }
        break;
    default:
        break;
    }
}

