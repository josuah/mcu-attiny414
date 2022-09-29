#include "attiny_clkctrl.h"
#include "attiny_cpu.h"

void clkctrl_set_osculp32k(void)
{
    CPU->CCP = CPU_CCP_CCP_IOREG;
    CLKCTRL->MCLKCTRLA = CLKCTRL_MCLKCTRLA_CLKSEL_OSCULP32K;
}
