#include "../include/RCC_drivers.h"

void HSE_Enable(void){
    RCC -> CR |= HSE_ON;
    while(!(RCC -> CR & HSE_RDY));
}
void HSI_Enable(void){
    RCC -> CR |= HSI_ON;
    while(!(RCC -> CR & HSI_RDY));
}

void PLL_Enable(void){
    RCC -> CR |= PLL_ON;
    while(!(RCC -> CR & PLL_RDY));
}

void HSE_Disable(void){ RCC -> CR &= ~HSE_OFF; }
void HSI_Disable(void){ RCC -> CR &= ~HSI_OFF; }
void PLL_Disable(void){RCC -> CR &= ~PLL_OFF;}

void PLLMUL_Config(uint32_t PLLMUL_Factor){
    if(RCC -> CR & PLL_ON){
        return;
    }
    RCC -> CFGR &= ~PLLMUL_CLEAR_MASK;
    RCC -> CFGR |= PLLMUL_Factor;
}
void PLLSRC_Config(uint32_t PLL_Source){
    RCC -> CFGR &= ~(1<<16);
    RCC -> CFGR |= PLL_Source;
}

void SYSCLK_Config(uint8_t SYSCLK_Source){
    RCC -> CFGR &= ~(0x03);
    RCC -> CFGR |= SYSCLK_Source;
    while((RCC -> CFGR & SWS_MASK)!= (SYSCLK_Source << 2));
}

void RCC_APB2_Enable(uint32_t peripheral, uint8_t state){
    if(state == ENABLE){
        RCC -> APB2ENR |= peripheral;
    }
    else if(state == DISABLE){
        RCC -> APB2ENR &= ~peripheral;
    }
}

void RCC_APB1_Prescaler_Config(uint32_t APB1_Prescaler){
    RCC -> CFGR &= APB1_CLEAR_MASK;
    RCC -> CFGR |= APB1_Prescaler;
}

void RCC_APB2_Prescaler_Config(uint32_t APB2_Prescaler){
    RCC -> CFGR &= APB2_CLEAR_MASK;
    RCC -> CFGR |= APB2_Prescaler;
}

void RCC_AHB_Prescaler_Config(uint32_t AHB_Prescaler){
    RCC -> CFGR &= AHB_CLEAR_MASK;
    RCC -> CFGR |= AHB_Prescaler;
}



void MCO_Config(uint32_t MCO_Source){
    RCC -> CFGR &= ~MCO_CLEAR_MASK;
    RCC -> CFGR |= MCO_Source;
}
