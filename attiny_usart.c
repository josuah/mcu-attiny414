#include <stdbool.h>
#include "attiny_usart.h"
#include "attiny_config.h"
#include "attiny_slpctrl.h"

static uint8_t const *usart0_buf;
static size_t usart0_sz;
static volatile bool usart0_done;

void __interrupt_usart0_dre(void)
{
    if (usart0_sz > 0) {
        USART0->TXDATAL = *usart0_buf++;
        usart0_sz--;
    } else {
        USART0->CTRLA &= (uint8_t)~USART_CTRLA_DREIE;
    }
}

void __interrupt_usart0_txc(void)
{
    usart0_done = (usart0_sz == 0);
}

void usart0_init(void)
{
    USART0->BAUD = USART_BAUD_HZ(CLK_USART0_HZ);
    USART0->CTRLA = USART_CTRLA_TXCIE;
    USART0->CTRLB = USART_CTRLB_TXEN;
}

void usart0_write(uint8_t const *buf, size_t sz)
{
    usart0_buf = buf;
    usart0_sz = sz;
    usart0_done = 0;
    USART0->CTRLA |= USART_CTRLA_DREIE;
    slpctrl_idle_until(&usart0_done);
}
