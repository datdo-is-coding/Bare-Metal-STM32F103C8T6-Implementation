#ifndef RCC_DRIVERS_H
#define RCC_DRIVERS_H
#include <stdint.h>

/*
    REGISTERS IN RCC 
    CR: Clock control register (RCC_CR)
    CFGR: Clock configuration register (RCC_CFGR)
    CIR: Clock interrupt register (RCC_CIR)
    APB2RSTR: APB2 peripheral reset register (RCC_APB2RSTR)
    APB1RSTR: APB1 peripheral reset register (RCC_APB1RSTR)
    AHBENR: AHB peripheral clock enable register (RCC_AHBENR)
    APB2ENR: APB2 peripheral clock enable register (RCC_APB2ENR)
    APB1ENR: APB1 peripheral clock enable register (RCC_APB1ENR)
    BDCR: Backup domain control register (RCC_BDCR)
    CSR: Control/status register (RCC_CSR)
*/


typedef struct{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
}RCC_Typedef;

#define RCC ((RCC_Typedef*) 0x40021000U)

// CLOCK CONTROL BITS
#define HSE_ON              (1<<16)
#define HSI_ON              (1<<0)
#define HSE_RDY             (1<<17)
#define HSI_RDY             (1<<1)
#define HSE_OFF             (1<<16)
#define HSI_OFF             (1<<0)
#define PLL_ON              (1<<24)
#define PLL_OFF             (1<<24)
#define PLL_RDY             (1 << 25)

// MCO output clock source
#define MCO_CLEAR_MASK      (0x07 << 24)
#define MCO_NO_CLK          (0x00 << 24)
#define MCO_SYS_CLK         (0x04  << 24)
#define MCO_HSI             (0x05 << 24)
#define MCO_HSE             (0x06 << 24)
#define MCO_PLL_DIV2        (0x07 << 24)

// PLL multiplication factor 
#define PLLMUL_CLEAR_MASK   (0x0F << 18)
#define PLLMUL_x4           (0x02 <<18)
#define PLLMUL_x5           (0x03 << 18)
#define PLLMUL_x6           (0x04 << 18)
#define PLLMUL_x7           (0x05 << 18)
#define PLLMUL_x8           (0x06 << 18)
#define PLLMUL_x9           (0x07 << 18)
#define PLLMUL_x6_5         (0x0D << 18)

// PLL source: HSI or HSE
#define PLL_SRC_HSI_DIV2    (0<<16)
#define PLL_SRC_HSE         (1<<16)

// System clock source: HSI, HSE or PLL
#define SYSCLK_SRC_HSI      0x00
#define SYSCLK_SRC_HSE      0x01
#define SYSCLK_SRC_PLL      0x02
#define SWS_MASK            (0x03 << 2)

#define ENABLE              1 
#define DISABLE             0

// APB2 peripheral clock enable bits
#define RCC_APB2ENR_USART1_EN   (1 << 14)
#define RCC_APB2ENR_SPI1_EN     (1 << 12)
#define RCC_APB2ENR_TIM1_EN     (1 << 11)
#define RCC_APB2ENR_ADC2_EN     (1 << 10)
#define RCC_APB2ENR_ADC1_EN     (1 << 9)
#define RCC_APB2ENR_IOPE_EN     (1 << 6)
#define RCC_APB2ENR_IOPD_EN     (1 << 5)
#define RCC_APB2ENR_IOPC_EN     (1 << 4)
#define RCC_APB2ENR_IOPB_EN     (1 << 3)
#define RCC_APB2ENR_IOPA_EN     (1 << 2)
#define RCC_APB2ENR_AFIO_EN     (1 << 0)

// APB1 prescaler values
#define APB1_DIV1   (0x0 << 8)
#define APB1_DIV2   (0x4 << 8)
#define APB1_DIV4   (0x5 << 8)
#define APB1_DIV8   (0x6 << 8)
#define APB1_DIV16  (0x7 << 8)

// APB2 Prescaler values
#define APB2_DIV1   (0x0 << 11)
#define APB2_DIV2   (0x4 << 11)
#define APB2_DIV4   (0x5 << 11)
#define APB2_DIV8   (0x6 << 11)
#define APB2_DIV16  (0x7 << 11)

// AHB Prescaler values
#define AHB_DIV1   (0x0 << 4)
#define AHB_DIV2   (0x8 << 4)
#define AHB_DIV4   (0x9 << 4)
#define AHB_DIV8   (0xA << 4)
#define AHB_DIV16  (0xB << 4)
#define AHB_DIV64  (0xC << 4)
#define AHB_DIV128 (0xD << 4)
#define AHB_DIV256 (0xE << 4)
#define AHB_DIV512 (0xF << 4)

#define APB1_CLEAR_MASK (0x07 << 8)
#define APB2_CLEAR_MASK (0x07 << 11)
#define AHB_CLEAR_MASK  (0x0F << 4)

void HSE_Enable(void);
void HSI_Enable(void);
void HSE_Disable(void);
void HSI_Disable(void);

void PLL_Enable(void);
void PLL_Disable(void);

void PLLMUL_Config(uint32_t PLLMUL_Factor);
void PLLSRC_Config(uint32_t PLL_Source);
void SYSCLK_Config(uint8_t SYSCLK_Source);

void MCO_Config(uint32_t MCO_Source);

void RCC_APB2_Enable(uint32_t peripheral, uint8_t state);

void RCC_APB1_Prescaler_Config(uint32_t APB1_Prescaler);
void RCC_APB2_Prescaler_Config(uint32_t APB2_Prescaler);
void RCC_AHB_Prescaler_Config(uint32_t AHB_Prescaler);
#endif