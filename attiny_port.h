#ifndef ATTINY_PORT_H
#define ATTINY_PORT_H
#include <stdint.h>

#define PORTA ((hw_port_t *)0x0400)
#define PORTB ((hw_port_t *)0x0420)
#define PORTC ((hw_port_t *)0x0440)

typedef struct {
    volatile uint8_t DIR;               // 0x00
    volatile uint8_t DIRSET;            // 0x01
    volatile uint8_t DIRCLR;            // 0x02
    volatile uint8_t DIRTGL;            // 0x03
    volatile uint8_t OUT;               // 0x04
    volatile uint8_t OUTSET;            // 0x05
    volatile uint8_t OUTCLR;            // 0x06
    volatile uint8_t OUTTGL;            // 0x07
    volatile uint8_t IN;                // 0x08
    volatile uint8_t INTFLAGS;          // 0x09
    volatile uint8_t RESERVED0[0x0F - 0x0A];
    volatile uint8_t PINCTRL[8];        // 0x0F
} hw_port_t;

#endif
