#include <stdint.h>
#include "../include/GPIO_driver.h"
#include "../include/RCC_driver.h"
#include "../include/Flash_driver.h"
#include "../include/SysTick_Timer.h"
#include "../include/mem_alloc.h"
#include "../include/button_ao.h"
#include "../include/led_ao.h"
#include "../include/AFIO_driver.h"
#include "../include/EXTI_driver.h"
#include "../include/NVIC_driver.h"
#include "../include/queue.h"

extern AO LED_AO;
extern AO Button_AO;

void EXTI15_10_IRQHandler(void){
    static uint32_t last = 0;

    if(EXTI_GetPending(11)){

        if(millis - last > 50){
            Event e = {BUTTON_PRESSED};
            enqueue(&Button_AO.q, &e);
            last = millis;
        }

        EXTI_ClearPending(11);
    }
}


int main(){
    // System clock configuration
    // Start High-Speed External (HSE) oscillator
    RCC_HSE_Enable();
    // Enable Flash Prefetch and set latency for 72MHz operation
    Flash_EnablePrefetch(ENABLE);
    Flash_SetLatency(FLASH_LATENCY_2);
    // Configure AHB, APB1, and APB2 prescalers
    // Set APB1 scaler to make sure the clock is not over 36MHz
    RCC_APB1_Prescaler_Config(APB1_DIV2);
    RCC_AHB_Prescaler_Config(AHB_DIV1);
    RCC_APB2_Prescaler_Config(APB2_DIV1);
    // Disable PLL to configure it, set HSE as PLL source and multiply by 9 to get 72MHz
    RCC_PLL_Disable();
    RCC_PLLSRC_Config(PLL_SRC_HSE);
    RCC_PLLMUL_Config(PLLMUL_x9);

    RCC_PLL_Enable();
    // Choose PLL as a clock source
    RCC_SYSCLK_Config(SYSCLK_SRC_PLL);
    
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
    
    // Enable AFIO clock
RCC_APB2_Peripheral_Enable(RCC_APB2ENR_AFIO_EN, ENABLE);

// Map PA11 → EXTI11
AFIO_ConfigureEXTI(11, AFIO_PORT_A);

// Configure EXTI line 11 for falling edge trigger
EXTI_SetTrigger(11, EXTI_FALLING);
// Enable EXTI line 11 interrupt
EXTI_EnableInterrupt(11);

// Enable NVIC
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_SetPriority(EXTI15_10_IRQn, 1);

    LED_AO.dispatcher = LED_Dispatcher;
    Button_AO.dispatcher = Button_Dispatcher;
    queue_init(&LED_AO.q);
    queue_init(&Button_AO.q);
    uint32_t last = millis;
    while(1){
        if(!isEmpty(&LED_AO.q)){
            while(!isEmpty(&LED_AO.q)){
                Event e;
                dequeue(&LED_AO.q, &e);
                LED_AO.dispatcher(&e);
            }
        }
        else if(!isEmpty(&Button_AO.q)){
            while(!isEmpty(&Button_AO.q)){
                Event e;
                dequeue(&Button_AO.q, &e);
                Button_AO.dispatcher(&e);
            }
        }
    }
}

