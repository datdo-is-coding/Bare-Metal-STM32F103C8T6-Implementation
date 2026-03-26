#include "../include/EXTI_driver.h"

void EXTI_EnableInterrupt(uint8_t line){
    EXTI -> IMR |= (1 << line);
}

void EXTI_DisableInterrupt(uint8_t line){
    EXTI -> IMR &= ~(1 << line);
}

void EXTI_SetTrigger(uint8_t line, uint8_t trigger){
    if(trigger & EXTI_RISING){
        EXTI -> RTSR |= (1 << line);
    }
    else{
        EXTI -> RTSR &= ~(1<<line);
    }

    if(trigger & EXTI_FALLING){
        EXTI -> FTSR |= (1 << line);
    }
    else{
        EXTI -> FTSR &= ~(1<<line);
    }
}

void EXTI_ClearPending(uint8_t line){
    EXTI -> PR |= ( 1<< line);
}

uint8_t EXTI_GetPending(uint8_t line){
    return EXTI -> PR & ( 1<< line) ? 1 : 0;
}

void EXTI_EnableEvent(uint8_t line){
    if(line > 18) return;
    EXTI->EMR |= (1 << line);
}

void EXTI_GenerateSWInterrupt(uint8_t line){
    if(line > 18) return;
    EXTI->SWIER |= (1 << line);
}