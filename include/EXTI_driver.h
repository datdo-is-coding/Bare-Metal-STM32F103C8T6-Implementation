#ifndef EXTI_DRIVER_H
#define EXTI_DRIVER_H

#include <stdint.h>
typedef struct{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
}EXTI_TypeDef;

#define EXTI ((EXTI_TypeDef*)0x40010400)

#define EXTI_LINE_0 0
#define EXTI_LINE_1 1
#define EXTI_LINE_2 2
#define EXTI_LINE_3 3
#define EXTI_LINE_4 4
#define EXTI_LINE_5 5
#define EXTI_LINE_6 6
#define EXTI_LINE_7 7
#define EXTI_LINE_8 8
#define EXTI_LINE_9 9
#define EXTI_LINE_10 10
#define EXTI_LINE_11 11
#define EXTI_LINE_12 12
#define EXTI_LINE_13 13
#define EXTI_LINE_14 14
#define EXTI_LINE_15 15
#define EXTI_LINE_16 16
#define EXTI_LINE_17 17
#define EXTI_LINE_18 18

#define ENABLE 1
#define DISABLE 0

#define EXTI_RISING     0x01
#define EXTI_FALLING    0x02
#define EXTI_BOTH       EXTI_RISING | EXTO_FALLING

void EXTI_EnableInterrupt(uint8_t line); 
void EXTI_DisableInterrupt(uint8_t line);
void EXTI_SetTrigger(uint8_t line, uint8_t trigger);
void EXTI_ClearPending(uint8_t line);
uint8_t EXTI_GetPending(uint8_t line);
void EXTI_EnableEvent(uint8_t line);
void EXTI_GenerateSWInterrupt(uint8_t line);
#endif