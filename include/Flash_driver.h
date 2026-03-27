#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H
#include <stdint.h>

#define FLASH ((FLASH_Typedef*) 0x40022000U)
// ACR bits
#define FLASH_ACR_LATENCY_MASK   (0x7 << 0)

#define FLASH_LATENCY_0          (0x0 << 0)
#define FLASH_LATENCY_1          (0x1 << 0)
#define FLASH_LATENCY_2          (0x2 << 0)

#define FLASH_ACR_PRFTBE         (1 << 4)   // Prefetch enable
#define ENABLE                   1
#define DISABLE                  0

typedef struct{
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t AR;
    volatile uint32_t RESERVED;
    volatile uint32_t OBR;
    volatile uint32_t WRPR;
}FLASH_Typedef;

void Flash_SetLatency(uint32_t latency);
void Flash_EnablePrefetch(uint8_t state);

#endif