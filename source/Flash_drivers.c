#include "../include/Flash_drivers.h"

void Flash_SetLatency(uint32_t latency){
    FLASH -> ACR &= ~FLASH_ACR_LATENCY_MASK;
    FLASH -> ACR |= latency;
}

void Flash_EnablePrefetch(uint8_t state){
    if(state == ENABLE){
        FLASH -> ACR |= FLASH_ACR_PRFTBE;
    }
    else if(state == DISABLE){
        FLASH -> ACR &= ~FLASH_ACR_PRFTBE;
    }
}