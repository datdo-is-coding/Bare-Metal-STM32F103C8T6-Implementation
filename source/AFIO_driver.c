#include "../include/AFIO_driver.h"

void AFIO_EventOutputEnable(uint8_t state){
    if(state == ENABLE){
        AFIO->EVCR |= EVOE;
    }else{
        AFIO->EVCR &= ~EVOE;
    }
}

void AFIO_SetEventOutputSource(uint8_t port, uint8_t pin){
    AFIO -> EVCR &= (1<<7);
    uint8_t value = (port<<4) + pin;
    AFIO -> EVCR |= value;
}

void AFIO_ConfigureEXTI(uint8_t EXTIx, uint8_t pin){
    uint8_t index = EXTIx / 4;
    uint8_t shift = (EXTIx / 4) *4;
    AFIO -> EXTICR[index] &= (0x0F << shift);
    AFIO -> EXTICR[index] |= (pin << shift);
}
