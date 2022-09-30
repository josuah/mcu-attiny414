#include "attiny_slpctrl.h"
#include "attiny_crt.h"

void slpctrl_standby(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_STANDBY
     | SLPCTRL_CTRLA_SEN;
    __sleep();
}

void slpctrl_powerdown(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_PDOWN
     | SLPCTRL_CTRLA_SEN;
    __sleep();
}
