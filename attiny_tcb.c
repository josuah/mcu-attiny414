#include "attiny_tcb.h"
#include "attiny_port.h"

void __interrupt_tcb0_int(void)
{
    PORTB->DIRSET = 1 << 0;
    PORTB->OUT ^= 1 << 0;
}

void tcb0_periodic_interrupt(uint16_t ticks)
{
    TCB0->CCMP = ticks;
    TCB0->CTRLA = 0
     | TCB_CTRLA_ENABLE
     | TCB_CTRLA_RUNSTDBY;
    TCB0->CTRLB = 0
     | TCB_CTRLB_CNTMODE_INT;
    TCB0->INTCTRL = 0
     | TCB_INTCTRL_CAPT;
}
