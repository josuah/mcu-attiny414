#include "attiny414.h"

#define PIN 1

int main(void)
{
    PORTA->DIRSET = 0xFF;
    PORTA->OUTCLR = 0xFF;

    // Usart
    USART0->BAUD = 5;

    // Counter
    TCB0->CCMP = 1024;
    TCB0->CNT = 1024;
    TCB0->CTRLB |= TCB_CTRLB_CCMPEN;
    TCB0->CTRLB &= TCB_CTRLB_CNTMODE_Msk;
    TCB0->CTRLB |= 0x07 << TCB_CTRLB_CNTMODE_Pos;
    TCB0->CTRLA |= TCB_CTRLA_ENABLE;

    return 0;
}
