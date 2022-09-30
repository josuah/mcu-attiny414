#ifndef ATTINY_CPU_H
#define ATTINY_CPU_H
#include <stdint.h>

#define CPU ((hw_cpu_t *)0x0030)

typedef struct {
    volatile uint8_t RESERVED0[0x04 - 0x00];
    volatile uint8_t CCP;               // 0x04
#define CPU_CCP_CCP_SPM                 (0x9Du << 0)
#define CPU_CCP_CCP_IOREG               (0xD8u << 0)
    volatile uint8_t RESERVED1[0x0D - 0x05];
    volatile uint16_t SP;               // 0x0D
    volatile uint8_t SREG;              // 0x0F
#define CPU_SREG_I                      (0x01u << 7)
#define CPU_SREG_T                      (0x01u << 6)
#define CPU_SREG_H                      (0x01u << 5)
#define CPU_SREG_S                      (0x01u << 4)
#define CPU_SREG_V                      (0x01u << 3)
#define CPU_SREG_N                      (0x01u << 2)
#define CPU_SREG_Z                      (0x01u << 1)
#define CPU_SREG_C                      (0x01u << 0)
} hw_cpu_t;

#endif
