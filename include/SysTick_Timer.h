#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H

#include <stdint.h>

/**/

typedef struct{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
}SysTick_Typedef;

extern volatile uint32_t millis;

#define SysTick ((SysTick_Typedef*) 0xE000E010)

#define ENABLE 1
#define DISABLE 0

#define Systick_AHB_CLOCK_DIV_8 0
#define Systick_AHB_CLOCK       1



void SysTick_Handler(void);

void SysTick_Enable(uint8_t state);
void SysTick_EnableInterrupt(uint8_t state);
void SysTick_ConfigClockSource(uint8_t CLK_SOURCE);
uint32_t SysTick_GetCurrentValue();
void SysTick_ClearCurrentValue();
void SysTick_ConfigReloadValue(uint32_t time);

void SysTick_Delay(uint32_t ticks);
#endif