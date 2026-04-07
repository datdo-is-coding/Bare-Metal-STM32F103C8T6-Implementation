#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>

/*
    DR: data register
 */

typedef struct{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
}USART_TypeDef;

typedef struct{
    uint32_t baud_rate;
    uint8_t word_length;
    uint8_t stop_bits;
    uint8_t parity;
    uint8_t mode_tx;
    uint8_t mode_rx;
}USART_Config_t;


#define USART1 (USART_TypeDef*) 0x40013800

#define USART2 (USART_TypeDef*) 0x40004400

#define USART3 (USART_TypeDef*) 0x40004800 

#define UART4   (USART_TypeDef*) 0x40004C00

#define UART5   (USART_TypeDef*) 0x40005000  

#define ENABLE  1
#define DISABLE 0

#define USART_8_BIT_W_LENGTH 0
#define USART_9_BIT_W_LENGTH 1

#define WKU_IDLE_LINE                0
#define WKU_ADDR_MARK            1

#define PARITY_EVEN                    0
#define PARITY_ODD                     1

#define RX_ACTIVE_MODE             0
#define RX_MUTE_MODE               1

#define _1_STOP_BIT                0x00
#define _0_5_STOP_BIT              0x01
#define _2_STOP_BIT                0x02
#define _1_5_STOP_BIT              0x03

// Baud rate register
void USART_SetBaudRate(USART_TypeDef* USART, uint32_t baudrate);

uint32_t RCC_GetClock(USART_TypeDef* USART);

void USART_EnableClock(USART_TypeDef* USART);


void USART_Enable(USART_TypeDef* USART, uint8_t state);

void USART_ConfigWordLength(USART_TypeDef* USART, uint8_t word_len);

void USART_ConfigWakeUp(USART_TypeDef* USART, uint8_t wakeup_mode);

void USART_EnableParityControl(USART_TypeDef* USART, uint8_t state);

void USART_OddEvenParity(USART_TypeDef* USART, uint8_t state);

void USART_Init(USART_TypeDef* USART, USART_Config_t* config);

// when PE =1 (PARITY ERROR =1) -> raise an interrupt
void USART_ParityError_IntEnable(USART_TypeDef* USART, uint8_t state);

// enable interrupt for TXEIE Transmit register empty event
void USART_TXE_IntEnable(USART_TypeDef* USART, uint8_t state);

// enable interrupt for TCIE Transmission complete event
void USART_TC_IntEnable(USART_TypeDef* USART, uint8_t state);

// enable interrupt for RXNEIE Receive register not empty event
void USART_RXNE_IntEnable(USART_TypeDef* USART, uint8_t state);

// enable interrupt for IDLEIE Idle line detected event
void USART_IDLE_IntEnable(USART_TypeDef* USART, uint8_t state);

// Enable or disable the USART transmitter and receiver
void USART_Transmitter_Enable(USART_TypeDef* USART, uint8_t state);

void USART_Receiver_Enable(USART_TypeDef* USART, uint8_t state);


void USART_Receiver_WKU_Mode(USART_TypeDef* USART, uint8_t mode);

// this is set by software and clear by hardware
// clear during the stop bit of break
void USART_SendBreak(USART_TypeDef* USART);



void USART_WriteData(USART_TypeDef* USART, uint8_t data);

uint32_t USART_ReadData(USART_TypeDef* USART);


// Control register 2 USART_CR2
void USART_ConfigStopBits(USART_TypeDef* USART,uint8_t stop_bits);

void USART_ConfigClock(USART_TypeDef* USART, uint8_t state);

void USART_ConfigClockPolarity(USART_TypeDef* USART, uint8_t polarity);

void USART_ConfigClockPhase(USART_TypeDef* USART, uint8_t phase);
#endif 
