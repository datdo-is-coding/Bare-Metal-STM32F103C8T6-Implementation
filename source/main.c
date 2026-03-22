#include <stdint.h>
#include "../include/GPIO_drivers.h"

void delay(uint32_t time){
    while(time--);
}

int main(){
    GPIO_EnableClock(IOPAEN);
    GPIO_EnableClock(IOPCEN);
    GPIO_Init(GPIOA, GPIO_PIN_5, OUTPUT_10MHz, OUTPUT_MODE_PUSH,DUMMY_ARG);
    GPIO_Init(GPIOC, GPIO_PIN_13, OUTPUT_10MHz, OUTPUT_MODE_PUSH,DUMMY_ARG);
    GPIO_Init(GPIOA, GPIO_PIN_11,INPUT_MODE,INPUT_PULL,GPIO_PULL_UP);
    while(1){
        GPIO_TogglePin(GPIOC,GPIO_PIN_13);
        GPIO_TogglePin(GPIOA,GPIO_PIN_5);
        delay(5000000);
    }
    
}
