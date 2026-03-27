#include <stdint.h>
#include "../include/GPIO_driver.h"


// mode for outut or input
// cnf type of output and input
void GPIO_Init(GPIO_Typedef* GPIOx,uint8_t GPIO_PIN_x, uint8_t mode, uint8_t cnf,uint8_t pull){
    uint8_t mode_cnf = (cnf<<2) | mode;
    if(GPIO_PIN_x<=7){
        GPIOx -> CRL &= ~(0xF << (4 * GPIO_PIN_x));
        GPIOx -> CRL |= (mode_cnf << (4 * GPIO_PIN_x));
    }
    else if(GPIO_PIN_x>=8 && GPIO_PIN_x<=15){
        GPIOx -> CRH &= ~(0xF << (4 * (GPIO_PIN_x - 8)));
        GPIOx -> CRH |= (mode_cnf << (4 * (GPIO_PIN_x-8)));
    }
    if(mode == INPUT_MODE && cnf == INPUT_PULL){
        if(pull == GPIO_PULL_DOWN){
            GPIOx -> ODR &= ~(1<<GPIO_PIN_x);
        }
        else if(pull == GPIO_PULL_UP){
            GPIOx -> ODR |= (1<<GPIO_PIN_x);
        }
    }
}
void GPIO_WritePin(GPIO_Typedef* GPIOx,uint8_t GPIO_PIN_x, uint8_t GPIO_Pin_State){
    if(GPIO_Pin_State == GPIO_PIN_SET){
        GPIOx -> BSRR = 1 << GPIO_PIN_x;
    }
    else{
        GPIOx -> BSRR = 1 << (GPIO_PIN_x+16);
    }   
}

void GPIO_TogglePin(GPIO_Typedef* GPIOx,uint8_t GPIO_PIN_x){
    if(GPIOx->ODR & (1<<GPIO_PIN_x)){
        GPIOx -> BSRR = 1 << (GPIO_PIN_x+16);
    }
    else{
        GPIOx -> BSRR = 1 << GPIO_PIN_x;
    }
}

uint32_t GPIO_ReadPin(GPIO_Typedef* GPIOx, uint8_t GPIO_PIN_x){
    if( GPIO_PIN_x <=15){
        return (GPIOx -> IDR >>GPIO_PIN_x) &0x01;
    }
    return 0;
}