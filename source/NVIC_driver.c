#include "../include/NVIC_driver.h"

// enable IRQ matrix bits
void NVIC_EnableIRQ(uint8_t IRQn){
    NVIC_ISER[IRQn / 32] |= (1<<(IRQn % 32));
}
// disable IRQ matrix bits
void NVIC_DisableIRQ(uint8_t IRQn){
    NVIC_ICER[IRQn / 32] |= (1<<(IRQn % 32));
}
// set pending IRQ matrix bits
void NVIC_SetPendingIRQ(uint8_t IRQn){
    NVIC_ISPR[IRQn / 32] |= (1<<(IRQn %32));
}
// clear pending IRQ matrix bits
void NVIC_ClearPendingIRQ(uint8_t IRQn){
    NVIC_ICPR[IRQn /32] |= (1<<(IRQn % 32));
}
// set priority of IRQn, only 4 bits are used for priority, so we shift left by 4
// the priority value should be between 0 and 15, 
// where 0 is the highest priority and 15 is the lowest priority
void NVIC_SetPriority(uint8_t IRQn, uint8_t priority){
    NVIC_IPR[IRQn] = (priority & 0x0F) << 4;
}
// get active status of IRQn, return 1 if active, 0 if not active
uint8_t NVIC_GetActive(uint8_t IRQn){
    return (NVIC_IABR[IRQn / 32] & (1<<(IRQn % 32))) ? 1 : 0;
}
// get pending status of IRQn, return 1 if pending, 0 if not pending
uint8_t NVIC_GetPending(uint8_t IRQn){
    return (NVIC_ISPR[IRQn / 32] & (1<<(IRQn % 32))) ? 1 : 0;
}
// get priority of IRQn, 
// return a value between 0 and 15, where 0 is the highest priority and 15 is the lowest priority
uint8_t NVIC_GetPriority(uint8_t IRQn){
    return (NVIC_IPR[IRQn]>>4) & (0x0F);
}
// set priority grouping, this function is used to configure the priority grouping of the NVIC
void NVIC_SetPriorityGrouping(uint32_t priorityGroup){
    // implement later
}

