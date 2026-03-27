#include <stdint.h>
#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H
/*
    CRL: Port configuration register low (GPIOx_CRL)
    Mode and CNF bits for pins 0 to 7 are configured in this register. Each pin is configured using 4 bits (MODEy[1:0] and CNFy[1:0], where y is the pin number).
    
    CRH: Port configuration register high (GPIOx_CRH)
    Mode and CNF bits for pins 8 to 15 are configured in this register. Each pin is configured using 4 bits (MODEy[1:0] and CNFy[1:0], where y is the pin number).
    
    IDR: Port input data register (GPIOx_IDR)
    
    ODR: Port output data register (GPIOx_ODR)
    
    BSRR: Port bit set/reset register (GPIOx_BSRR)
    Atomic level accessing bit but not the whole word
    like ODR or IDR

    BRR: Port bit reset register (GPIOx_BRR)
    
    LCKR: Port configuration lock register (GPIOx_LCKR)
*/
typedef struct{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
}GPIO_Typedef;


#define GPIOA ((GPIO_Typedef*) 0x40010800)
#define GPIOB ((GPIO_Typedef*) 0x40010C00)
#define GPIOC ((GPIO_Typedef*) 0x40011000 )
#define GPIOD ((GPIO_Typedef*) 0x40011400)
#define GPIOE ((GPIO_Typedef*) 0x40011800)
#define GPIOF ((GPIO_Typedef*) 0x40011C00)
#define GPIOG ((GPIO_Typedef*) 0x40012000)

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0

#define GPIO_PIN_0  0
#define GPIO_PIN_1  1
#define GPIO_PIN_2  2
#define GPIO_PIN_3  3
#define GPIO_PIN_4  4
#define GPIO_PIN_5  5
#define GPIO_PIN_6  6
#define GPIO_PIN_7  7
#define GPIO_PIN_8  8
#define GPIO_PIN_9  9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15

#define IOPAEN 2
#define IOPBEN 3
#define IOPCEN 4
#define IOPDEN 5
#define IOPEEN 6
#define IOPFEN 7

#define INPUT_ANALOG_MODE   0x00
#define FLOATING_INPUT_MODE 0x01
#define INPUT_PULL          0x02

// cnf type of output and input
#define OUTPUT_MODE_PUSH    0x00
#define OUTPUT_MODE_OPEN    0x01
#define AF_OUTPUT_PUSH      0x02
#define AF_OUTPUT_OPEN      0x03

// mode for outut or input
#define INPUT_MODE          0x00
#define OUTPUT_10MHz        0x01
#define OUTPUT_2MHz         0x02
#define OUTPUT_50MHz        0x03

#define GPIO_PULL_UP        0x00
#define GPIO_PULL_DOWN      0x01
#define DUMMY_ARG           0x00
void GPIO_Init(GPIO_Typedef* GPIOx,uint8_t GPIO_PIN_x, uint8_t mode, uint8_t cnf,uint8_t pull);
void GPIO_WritePin(GPIO_Typedef* GPIOx,uint8_t GPIO_PIN_x, uint8_t GPIO_Pin_State);
void GPIO_TogglePin(GPIO_Typedef* GPIOx,uint8_t GPIO_PIN_x);
uint32_t GPIO_ReadPin(GPIO_Typedef* GPIOx, uint8_t GPIO_PIN_x);


#endif