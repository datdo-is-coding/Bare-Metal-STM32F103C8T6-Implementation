#include "../include/RCC_driver.h"

// Configure MCO output clock source: No Clock, System Clock, HSI, HSE or PLL divided by 2
void MCO_Config(uint32_t MCO_Source){
    RCC -> CFGR &= ~MCO_CLEAR_MASK;
    RCC -> CFGR |= MCO_Source;
}

// Enable High Speed External Crystal
void HSE_Enable(void){
    RCC -> CR |= HSE_ON;
    while(!(RCC -> CR & HSE_RDY));
}

// Enable High Speed Internal Oscillator
void HSI_Enable(void){
    RCC -> CR |= HSI_ON;
    while(!(RCC -> CR & HSI_RDY));
}

// Enable Phase Locked Loop
void PLL_Enable(void){
    RCC -> CR |= PLL_ON;
    while(!(RCC -> CR & PLL_RDY));
}
// Disable HSE / HSI / PLL
void HSE_Disable(void){ RCC -> CR &= ~HSE_OFF; }
void HSI_Disable(void){ RCC -> CR &= ~HSI_OFF; }
void PLL_Disable(void){RCC -> CR &= ~PLL_OFF;}

// Configure PLL multiplication factor and source
void PLLMUL_Config(uint32_t PLLMUL_Factor){
    // according to hardware rule, 
    // do not change PLL param when PLL is on, 
    // so return if PLL is on
    if(RCC -> CR & PLL_ON){
        return;
    }
    RCC -> CFGR &= ~PLLMUL_CLEAR_MASK;
    RCC -> CFGR |= PLLMUL_Factor;
}
void PLLSRC_Config(uint32_t PLL_Source){
    // according to hardware rule, 
    // do not change PLL param when PLL is on, 
    // so return if PLL is on
    if(RCC -> CR & PLL_ON){
        return;
    }
    RCC -> CFGR &= ~(1<<16);
    RCC -> CFGR |= PLL_Source;
}
// Determine to divide HSE by 2 before feeding it to PLL or not
void PLLXTPRE_Config(uint32_t HSE_entry){
    // according to hardware rule, 
    // do not change PLL param when PLL is on, 
    // so return if PLL is on
    if(RCC -> CR & PLL_ON){
        return;
    }
    RCC -> CFGR &= ~(1<<17);
    RCC -> CFGR |= HSE_entry;
}
// Configure clock source for System Clock Source
void SYSCLK_Config(uint8_t SYSCLK_Source){
    if(SYSCLK_Source > 0x02) return;
    if(SYSCLK_Source == SYSCLK_SRC_PLL && !(RCC -> CR & PLL_RDY)){
        return;
    }
    RCC -> CFGR &= ~(0x03);
    RCC -> CFGR |= SYSCLK_Source;
    while((RCC -> CFGR & SWS_MASK)!= (SYSCLK_Source << 2));
}


// Configure ADC prescaler, clock source: PCLK
void RCC_ADC_Prescaler_Config(uint32_t ADC_Prescaler){
    RCC -> CFGR &= ~(0x03 << 14);
    RCC -> CFGR |= ADC_Prescaler;
}


// Configure APB1, APB2 and AHB prescalers
void RCC_APB1_Prescaler_Config(uint32_t APB1_Prescaler){
    RCC -> CFGR &= ~APB1_CLEAR_MASK;
    RCC -> CFGR |= APB1_Prescaler;
}

void RCC_APB2_Prescaler_Config(uint32_t APB2_Prescaler){
    RCC -> CFGR &= ~APB2_CLEAR_MASK;
    RCC -> CFGR |= APB2_Prescaler;
}

void RCC_AHB_Prescaler_Config(uint32_t AHB_Prescaler){
    RCC -> CFGR &= ~AHB_CLEAR_MASK;
    RCC -> CFGR |= AHB_Prescaler;
}

// Enable interrupt
void RCC_Interrupt_Enable(uint32_t interrupt, uint8_t state){
    if(state == ENABLE){
        RCC -> CIR |= interrupt;
    }
    else if(state == DISABLE){
        RCC -> CIR &= ~interrupt;
    }
}

// Clear interrupt flag
void RCC_Interrupt_Clear(uint32_t interrupt){
    RCC -> CIR |= interrupt;
}


// Set reset bit 1 
// and set the value to 0 to release reset
void RCC_APB2_Peripheral_Reset(uint32_t peripheral){
    RCC -> APB2RSTR |= peripheral;
    RCC -> APB2RSTR &= ~peripheral;
}

// reset APB1 Peripheral
void RCC_APB1_Peripheral_Reset(uint32_t peripheral){
    RCC -> APB1RSTR |= peripheral;
    RCC -> APB1RSTR &= ~peripheral;
}

// AHB peripheral clock enable
void RCC_AHB_Peripheral_Enable(uint32_t peripheral, uint8_t state){
    if(state == ENABLE){
        RCC -> AHBENR |= peripheral;
    }
    else if(state == DISABLE){
        RCC -> AHBENR &= ~peripheral;
    }
}
//APB2 Peripheral Enable
void RCC_APB2_Peripheral_Enable(uint32_t peripheral, uint8_t state){
    if(state == ENABLE){
        RCC -> APB2ENR |= peripheral;
    }
    else if(state == DISABLE){
        RCC -> APB2ENR &= ~peripheral;
    }
}

void RCC_APB1_Peripheral_Enable(uint32_t peripheral, uint8_t state){
    if(state == ENABLE){
        RCC->APB1ENR |= peripheral;
    }
    else if(state == DISABLE){
        RCC->APB1ENR &= ~peripheral;
    }
}

void RCC_LSE_Bypass(uint8_t state){
    if(RCC -> BDCR & LSEON){
        return;
    }
    if(state == ENABLE){
        RCC -> BDCR |= LSEBYP;
    }
    else if(state == DISABLE){
        RCC -> BDCR &= ~LSEBYP;
    }
}

void RCC_LSE_Enable(uint8_t state){

    if(state == ENABLE){
        RCC -> BDCR |= LSEON;
        while(!(RCC -> BDCR & LSERDY));
    }
    else if(state == DISABLE){
        RCC -> BDCR &= ~LSEON;
    }
    
}

void RCC_BackupDomain_Reset(void){
    RCC -> BDCR |= BDRST;
    RCC -> BDCR &= ~BDRST;
}

void RCC_RTC_Enable(uint32_t state){
    if(state == ENABLE){
        RCC -> BDCR |= RTC_EN;
    }
    else if(state == DISABLE){
        RCC -> BDCR &= ~RTC_EN;
    }
}
// if once selected clock source for the RTC
// must call BDCR reset function to change it
void RCC_RTC_Clock_Source_Config(uint32_t RTC_Clock_Source){
    if(RCC -> BDCR & RTC_EN){
        return;
    }
    RCC -> BDCR &= ~(0x03 << 8);
    RCC -> BDCR |= RTC_Clock_Source;
}
void RCC_Clear_Reset_Flag(void){
    RCC -> CSR |= RMVF;
}

uint32_t RCC_Get_Reset_Flag(void){
    return RCC -> CSR & (LPW_RSTF | WWDG_RSTF | IWDG_RSTF | SFT_RSTF | POR_RSTF | PIN_RSTF);
}

void RCC_LSI_Enable(uint8_t state){
    if(state == ENABLE){
        RCC -> CSR |= LSION;
        while(!(RCC -> CSR & LSI_RDY));
    }
    else if(state == DISABLE){
        RCC -> CSR &= ~LSION;
    }
}

