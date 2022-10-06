#include "attiny_slpctrl.h"
#include "attiny_crt.h"

void slpctrl_standby(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_STANDBY
     | SLPCTRL_CTRLA_SEN;
    __sleep_until_interrupt();
}

void slpctrl_powerdown(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_PDOWN
     | SLPCTRL_CTRLA_SEN;
    __sleep_until_interrupt();
}

void slpctrl_idle(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_IDLE
     | SLPCTRL_CTRLA_SEN;
    __sleep_until_interrupt();
}

void slpctrl_standby_until(volatile bool *flag)
{
    for (;;) {
        __interrupts_off();
        if (*flag)
            break;
        slpctrl_standby();
    }
    __interrupts_on();
}

void slpctrl_idle_until(volatile bool *flag)
{
    for (;;) {
        __interrupts_off();
        if (*flag)
            break;
        slpctrl_idle();
    }
    __interrupts_on();
}
