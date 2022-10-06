#ifndef ATTINY_CRT_H
#define ATTINY_CRT_H
#include <stdint.h>

void __protected_write(volatile uint8_t *reg, uint8_t val);
void __interrupts_on(void);
void __interrupts_off(void);
void _exit(int unused);
void __sleep_until_interrupt(void);

#endif
