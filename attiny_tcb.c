#include "attiny_tcb.h"

void tcb0_wakeup_alarm(uint16_t ticks)
{
    TCB0->CCMP = ticks;
    TCB0->CTRLA = 0
     | TCB_CTRLA_ENABLE
     | TCB_CTRLA_RUNSTDBY;
    TCB0->CTRLB = 0
     | TCB_CTRLB_CNTMODE_SINGLE;
}
