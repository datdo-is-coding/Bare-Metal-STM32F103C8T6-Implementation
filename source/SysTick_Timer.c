#include "../include/SysTick_Timer.h"

volatile uint32_t millis = 0;

void SysTick_Enable(uint8_t state){
    if(state == ENABLE || state == DISABLE){
        SysTick -> CTRL &= ~(1 << 0);
        SysTick -> CTRL |= (state << 0);
    }
}

void SysTick_EnableInterrupt(uint8_t state){
    if(state == ENABLE || state == DISABLE){
        SysTick -> CTRL &= ~(1 << 1);
        SysTick -> CTRL |= (state << 1);
    }
}

void SysTick_ConfigReloadValue(uint32_t time){
    if(time > 0x00FFFFFF) return;
    SysTick -> LOAD &= 0x00;
    SysTick -> LOAD |= time;
}

void SysTick_ConfigClockSource(uint8_t CLK_SOURCE){
    if(CLK_SOURCE > 0x01) return;
    SysTick -> CTRL &= ~(1 << 2);
    SysTick -> CTRL |= (CLK_SOURCE << 2);
}

uint32_t SysTick_GetCurrentValue(){
    return SysTick -> VAL;
}
void SysTick_ClearCurrentValue(){
    SysTick -> VAL = 0x00;
}

// ticks = time * clock frequency
// example: HCLK = 72MHz
// time : 1ms = 0.001s
// clock source HCLK /8 = 9MHz
// ticks = 0.001 * 9 000 000 = 9000 ticks
void SysTick_Delay(uint32_t ticks){
    SysTick -> LOAD &= 0x00;
    // Set Reload
    SysTick -> LOAD = ticks - 1;
    // Clear current Value
    SysTick -> VAL = 0;
    // Enable Systick
    SysTick -> CTRL |= (1 << 0);
    while((SysTick -> CTRL & (1<<16)) == 0 );
    SysTick -> CTRL &= ~(1<<0);
}

void SysTick_Handler(void){
    millis++;
}