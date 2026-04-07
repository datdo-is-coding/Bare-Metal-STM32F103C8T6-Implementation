
#include "../include/UART_driver.h"
#include "../include/RCC_driver.h"
#include "../include/GPIO_driver.h"
#include "../include/ring_buffer.h"

Ring_Buffer_t uart_tx_buffer;

uint32_t RCC_GetClock(USART_TypeDef* USART){
    if(USART == USART1){
        return 72000000;
    }
    else{
        return 36000000;
    }
}

void USART_EnableClock(USART_TypeDef* USART){
    if(USART == USART1){
        RCC_APB2_Peripheral_Enable(USART1_EN, ENABLE);
    }
    else if(USART == USART2){
        RCC_APB1_Peripheral_Enable(USART2_EN, ENABLE);
    }
    else if(USART == USART3){
        RCC_APB1_Peripheral_Enable(USART3_EN, ENABLE);    }
    else if(USART == UART4){
        RCC_APB1_Peripheral_Enable(USART4_EN, ENABLE);    }
    else if(USART == UART5){
        RCC_APB1_Peripheral_Enable(USART5_EN, ENABLE);    }
}

void USART_GPIO_Init(USART_TypeDef* USART){
    if(USART == USART1){
        // GPIOA PA9 (TX) and PA10 (RX)
        RCC_APB2_Peripheral_Enable(IOPA_EN, ENABLE);
        GPIO_Init(GPIOA, GPIO_PIN_9, OUTPUT_50MHz, AF_OUTPUT_PP, DUMMY_ARG);
        GPIO_Init(GPIOA, GPIO_PIN_10, INPUT_MODE, INPUT_PULL, GPIO_PULL_UP);
    }
    else if(USART == USART2){
        // GPIOA PA2 (TX) and PA3 (RX)
        RCC_APB2_Peripheral_Enable(IOPA_EN, ENABLE);
        GPIO_Init(GPIOA, GPIO_PIN_2, OUTPUT_50MHz, AF_OUTPUT_PP, DUMMY_ARG);
        GPIO_Init(GPIOA, GPIO_PIN_3, INPUT_MODE, INPUT_PULL, GPIO_PULL_UP);
    }
    else if(USART == USART3){
        // GPIOB PB10 (TX) and PB11 (RX)
        RCC_APB2_Peripheral_Enable(IOPB_EN, ENABLE);
        GPIO_Init(GPIOB, GPIO_PIN_10, OUTPUT_50MHz, AF_OUTPUT_PP, DUMMY_ARG);
        GPIO_Init(GPIOB, GPIO_PIN_11, INPUT_MODE, INPUT_PULL,  GPIO_PULL_UP);
    }
    else if(USART == UART4){
        // GPIOC PC10 (TX) and PC11 (RX)
        RCC_APB2_Peripheral_Enable(IOPC_EN, ENABLE);
        GPIO_Init(GPIOC, GPIO_PIN_10, OUTPUT_50MHz, AF_OUTPUT_PP, DUMMY_ARG);
        GPIO_Init(GPIOC, GPIO_PIN_11, INPUT_MODE, INPUT_PULL,  GPIO_PULL_UP);
    }
    else if(USART == UART5){
        // GPIOC PC12 (TX) and GPIOD PD2 (RX)
        RCC_APB2_Peripheral_Enable(IOPC_EN, ENABLE);
        RCC_APB2_Peripheral_Enable(IOPD_EN, ENABLE);
        GPIO_Init(GPIOC, GPIO_PIN_12, OUTPUT_50MHz, AF_OUTPUT_PP, DUMMY_ARG);
        GPIO_Init(GPIOD, GPIO_PIN_2, INPUT_MODE, INPUT_PULL,  GPIO_PULL_UP);

    }
}
// USART_CR1  Control Register 1

void USART_Enable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<13);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<13);
    }
}

void USART_ConfigWordLength(USART_TypeDef* USART, uint8_t word_len){
    if(word_len ==  USART_9_BIT_W_LENGTH){
        USART -> CR1 |= (1<<12);
    }
    else if(word_len == USART_8_BIT_W_LENGTH){
        USART -> CR1 &= ~(1<<12);
    }
}

