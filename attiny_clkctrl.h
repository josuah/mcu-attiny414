#ifndef ATTINY_CLKCTRL_H
#define ATTINY_CLKCTRL_H
#include <stdint.h>

#define CLKCTRL ((hw_clkctrl_t *)0x0060)

typedef struct {
    volatile uint8_t MCLKCTRLA;         // 0x00
#define CLKCTRL_MCLKCTRLA_CLKOUT        (0x01u << 7)
#define CLKCTRL_MCLKCTRLA_CLKSEL_Msk    (0x03u << 0)
#define CLKCTRL_MCLKCTRLA_CLKSEL_Pos              0
#define CLKCTRL_MCLKCTRLA_CLKSEL_OSC20M (0x00u << 0)
#define CLKCTRL_MCLKCTRLA_CLKSEL_OSCULP32K (0x01u << 0)
#define CLKCTRL_MCLKCTRLA_CLKSEL_XOSC32K (0x02u << 0)
#define CLKCTRL_MCLKCTRLA_CLKSEL_EXTCLK (0x03u << 0)
    volatile uint8_t MCLKCTRLB;         // 0x01
#define CLKCTRL_MCLKCTRLB_PDIV_Msk      (0x0Fu << 1)
#define CLKCTRL_MCLKCTRLB_PDIV_Pos                1
#define CLKCTRL_MCLKCTRLB_PEN           (0x01u << 0)
    volatile uint8_t MCLKLOCK;          // 0x02
#define CLKCTRL_MCLKLOCK_LOCKEN         (0x01u << 0)
    volatile uint8_t MCLKSTATUS;        // 0x03
#define CLKCTRL_MCLKSTATUS_EXTS           (0x01u << 7)
#define CLKCTRL_MCLKSTATUS_XOSC32KS       (0x01u << 6)
#define CLKCTRL_MCLKSTATUS_OSC32KS        (0x01u << 5)
#define CLKCTRL_MCLKSTATUS_OSC20MS        (0x01u << 4)
#define CLKCTRL_MCLKSTATUS_SOSC           (0x01u << 0)
    volatile uint8_t RESERVED0[0x0F - 0x03];
    volatile uint8_t OSC20MCTRLA;       // 0x10
    volatile uint8_t OSC20MCALIBA;      // 0x11
    volatile uint8_t OSC20MCALIBB;      // 0x12
    volatile uint8_t RESERVED1[0x17 - 0x12];
    volatile uint8_t OSC32KCTRLA;       // 0x18
    volatile uint8_t RESERVED2[0x1B - 0x18];
    volatile uint8_t XOSC32KCTRLA;      // 0x1C
} hw_clkctrl_t;

void clkctrl_set_osculp32k(void);

#endif
