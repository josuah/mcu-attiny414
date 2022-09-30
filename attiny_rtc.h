#ifndef ATTINY_RTC_H
#define ATTINY_RTC_H
#include <stdint.h>
#include "attiny_config.h"

#define RTC ((hw_rtc_t *)0x0140)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
#define RTC_CTRLA_RUNSTDBY              (0x01u << 7)
#define RTC_CTRLA_PRESCALER_Msk         (0x0Fu << 3)
#define RTC_CTRLA_PRESCALER_Pos                   3
#define RTC_CTRLA_RTCEN                 (0x01u << 0)
    volatile uint8_t STATUS;            // 0x01
#define RTC_CTRLA_CMPBUSY               (0x01u << 3)
#define RTC_CTRLA_PERBUSY               (0x01u << 2)
#define RTC_CTRLA_CNTBUSY               (0x01u << 1)
#define RTC_CTRLA_CTRLABUSY             (0x01u << 0)
    volatile uint8_t INTCTRL;           // 0x02
#define RTC_INTCTRL_CMP                 (0x01u << 1)
#define RTC_INTCTRL_OVF                 (0x01u << 0)
    volatile uint8_t INTFLAGS;          // 0x03
#define RTC_INTFLAGS_CMP                (0x01u << 1)
#define RTC_INTFLAGS_OVF                (0x01u << 0)
    volatile uint8_t TEMP;              // 0x04
    volatile uint8_t DBGCTRL;           // 0x05
#define RTC_DBGCTLR_DBGRUN              (0x01u << 0)
    volatile uint8_t RESERVED0[0x07 - 0x06];
    volatile uint8_t CLKSEL;            // 0x07
#define RTC_CLKSEL_CLKSEL_Msk           (0x03u << 0)
#define RTC_CLKSEL_CLKSEL_Pos                     0
#define RTC_CLKSEL_CLKSEL_INT32K        (0x00u << 0)
#define RTC_CLKSEL_CLKSEL_INT1K         (0x01u << 0)
#define RTC_CLKSEL_CLKSEL_TOSC32K       (0x02u << 0)
#define RTC_CLKSEL_CLKSEL_EXTCLK        (0x03u << 0)
    volatile uint16_t CNT;              // 0x08
    volatile uint16_t PER;              // 0x0A
    volatile uint16_t CMP;              // 0x0C
    volatile uint8_t RESERVED1[0x10 - 0x0E];
    volatile uint8_t PITCTRLA;          // 0x10
#define RTC_PITCTRLA_PERIOD_Msk         (0x0Fu << 3)
#define RTC_PITCTRLA_PERIOD_Pos                   3
#define RTC_PITCTRLA_PERIOD_OFF         (0x00u << 3)
#define RTC_PITCTRLA_PERIOD_CYC4        (0x01u << 3)
#define RTC_PITCTRLA_PERIOD_CYC8        (0x02u << 3)
#define RTC_PITCTRLA_PERIOD_CYC16       (0x03u << 3)
#define RTC_PITCTRLA_PERIOD_CYC32       (0x04u << 3)
#define RTC_PITCTRLA_PERIOD_CYC64       (0x05u << 3)
#define RTC_PITCTRLA_PERIOD_CYC128      (0x06u << 3)
#define RTC_PITCTRLA_PERIOD_CYC256      (0x07u << 3)
#define RTC_PITCTRLA_PERIOD_CYC512      (0x08u << 3)
#define RTC_PITCTRLA_PERIOD_CYC1024     (0x09u << 3)
#define RTC_PITCTRLA_PERIOD_CYC2048     (0x0Au << 3)
#define RTC_PITCTRLA_PERIOD_CYC4096     (0x0Bu << 3)
#define RTC_PITCTRLA_PERIOD_CYC8192     (0x0Cu << 3)
#define RTC_PITCTRLA_PERIOD_CYC16384    (0x0Du << 3)
#define RTC_PITCTRLA_PERIOD_CYC32768    (0x0Eu << 3)
#define RTC_PITCTRLA_PITEN              (0x01u << 0)
    volatile uint8_t PITSTATUS;         // 0x11
#define RTC_PITSTATUS_CTRLBUSY          (0x01u << 0)
    volatile uint8_t PITINTCTRL;        // 0x12
#define RTC_PITINTCTRL_PI               (0x01u << 0)
    volatile uint8_t PITINTFLAGS;       // 0x13
#define RTC_PITINTFLAGS_PI              (0x01u << 0)
    volatile uint8_t RESERVED2[0x15 - 0x14];
    volatile uint8_t PITDBGCTRL;        // 0x15
#define RTC_PITDBGCTRL_DBGRUN           (0x01u << 0)
} hw_rtc_t;

void __interrupt_rtc_pit(void);
void rtc_init_periodic_interrupt(void);

#endif
