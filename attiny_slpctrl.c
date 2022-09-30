#include "attiny_slpctrl.h"
#include "attiny_crt.h"

void slpctrl_standby(void)
{
    SLPCTRL->CTRLA = 0
     | SLPCTRL_CTRLA_SMODE_STANDBY
     | SLPCTRL_CTRLA_SEN;
    __sleep();
}
