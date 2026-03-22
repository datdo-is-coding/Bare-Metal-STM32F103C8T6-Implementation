#include <stdint.h>

// the address for initialized data
extern uint32_t _sidata;
// the address for the start of .data section on the SRAM
extern uint32_t _sdata;
// the address for the end of .data section on the SRAM
extern uint32_t _edata;
// the address for the start of .bss section on the SRAM
extern uint32_t _sbss;
// the address for the end of .bss section on the RAM
extern uint32_t _ebss;
// the address for the end of stack memory in RAM (aka the end of the RAM)
extern uint32_t _estack;

#define RESERVED 0

extern int main(void);


/*
    Reset Handler
    Behaviour:
    - Copy initialized data from Flash to SRAM
    - Zerod .bss section
    - Calls main()
*/
void Reset_Handler(void){
    uint32_t* src = (uint32_t*) &_sidata;
    uint32_t* dst = (uint32_t*) &_sdata;
    while(dst < (uint32_t*)&_edata){
        *dst++ = *src++;
    }

    dst = (uint32_t*) & _sbss;
    while(dst < (uint32_t*) &_ebss){
        *dst++ = 0;
    }

    main();
    while (1);
}

/*
    Default Handler
    Behaviour: just HANG the CPU 
               with infinite loop
*/
void Default_Handler(void){
    while(1);
}

void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

void WWDG_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void TAMPER_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));

void DMA1_Channel1_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));

void ADC1_2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));

void USB_HP_CAN1_TX_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void USB_LP_CAN1_RX0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));

void EXTI9_5_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));

void TIM1_BRK_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));

void TIM2_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));

void I2C1_EV_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));

void SPI1_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));

void USART1_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));

void EXTI15_10_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));

void RTC_Alarm_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void USBWakeUp_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));

void BootRAM(void)                    __attribute__((weak, alias("Default_Handler")));
/*
    This is the vector table
    for medium density devices STM32F101,
    STM32F102, STM32F103

    In our case the Blue Pill STM32F103C8T6
*/
const uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    (uint32_t) &_estack,
    (uint32_t) &Reset_Handler,
    (uint32_t) &NMI_Handler,
    (uint32_t) &HardFault_Handler,
    (uint32_t) &MemManage_Handler,
    (uint32_t) &BusFault_Handler,
    (uint32_t) &UsageFault_Handler,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) &SVC_Handler,
    (uint32_t) &DebugMon_Handler,
    (uint32_t) RESERVED,
    (uint32_t) &PendSV_Handler,
    (uint32_t) &SysTick_Handler,
    (uint32_t) &WWDG_IRQHandler,
    (uint32_t) &PVD_IRQHandler,
    (uint32_t) &TAMPER_IRQHandler,
    (uint32_t) &RTC_IRQHandler,
    (uint32_t) &FLASH_IRQHandler,
    (uint32_t) &RCC_IRQHandler,
    (uint32_t) &EXTI0_IRQHandler,
    (uint32_t) &EXTI1_IRQHandler,
    (uint32_t) &EXTI2_IRQHandler,
    (uint32_t) &EXTI3_IRQHandler,
    (uint32_t) &EXTI4_IRQHandler,
    (uint32_t) &DMA1_Channel1_IRQHandler,
    (uint32_t) &DMA1_Channel2_IRQHandler,
    (uint32_t) &DMA1_Channel3_IRQHandler,
    (uint32_t) &DMA1_Channel4_IRQHandler,
    (uint32_t) &DMA1_Channel5_IRQHandler,
    (uint32_t) &DMA1_Channel6_IRQHandler,
    (uint32_t) &DMA1_Channel7_IRQHandler,
    (uint32_t) &ADC1_2_IRQHandler,
    (uint32_t) &USB_HP_CAN1_TX_IRQHandler,
    (uint32_t) &USB_LP_CAN1_RX0_IRQHandler,
    (uint32_t) &CAN1_RX1_IRQHandler,
    (uint32_t) &CAN1_SCE_IRQHandler,
    (uint32_t) &EXTI9_5_IRQHandler,
    (uint32_t) &TIM1_BRK_IRQHandler,
    (uint32_t) &TIM1_UP_IRQHandler,
    (uint32_t) &TIM1_TRG_COM_IRQHandler,
    (uint32_t) &TIM1_CC_IRQHandler,
    (uint32_t) &TIM2_IRQHandler,
    (uint32_t) &TIM3_IRQHandler,
    (uint32_t) &TIM4_IRQHandler,
    (uint32_t) &I2C1_EV_IRQHandler,
    (uint32_t) &I2C1_ER_IRQHandler,
    (uint32_t) &I2C2_EV_IRQHandler,
    (uint32_t) &I2C2_ER_IRQHandler,
    (uint32_t) &SPI1_IRQHandler,
    (uint32_t) &SPI2_IRQHandler,
    (uint32_t) &USART1_IRQHandler,
    (uint32_t) &USART2_IRQHandler,
    (uint32_t) &USART3_IRQHandler,
    (uint32_t) &EXTI15_10_IRQHandler,
    (uint32_t) &RTC_Alarm_IRQHandler,
    (uint32_t) &USBWakeUp_IRQHandler,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) RESERVED,
    (uint32_t) &BootRAM
};