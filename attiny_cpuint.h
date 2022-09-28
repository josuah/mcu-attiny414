#ifndef ATTINY_CPUINT_H
#define ATTINY_CPUINT_H
#include <stdint.h>

#define CPUINT ((hw_cpuint_t *)0x0110)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
#define CPUINT_CTRLA_IVSEL              (0x01u << 6)
#define CPUINT_CTRLA_CVT                (0x01u << 5)
#define CPUINT_CTRLA_LVL0RR             (0x01u << 0)
    volatile uint8_t STATUS;            // 0x01
#define CPUINT_STATUS_NMIEX             (0x01u << 7)
#define CPUINT_STATUS_LVL1EX            (0x01u << 1)
#define CPUINT_STATUS_LVL0EX            (0x01u << 0)
    volatile uint8_t LVL0PRI;           // 0x02
    volatile uint8_t LVL1VEC;           // 0x03
} hw_cpuint_t;

#endif
