#include "attiny414.h"

int main(void)
{
    PORTA->DIRSET = 1 << 5;
    PORTA->OUTSET = 1 << 5;

    TCB0->CCMP = 0x80FF;
    TCB0->CTRLA |= TCB_CTRLA_ENABLE;
    TCB0->CTRLB |= TCB_CTRLB_CCMPEN;
    TCB0->CTRLB &= TCB_CTRLB_CNTMODE_Msk;
    TCB0->CTRLB |= 0x07 << TCB_CTRLB_CNTMODE_Pos;
    TCB0->CTRLB |= TCB_CTRLB_CCMPEN;

    return 0;
}
