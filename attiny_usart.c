#include <stdbool.h>
#include "attiny_usart.h"
#include "attiny_config.h"

static uint8_t const *usart0_buf;
static size_t usart0_sz;
static volatile bool usart0_done;

void usart0_init(void)
{
    USART0->BAUD = USART_BAUD_HZ(USART0_BAUD_HZ);
    USART0->CTRLA = 0;
    // USART_CTRLA_RXCIE not enabled for now.
    USART0->CTRLB = 0
     | USART_CTRLB_TXEN;
    // USART_CTRLB_RXEN not enabled for now.
}

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

void usart0_write(uint8_t const *buf, size_t sz)
{
    usart0_buf = buf;
    usart0_sz = sz;
    usart0_done = 0;
    USART0->CTRLA |= USART_CTRLA_DREIE;
    while (!usart0_done);
}
