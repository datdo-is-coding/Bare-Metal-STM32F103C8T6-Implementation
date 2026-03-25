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

// PLLXPRE macro: HSE divided by 2 or not before feeding it to PLL
#define PLL_SRC_HSE_DIV1    (0<<17)
#define PLL_SRC_HSE_DIV2    (1<<17)

// System clock source: HSI, HSE or PLL
#define SYSCLK_SRC_HSI      0x00
#define SYSCLK_SRC_HSE      0x01
#define SYSCLK_SRC_PLL      0x02
#define SWS_MASK            (0x03 << 2)

#define ENABLE              1 
#define DISABLE             0

// ADC prescaler values
#define ADC_DIV2    (0x0 << 14)
#define ADC_DIV4    (0x1 << 14)
#define ADC_DIV6    (0x2 << 14)
#define ADC_DIV8    (0x3 << 14)

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

// Clock interrupt enable
#define RCC_PLL_RDYIE   (1 << 12)
#define RCC_HSE_RDYIE   (1 << 11)
#define RCC_HSI_RDYIE   (1 << 10)
#define RCC_LSE_RDYIE   (1 << 9)
#define RCC_LSI_RDYIE   (1 << 8)

// Clock Clear Flag
#define RCC_CSSC        (1 << 23)
#define PLL_RDYC        (1 << 20)
#define HSE_RDYC        (1 << 19)
#define HSI_RDYC        (1 << 18)
#define LSE_RDYC        (1 << 17)
#define LSI_RDYC        (1 << 16)

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

// APB2 peripheral reset bits
#define RCC_APB2RSTR_TIM_11_RST (1 << 21)
#define RCC_APB2RSTR_TIM_10_RST (1 << 20)
#define RCC_APB2RSTR_TIM_9_RST  (1 << 19)
#define RCC_APB2RSTR_ADC3_RST   (1 << 15)
#define RCC_APB2RSTR_USART1_RST (1 << 14)
#define RCC_APB2RSTR_TIM8_RST   (1 << 13)
#define RCC_APB2RSTR_SPI1_RST   (1 << 12)
#define RCC_APB2RSTR_TIM1_RST   (1 << 11)
#define RCC_APB2RSTR_ADC2_RST   (1 << 10)
#define RCC_APB2RSTR_ADC1_RST   (1 << 9)
#define RCC_APB2RSTR_IOPG_RST   (1 << 8)
#define RCC_APB2RSTR_IOPF_RST   (1 << 7)
#define RCC_APB2RSTR_IOPE_RST   (1 << 6)
#define RCC_APB2RSTR_IOPD_RST   (1 << 5)
#define RCC_APB2RSTR_IOPC_RST   (1 << 4)
#define RCC_APB2RSTR_IOPB_RST   (1 << 3)
#define RCC_APB2RSTR_IOPA_RST   (1 << 2)
#define RCC_APB2RSTR_AFIO_RST   (1 << 0)

// APB1 peripheral reset bits
#define RCC_APB1RSTR_DAC_RST    (1 << 29)
#define RCC_APB1RSTR_PWR_RST    (1 << 28)
#define RCC_APB1RSTR_BKP_RST    (1 << 27)
#define RCC_APB1RSTR_CAN_RST    (1 << 25)
#define RCC_APB1RSTR_USB_RST    (1 << 23)
#define RCC_APB1RSTR_I2C2_RST   (1 << 22)
#define RCC_APB1RSTR_I2C1_RST   (1 << 21)
#define RCC_APB1RSTR_UART5_RST  (1 << 20)
#define RCC_APB1RSTR_UART4_RST  (1 << 19)
#define RCC_APB1RSTR_UART3_RST  (1 << 18)
#define RCC_APB1RSTR_UART2_RST  (1 << 17)
#define RCC_APB1RSTR_SPI3_RST   (1 << 15)
#define RCC_APB1RSTR_SPI2_RST   (1 << 14)
#define RCC_APB1RSTR_WWDG_RST   (1 << 11)
#define RCC_APB1RSTR_TIM_14_RST (1 << 8)
#define RCC_APB1RSTR_TIM_13_RST (1 << 7)
#define RCC_APB1RSTR_TIM_12_RST (1 << 6)
#define RCC_APB1RSTR_TIM_7_RST  (1 << 5)
#define RCC_APB1RSTR_TIM_6_RST  (1 << 4)
#define RCC_APB1RSTR_TIM_5_RST  (1 << 3)
#define RCC_APB1RSTR_TIM_4_RST  (1 << 2)
#define RCC_APB1RSTR_TIM_3_RST  (1 << 1)
#define RCC_APB1RSTR_TIM_2_RST  (1 << 0)

// AHB peripheral clock enable bits
#define SDIO_EN     (1 << 10)
#define FSMC_EN     (1 << 8)
#define CRC_EN      (1 << 6)
#define FLITF_EN    (1 << 4)
#define SRAM_EN     (1 << 2)
#define DMA2_EN     (1 << 1)
#define DMA1_EN     (1 << 0)

