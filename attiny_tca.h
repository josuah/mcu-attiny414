#ifndef ATTINY_TCA_H
#define ATTINY_TCA_H
#include <stdint.h>

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
    volatile uint8_t CTRLB;             // 0x01
    volatile uint8_t CTRLC;             // 0x02
    volatile uint8_t CTRLD;             // 0x03
    volatile uint8_t CTRLE;             // 0x04
    volatile uint8_t RESERVED0[0x07 - 0x04];
    volatile uint8_t EVCTRLA;           // 0x08
    volatile uint8_t EVCTRLB;           // 0x09
    volatile uint8_t RESERVED1[0x0B - 0x09];
    volatile uint8_t INTCTRL;           // 0x0C
    volatile uint8_t INTFLAGS;          // 0x0D
    volatile uint8_t STATUS;            // 0x0E
    volatile uint8_t RESERVED2[0x10 - 0x0F];
    volatile uint8_t INPUTCTRLA;        // 0x10
    volatile uint8_t INPUTCTRLB;        // 0x11
    volatile uint8_t FAULTCTRL;         // 0x12
    volatile uint8_t RESERVED[0x14 - 0x13];
    volatile uint8_t DLYCTRL;           // 0x14
    volatile uint8_t DLYVAL;            // 0x15
    volatile uint8_t RESERVED3[0x18 - 0x16];
    volatile uint8_t DITCTRL;           // 0x18
    volatile uint8_t DITVAL;            // 0x19
    volatile uint8_t RESERVED4[0x1E - 0x1A];
    volatile uint8_t DBGCTRL;           // 0x1E
    volatile uint8_t RESERVED5[0x22 - 0x1F];
    volatile uint8_t CAPTUREA;          // 0x22
    volatile uint8_t CAPTUREB;          // 0x24
    volatile uint8_t RESERVED6[0x28 - 0x26];
    volatile uint8_t CMPASET;           // 0x28
    volatile uint8_t CMPACLR;           // 0x2A
    volatile uint8_t CMPBSET;           // 0x2C
    volatile uint8_t CMPBCLR;           // 0x2E
} hw_tca_t;
#define TCA0 ((hw_tca_t *)0x0A00)

#endif
