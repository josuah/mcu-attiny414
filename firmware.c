#include "attiny414.h"

void tcb_example(void)
{
    PORTA->DIRSET = 1 << PIN_TCB_OUT;

    TCB0->CCMP = 0x80FF;
    TCB0->CTRLA = 0
     | TCB_CTRLA_ENABLE;
    TCB0->CTRLB = 0
     | TCB_CTRLB_CCMPEN
     | TCB_CTRLB_CNTMODE_PWM8;
}

void __interrupt_usart0_txc(void)
{
    PORTA->OUT = 0xFF;
}

void __interrupt_usart0_rxc(void)
{
    PORTA->OUT = 0xFF;
}

void __interrupt_usart0_dre(void)
{
    PORTA->OUT = 0xFF;
}

int main(void)
{
    PORTA->DIRSET = 0xFF;
    //PORTA->DIRSET = 1 << PIN_USART_TX;
    //PORTA->DIRCLR = 1 << PIN_USART_RX;

    USART0->BAUD = USART0_BAUD_HZ(9600);
    USART0->CTRLA = 0
     | USART_CTRLA_RXCIE
     | USART_CTRLA_TXCIE
     | USART_CTRLA_DREIE;
    USART0->CTRLB = 0
     | USART_CTRLB_TXEN
     | USART_CTRLB_RXEN;

    __interrupts_enable();

    for (;;) {
        while (!(USART0->STATUS & USART_STATUS_DREIF));
        USART0->TXDATAL = 0x55;
        while (!(USART0->STATUS & USART_STATUS_TXCIF));
    }

    return 0;
}
