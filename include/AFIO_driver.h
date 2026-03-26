#ifndef AFIO_DRIVER_H
#define AFIO_DRIVER_H

#include <stdint.h>
// To read/write AFIO registers
// the AFIO clock should first be enabled

typedef struct{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
    volatile uint32_t MAPR2;
}AFIO_TypeDef;

#define AFIO ((AFIO_TypeDef*)0x40010000)
#define ENABLE  1
#define DISABLE 0

// AFIO_EVCR: Event control register
#define EVOE 1<<7
#define AFIO_PORT_A 0x00
#define AFIO_PORT_B 0x01
#define AFIO_PORT_C 0x02
#define AFIO_PORT_D 0x03
#define AFIO_PORT_E 0x04

#define AFIO_PIN_0 1
#define AFIO_PIN_1 2
#define AFIO_PIN_2 3
#define AFIO_PIN_3 4
#define AFIO_PIN_4 5
#define AFIO_PIN_5 6
#define AFIO_PIN_6 7
#define AFIO_PIN_7 8
#define AFIO_PIN_8 9
#define AFIO_PIN_9 10
#define AFIO_PIN_10 11
#define AFIO_PIN_11 12
#define AFIO_PIN_12 13
#define AFIO_PIN_13 14
#define AFIO_PIN_14 15
#define AFIO_PIN_15 16

#define AFIO_PORT_A_x 0x00
#define AFIO_PORT_B_x 0x01
#define AFIO_PORT_C_x 0x02
#define AFIO_PORT_D_x 0x03
#define AFIO_PORT_E_x 0x04


void AFIO_EventOutputEnable(uint8_t state);
void AFIO_SetEventOutputSource(uint8_t port, uint8_t pin);

void AFIO_ConfigureEXTI(uint8_t EXTIx, uint8_t pin);
#endif