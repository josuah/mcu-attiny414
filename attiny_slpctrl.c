#include "attiny_slpctrl.h"
#include "attiny_crt.h"

void slpctrl_standby(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_STANDBY
     | SLPCTRL_CTRLA_SEN;
    __asm__("sei");
    __asm__("sleep");
}

void slpctrl_powerdown(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_PDOWN
     | SLPCTRL_CTRLA_SEN;
    __asm__("sei");
    __asm__("sleep");
}

void slpctrl_idle(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_IDLE
     | SLPCTRL_CTRLA_SEN;
    __asm__("sei");
    __asm__("sleep");
}

void slpctrl_standby_until(volatile bool *flag)
{
    for (;;) {
        __asm__("cli");
        if (*flag)
            break;
        slpctrl_standby();
    }
    __asm__("sei");
}

void slpctrl_idle_until(volatile bool *flag)
{
    for (;;) {
        __asm__("cli");
        if (*flag)
            break;
        slpctrl_idle();
    }
    __asm__("sei");
}
