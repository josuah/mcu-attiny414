#include "attiny_clkctrl.h"
#include "attiny_crt.h"
#include "attiny_cpu.h"

void clkctrl_set_osculp32k(void)
{
    // Make sure the new clock is stable before switching to it.
    while (!(CLKCTRL->MCLKSTATUS & CLKCTRL_MCLKSTATUS_OSC32KS));
    // Set the new clock value after unlocking the register.
    __protected_write(&CLKCTRL->MCLKCTRLA, CLKCTRL_MCLKCTRLA_CLKSEL_OSCULP32K);
    // Wait completion of the ongoing clock transfer.
    while (CLKCTRL->MCLKSTATUS & CLKCTRL_MCLKSTATUS_SOSC);
}

void clkctrl_set_osc20m(void)
{
    // Make sure the new clock is stable before switching to it.
    while (!(CLKCTRL->MCLKSTATUS & CLKCTRL_MCLKSTATUS_OSC20MS));
    // Set the new clock value after unlocking the register.
    __protected_write(&CLKCTRL->MCLKCTRLA, CLKCTRL_MCLKCTRLA_CLKSEL_OSC20M);
    // Wait completion of the ongoing clock transfer.
    while (CLKCTRL->MCLKSTATUS & CLKCTRL_MCLKSTATUS_SOSC);
}
