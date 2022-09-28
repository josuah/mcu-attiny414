#include "attiny_crt.h"
#include "attiny_usart.h"
#include "attiny_port.h"
#include "attiny_tcb.h"

void tcb_example(void)
{
    PORTA->DIRSET = 0xFF;

    TCB0->CCMP = 0x80FF;
    TCB0->CTRLA = 0
     | TCB_CTRLA_ENABLE;
    TCB0->CTRLB = 0
     | TCB_CTRLB_CCMPEN
     | TCB_CTRLB_CNTMODE_PWM8;
}

int main(void)
{
    PORTB->DIRSET = 0xFF;
    usart0_init();

    __interrupts_enable();

    for (;;) {
        usart0_write((uint8_t *)" test", 5);
    }

    return 0;
}
