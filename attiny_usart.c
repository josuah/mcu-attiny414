#include "attiny_usart.h"
#include "attiny_config.h"

uint8_t *usart0_buf;
size_t usart0_sz;
volatile int usart0_done;

void __interrupt_usart0_dre(void)
{
    if (usart0_sz > 0) {
        USART0->TXDATAL = *usart0_buf++;
        usart0_sz--;
    } else {
        usart0_done = 1;
        USART0->CTRLB &= ~USART_CTRLA_DREIE;
    }
}

void usart0_init(void)
{
    USART0->BAUD = USART_BAUD_HZ(USART0_BAUD_HZ);
    USART0->CTRLA = 0
     | USART_CTRLA_RXCIE
     | USART_CTRLA_TXCIE;
    USART0->CTRLB = 0
     | USART_CTRLB_TXEN
     | USART_CTRLB_RXEN;
}

void usart0_write(uint8_t *buf, size_t sz)
{
    usart0_buf = buf;
    usart0_sz = sz;
    usart0_done = 0;
    USART0->CTRLA |= USART_CTRLA_DREIE;
    while (!usart0_done);
}
