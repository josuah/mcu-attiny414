#ifndef ATTINY_CRT_H
#define ATTINY_CRT_H
#include <stdint.h>

void __protected_write(volatile uint8_t *reg, uint8_t val);

#endif
