#include "attiny_tcb.h"

#include "attiny_port.h"

void __interrupt_tcb0_int(void)
{
}

void tcb0_periodic_interrupt(void)
{
    TCB0->CTRLB = TCB_CTRLB_CNTMODE_INT;
    TCB0->INTCTRL = TCB_INTCTRL_CAPT;
    TCB0->CTRLA = TCB_CTRLA_ENABLE | TCB_CTRLA_RUNSTDBY;
}

void tcb0_pwm(void)
{
    TCB0->CTRLB = TCB_CTRLB_CCMPEN;
    TCB0->INTCTRL = 0;
    TCB0->CTRLA = TCB_CTRLA_ENABLE | TCB_CTRLA_RUNSTDBY;
}

void tcb0_off(void)
{
    TCB0->CTRLA &= (uint8_t)~TCB_CTRLA_ENABLE;
}
