#ifndef NVIC_DRIVER_H
#define NVIC_DRIVER_H

#include <stdint.h>
/*
    ISER: Interrupt Set-Enable Registers
    ICER: Interrupt Clear-Enable Registers
    ISPR: Interrupt Set-Pending Registers
    ICPR: Interrupt Clear-Pending Registers
    IABR: Interrupt Active Bit Registers
    IPR: Interrupt Priority Registers
    
*/
#define NVIC_ISER   ((volatile uint32_t*)0xE000E100)
#define NVIC_ICER   ((volatile uint32_t*)0xE000E180)
#define NVIC_ISPR   ((volatile uint32_t*)0xE000E200)
#define NVIC_ICPR   ((volatile uint32_t*)0xE000E280)
#define NVIC_IABR   ((volatile uint32_t*)0xE000E300)
#define NVIC_IPR    ((volatile uint8_t*) 0xE000E400)

void NVIC_EnableIRQ(uint8_t IRQn);
void NVIC_DisableIRQ(uint8_t IRQn);
void NVIC_SetPendingIRQ(uint8_t IRQn);
void NVIC_ClearPendingIRQ(uint8_t IRQn);
void NVIC_SetPriority(uint8_t IRQn, uint8_t priority);
uint8_t NVIC_GetActive(uint8_t IRQn);
uint8_t NVIC_GetPending(uint8_t IRQn);
uint8_t NVIC_GetPriority(uint8_t IRQn);
void NVIC_SetPriorityGrouping(uint32_t priorityGroup);

#endif