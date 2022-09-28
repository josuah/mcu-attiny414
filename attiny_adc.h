#ifndef ATTINY_ADC_H
#define ATTINY_ADC_H
#include <stdint.h>

#define ADC0 ((hw_adc_t *)0x0600)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
#define ADC_CTRLA_RUNSTDBY              (0x01u << 7)
#define ADC_CTRLA_RESSEL                (0x01u << 2)
#define ADC_CTRLA_FREERUN               (0x01u << 1)
#define ADC_CTRLA_ENABLE                (0x01u << 0)
    volatile uint8_t CTRLB;             // 0x01
#define ADC_CTRLB_SAMPNUM_Msk           (0x07u << 0)
#define ADC_CTRLB_SAMPNUM_Pos                     0
    volatile uint8_t CTRLC;             // 0x02
#define ADC_CTRLC_SAMPCAP               (0x01u << 6)
#define ADC_CTRLC_REFSEL                (0x03u << 4)
#define ADC_CTRLC_PRESC                 (0x07u << 0)
    volatile uint8_t CTRLD;             // 0x03
#define ADC_CTRLD_INITDLY_Msk           (0x07u << 5)
#define ADC_CTRLD_INITDLY_Pos                     5
#define ADC_CTRLD_ASDV                  (0x01u << 4)
#define ADC_CTRLD_SAMPDLY_Msk           (0x07u << 0)
#define ADC_CTRLD_SAMPDLY_Pos                     0
    volatile uint8_t CTRLE;             // 0x04
#define ADC_CTRLE_WINCM_Msk             (0x08u << 0)
#define ADC_CTRLE_WINCM_Pos                       0
    volatile uint8_t SAMPCTRL;          // 0x05
    volatile uint8_t MUXPOS;            // 0x06
#define ADC_MUXPOS_MUXPOS_DAC0          (0x1Cu << 0)
#define ADC_MUXPOS_MUXPOS_INTREF        (0x1Du << 0)
#define ADC_MUXPOS_MUXPOS_TEMSENSE      (0x1Eu << 0)
#define ADC_MUXPOS_MUXPOS_GND           (0x1Fu << 0)
    volatile uint8_t RESERVED0[0x08 - 0x07];
    volatile uint8_t COMMAND;           // 0x08
#define ADC_COMMAND_STCONV              (0x01u << 0)
    volatile uint8_t EVCTRL;            // 0x09
#define ADC_EVCTRL_STARTEI              (0x01u << 0)
    volatile uint8_t INTCTRL;           // 0x0A
#define ADC_INTCTRL_WCMP                (0x01u << 1)
#define ADC_INTCTRL_RESRDY              (0x01u << 0)
    volatile uint8_t INTFLAGS;          // 0x0B
#define ADC_INTFLAGS_WCMP               (0x01u << 1)
#define ADC_INTFLAGS_RESRDY             (0x01u << 0)
    volatile uint8_t DBGCTRL;           // 0x0C
#define ADC_DBGCTRL_DBGRUN              (0x01u << 0)
    volatile uint8_t TEMP;              // 0x0D
    volatile uint8_t RESERVED[0x10 - 0x0E];
    volatile uint16_t RES;              // 0x10
    volatile uint16_t WINLT;            // 0x12
    volatile uint16_t WINHT;            // 0x14
    volatile uint8_t CALIB;             // 0x16
#define ADC_CALIB_DUTYCYC               (0x01u << 0)
} hw_adc_t;

void adc0_init(void);
void adc0_start(void);
uint16_t adc0_read(void);


#endif
