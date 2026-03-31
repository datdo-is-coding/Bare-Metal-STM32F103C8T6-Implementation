#include "../include/UART_driver.h"


// USART_CR1  Control Register 1

void USART_Enable(USART_TypeDef* USART, uint8_t state){
    if(state == ENABLE){
        USART -> CR1 |= (1<<13);
    }
    else if(state == DISABLE){
        USART -> CR1 &= ~(1<<13);
    }
}

void USART_ConfigWordLength(USART_TypeDef* USART, uitn8_t word_len){
    if(word_len ==  USART_9_BIT_W_LENGTH){
        USART -> CR1 |= (1<<12);
    }
    else if(word_len == USART_8_BIT_W_LENGTH){
        USART -> CR1 &= ~(1<<12);
    }
}

void USART_ConfigWakeUp(USART_TypeDef* USART, uint8_t wakeup_mode){
    if(wakeup_mode==  WKU_IDLE_LINE){
        USART -> CR1 |= (1<<11);
    }
    else if(wakeup_mode == WKU_ADDR_MARK){
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

// Baud rate register

void USART_LoadMantissaVal(USART_TypeDef* USART, uint32_t val){
    if(val>0x0FFF) return;
    USART -> BRR &= ~(0x0FFF<<4);
    USART -> BRR |= (val <<4);
}
void USART_LoadFractionVal(USART_TypeDef* USART, uint8_t val){
    if(val >=0x10) return;
    USART -> BRR &= ~0x0F;
    USART -> BRR |= (val);
}


// USART_DR

void USART_WriteData(USART_TypeDef* USART, uint8_t data){
    while(
    USART -> DR = data & 0x1FF;
    
}
uint32_t USART_ReadData(USART_TypeDef* USART){
    return USART -> DR;
}
