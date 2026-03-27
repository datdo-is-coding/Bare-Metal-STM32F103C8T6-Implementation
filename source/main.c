#include <stdint.h>
#include "../include/GPIO_driver.h"
#include "../include/RCC_driver.h"
#include "../include/Flash_driver.h"
#include "../include/SysTick_Timer.h"



int main(){
    // System clock configuration
    // Start High-Speed External (HSE) oscillator
    HSE_Enable();
    // Enable Flash Prefetch and set latency for 72MHz operation
    Flash_EnablePrefetch(ENABLE);
    Flash_SetLatency(FLASH_LATENCY_2);
    // Configure AHB, APB1, and APB2 prescalers
    // Set APB1 scaler to make sure the clock is not over 36MHz
    RCC_APB1_Prescaler_Config(APB1_DIV2);
    RCC_AHB_Prescaler_Config(AHB_DIV1);
    RCC_APB2_Prescaler_Config(APB2_DIV1);
    // Disable PLL to configure it, set HSE as PLL source and multiply by 9 to get 72MHz
    PLL_Disable();
    PLLSRC_Config(PLL_SRC_HSE);
    PLLMUL_Config(PLLMUL_x9);

    PLL_Enable();
    // Choose PLL as a clock source
    SYSCLK_Config(SYSCLK_SRC_PLL);
    
    SysTick_ConfigReloadValue(72000);
    
    SysTick_ClearCurrentValue();
    SysTick_ConfigClockSource(Systick_AHB_CLOCK);
    SysTick_EnableInterrupt(ENABLE);
    SysTick_Enable(ENABLE);
    // Enable clock for GPIOC and GPIOA
    RCC_APB2_Peripheral_Enable(RCC_APB2ENR_IOPC_EN, ENABLE);
    RCC_APB2_Peripheral_Enable(RCC_APB2ENR_IOPA_EN, ENABLE);

    // Inittialize GPIOC pin 13 as output and GPIOA pin 11 as input with pull-up

    GPIO_Init(GPIOC, GPIO_PIN_13, OUTPUT_10MHz, OUTPUT_MODE_PUSH,DUMMY_ARG);
    GPIO_Init(GPIOA, GPIO_PIN_11,INPUT_MODE,INPUT_PULL,GPIO_PULL_UP);
    GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    uint32_t last = millis;
    while(1){
        if(millis - last >= 5000){
            GPIO_TogglePin(GPIOC,GPIO_PIN_13);
            last = millis;
        }
            
     
    }
    
}