//APB2 peripheral clock enable bits
#define TIM11_EN    (1 << 21)
#define TIM10_EN    (1 << 20)
#define TIM9_EN     (1 << 19)
#define ADC3_EN     (1 << 15)
#define USART1_EN   (1 << 14)
#define TIM8_EN     (1 << 13)
#define SPI1_EN     (1 << 12)
#define TIM1_EN     (1 << 11)
#define ADC2_EN     (1 << 10)
#define ADC1_EN     (1 << 9)
#define IOPG_EN     (1 << 8)
#define IOPF_EN     (1 << 7)
#define IOPE_EN     (1 << 6)
#define IOPD_EN     (1 << 5)
#define IOPC_EN     (1 << 4)
#define IOPB_EN     (1 << 3)
#define IOPA_EN     (1 << 2)
#define AFIO_EN     (1 << 0)

// APBE1 peripheral clock enable bits
#define DAC_EN      (1 << 29)
#define PWR_EN      (1 << 28)
#define BKP_EN      (1 << 27)
#define CAN_EN      (1 << 25)
#define USB_EN      (1 << 23)
#define I2C2_EN     (1 << 22)
#define I2C1_EN     (1 << 21)
#define UART5_EN    (1 << 20)
#define UART4_EN    (1 << 19)
#define UART3_EN    (1 << 18)
#define UART2_EN    (1 << 17)
#define SPI3_EN      (1 << 15)
#define SPI2_EN      (1 << 14)
#define WWDG_EN      (1 << 11)
#define TIM14_EN     (1 << 8)
#define TIM13_EN     (1 << 7)
#define TIM12_EN     (1 << 6)
#define TIM7_EN      (1 << 5)
#define TIM6_EN      (1 << 4)
#define TIM5_EN      (1 << 3)
#define TIM4_EN      (1 << 2)
#define TIM3_EN      (1 << 1)
#define TIM2_EN      (1 << 0)

// Backup domain control bits
#define BDRST     (1 << 16)
#define RTC_EN    (1 << 15)

#define RTC_NO_CLOCK  (0x00 << 8)
#define RTC_LSE        (0x01 << 8)
#define RTC_LSI        (0x02 << 8)
#define RTC_HSE_DIV128  (0x03 << 8)

#define LSEBYP         (1 << 2)
#define LSERDY          (1 << 1)
#define LSEON           (1 << 0)

// Control/status register bits
#define LPW_RSTF         (1 << 31)
#define WWDG_RSTF          (1 << 30)
#define IWDG_RSTF          (1 << 29)
#define SFT_RSTF            (1 << 28)
#define POR_RSTF            (1 << 27)
#define PIN_RSTF            (1 << 26)
#define RMVF               (1 << 24)
#define LSI_RDY             (1 << 1)
#define LSION               (1 << 0)

void HSE_Enable(void);
void HSI_Enable(void);
void HSE_Disable(void);
void HSI_Disable(void);

void PLL_Enable(void);
void PLL_Disable(void);
void PLLMUL_Config(uint32_t PLLMUL_Factor);
void PLLSRC_Config(uint32_t PLL_Source);
void PLLXTPRE_Config(uint32_t HSE_entry);

void SYSCLK_Config(uint8_t SYSCLK_Source);

void MCO_Config(uint32_t MCO_Source);


void RCC_APB1_Prescaler_Config(uint32_t APB1_Prescaler);
void RCC_APB2_Prescaler_Config(uint32_t APB2_Prescaler);
void RCC_AHB_Prescaler_Config(uint32_t AHB_Prescaler);

void RCC_Interrupt_Enable(uint32_t interrupt, uint8_t state);
void RCC_Interrupt_Clear(uint32_t interrupt);

void RCC_APB2_Peripheral_Reset(uint32_t peripheral);
void RCC_APB1_Peripheral_Reset(uint32_t peripheral);

void RCC_AHB_Peripheral_Enable(uint32_t peripheral, uint8_t state);
void RCC_APB2_Peripheral_Enable(uint32_t peripheral, uint8_t state);
void RCC_APB1_Peripheral_Enable(uint32_t peripheral, uint8_t state);

// before modifying BDCR register
// enable PWR + enable backup domain write access
// dont use it before you read about backup domain in reference manual
void RCC_LSE_Bypass(uint8_t state);
void RCC_LSE_Enable(uint8_t state);
void RCC_BackupDomain_Reset(void);
void RCC_RTC_Enable(uint32_t state);
void RCC_RTC_Clock_Source_Config(uint32_t RTC_Clock_Source);

uint32_t RCC_Get_Reset_Flag(void);
void RCC_Clear_Reset_Flag(void);
void RCC_LSI_Enable(uint8_t state);
#endif