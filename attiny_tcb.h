#ifndef ATTINY_TCB_H
#define ATTINY_TCB_H
#include <stdint.h>

#define TCB0 ((hw_tcb_t *)0x0A40)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
#define TCB_CTRLA_RUNSTDBY              (0x01u << 6)
#define TCB_CTRLA_SYNCUPD               (0x01u << 4)
#define TCB_CTRLA_CLKSEL_Msk            (0x03u << 1)
#define TCB_CTRLA_CLKSEL_Pos                      1
#define TCB_CTRLA_ENABLE                (0x01u << 0)
    volatile uint8_t CTRLB;             // 0x01
#define TCB_CTRLB_ASYNC                 (0x01u << 6)
#define TCB_CTRLB_CCMPINT               (0x01u << 5)
#define TCB_CTRLB_CCMPEN                (0x01u << 4)
#define TCB_CTRLB_CNTMODE_Msk           (0x07u << 0)
#define TCB_CTRLB_CNTMODE_Pos                     0
#define TCB_CTRLB_CNTMODE_INT           (0x00u << 0)
#define TCB_CTRLB_CNTMODE_TIMEOUT       (0x01u << 0)
#define TCB_CTRLB_CNTMODE_CAPT          (0x02u << 0)
#define TCB_CTRLB_CNTMODE_FRQ           (0x03u << 0)
#define TCB_CTRLB_CNTMODE_PW            (0x04u << 0)
#define TCB_CTRLB_CNTMODE_FRQPW         (0x05u << 0)
#define TCB_CTRLB_CNTMODE_SINGLE        (0x06u << 0)
#define TCB_CTRLB_CNTMODE_PWM8          (0x07u << 0)
    volatile uint8_t RESERVED0[0x04 - 0x02];
    volatile uint8_t EVCTRL;            // 0x04
#define TCB_EVCTRL_FILTER               (0x01u << 6)
#define TCB_EVCTRL_EDGE                 (0x01u << 4)
#define TCB_EVCTRL_CAPTEI               (0x01u << 0)
    volatile uint8_t INTCTRL;           // 0x05
#define TCB_INTCTRL_CAPT                (0x01u << 0)
    volatile uint8_t INTFLAGS;          // 0x06
#define TCB_INTFLAGS_CAPT               (0x01u << 0)
    volatile uint8_t STATUS;            // 0x07
#define TCB_STATUS_RUN                  (0x01u << 0)
    volatile uint8_t DBGCTRL;           // 0x08
#define TCB_DBGCTRL_DBGRUN              (0x01u << 0)
    volatile uint8_t TEMP;              // 0x09
    volatile uint16_t CNT;              // 0x0A
    volatile uint16_t CCMP;             // 0x0C
} hw_tcb_t;

#endif
