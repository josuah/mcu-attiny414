#include "attiny_slpctrl.h"
#include "attiny_crt.h"

void slpctrl_standby(void)
{
    SLPCTRL->CTRLA = SLPCTRL_CTRLA_SEN | SLPCTRL_CTRLA_SMODE_STANDBY;
    __asm__("sei");
    __asm__("sleep");
}

void slpctrl_powerdown(void)
{
    SLPCTRL->CTRLA = SLPCTRL_CTRLA_SEN | SLPCTRL_CTRLA_SMODE_PDOWN;
    __asm__("sei");
    __asm__("sleep");
}

void slpctrl_idle(void)
{
    SLPCTRL->CTRLA = SLPCTRL_CTRLA_SEN | SLPCTRL_CTRLA_SMODE_IDLE;
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