void USART_ConfigWakeUp(USART_TypeDef* USART, uint8_t wakeup_mode){
    if(wakeup_mode== WKU_ADDR_MARK){
        USART -> CR1 |= (1<<11);
    }
    else if(wakeup_mode == WKU_IDLE_LINE){
        USART -> CR1 &= ~(1<<11);
    }
}

void USART_EnableParityControl(USART_TypeDef* USART, uint8_t state){
    if(state==  ENABLE){
        USART -> CR1 |= (1<<10);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<10);
    } 
}

void USART_OddEvenParity(USART_TypeDef* USART, uint8_t state){
    if(state == PARITY_ODD){
        USART -> CR1 |= (1<<9);
    }
    else if(state == PARITY_EVEN){
        USART -> CR1 &= ~(1<<9);
    }    
}

void USART_SetBaudRate(USART_TypeDef* USART, uint32_t baudrate){
    float usartdiv = (float) RCC_GetClock(USART) / (16.0f * baudrate);

    uint32_t mantissa = (uint32_t)usartdiv;
    uint32_t fraction = (uint32_t)((usartdiv - mantissa) * 16 + 0.5f);

    if(fraction == 16){
        mantissa += 1;
        fraction = 0;
    }

    USART->BRR = (mantissa << 4) | (fraction & 0x0F);
}

void USART_Init(USART_TypeDef* USART, USART_Config_t *config){

    USART_EnableClock(USART);

    USART_GPIO_Init(USART);

    queue_init(&uart_tx_queue);
    // 1. Disable USART before config
    USART_Enable(USART, DISABLE);

    // 2. Set baudrate
    USART_SetBaudRate(USART, config->baudrate);

    // 3. Word length
    USART_ConfigWordLength(USART, config->word_length);

    // 4. Stop bits
    USART_ConfigStopBits(USART, config->stop_bits);

    // 5. Parity
    if(config->parity == ENABLE){
        USART_EnableParityControl(USART, ENABLE);
        USART_OddEvenParity(USART, config->parity_type);
    } else {
        USART_EnableParityControl(USART, DISABLE);
    }

    // 6. TX / RX
    USART_Transmitter_Enable(USART, config->mode_tx);
    USART_Receiver_Enable(USART, config->mode_rx);

    // 7. Enable USART
    USART_Enable(USART, ENABLE);
}


// when PE =1 (PARITY ERROR =1) -> raise an interrupt
void USART_ParityError_IntEnable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<8);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<8);
    }
}
// enable interrupt for TXEIE Transmit register empty event
void USART_TXE_IntEnable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<7);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<7);
    }
}

void USART_TC_IntEnable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<6);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<6);
    }
}
void USART_RXNE_IntEnable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<5);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<5);
    }
}

void USART_IDLE_IntEnable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<4);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<4);
    }
}

void USART_Transmitter_Enable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<3);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<3);
    }
}

void USART_Receiver_Enable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<2);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<2);
    }
}

void USART_Receiver_WKU_Mode(USART_TypeDef* USART, uint8_t mode){
    if(mode == RX_MUTE_MODE){
        USART -> CR1 |= (1<<1);
    }
    else if(mode == RX_ACTIVE_MODE){
        USART -> CR1 &= ~(1<<1);
    }
}

void USART_SendBreak(USART_TypeDef* USART){
    USART -> CR1 |= (1<<0);
}




// USART_DR

void USART_WriteData(USART_TypeDef* USART, uint8_t data){
    while((USART -> SR  &(1<<7)) == 0); // wait for TDR to transfer data to shift register

    USART -> DR = data & 0x1FF;
    
}
uint32_t USART_ReadData(USART_TypeDef* USART){
    while((USART -> SR  &(1<<5)) == 0); // wait for RDR to receive data from shift register
    return USART -> DR;
}


void USART_ConfigStopBits(USART_TypeDef* USART,uint8_t stop_bits){
    USART -> CR2  &= ~(0x03<<12);
    USART -> CR2 |= (stop_bits << 12);
}

void USART_ConfigClock(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR2 |= (1 <<11);
    }
    else if(state == DISABLE){
        USART -> CR2 &= ~(1 <<11);
    }
}


void USART_SendBytes(uint8_t* data, uint32_t size){
    for(uint32_t i = 0; i < size; i++){
        enqueue(&uart_tx_queue, (Event*) &data[i]);
    }
}