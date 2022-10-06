#ifndef ATTINY_BOD_H
#define ATTINY_BOD_H

#define BOD ((hw_bod_t *)0x0080)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
#define BOD_CTRLA_SAMPFREQ              (0x01u << 4)
#define BOD_CTRLA_ACTIVE_Pos                      2
#define BOD_CTRLA_ACTIVE_Msk            (0x03u << 2)
#define BOD_CTRLA_SLEEP_Pos                       0
#define BOD_CTRLA_SLEEP_Msk             (0x03u << 0)
    volatile uint8_t CTRLB;             // 0x01
#define BOD_CTRLB_LVL_Pos                         0
#define BOD_CTRLB_LVL_Msk               (0x07u << 0)
    volatile uint8_t RESERVED0[0x08 - 0x02];
    volatile uint8_t VLMCTRLA;          // 0x08
#define BOD_VMCTRLA_VLMLVL_Pos                    1
#define BOD_VMCTRLA_VLMLVL_Msk          (0x03u << 1)
    volatile uint8_t INTCTRL;           // 0x09
#define BOD_INTCTRL_VLMCFG_Pos                    1
#define BOD_INTCTRL_VLMCFG_Msk          (0x03u << 1)
#define BOD_INTCTRL_VLMIE               (0x01u << 0)
    volatile uint8_t INTFLAGS;          // 0x0A
#define BOD_INTCTRL_VLMIF               (0x01u << 0)
    volatile uint8_t STATUS;            // 0x0B
#define BOD_INTCTRL_VLMS                (0x01u << 0)
} hw_bod_t;

#endif
