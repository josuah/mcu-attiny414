#include <stdbool.h>
#include "attiny_spi.h"
#include "attiny_config.h"
#include "attiny_slpctrl.h"

// Read parameters.
static uint8_t spi0_rval;

// Write parameters.
static uint8_t const *spi0_wbuf;
static size_t spi0_wsz;

// Flag shared between interrupts and main thread.
static volatile bool spi0_done;

#include "attiny_port.h"

static inline void __interrupt_spi0_rxcif(void)
{
    spi0_rval = SPI0->DATA;
}

static inline void __interrupt_spi0_dreif(void)
{
    if (spi0_wsz > 0) {
        SPI0->DATA = *spi0_wbuf++;
        spi0_wsz--;
    }
    if (spi0_wsz == 0) {
        SPI0->INTCTRL = 0;
        spi0_done = true;
    }
}

void __interrupt_spi0_int(void)
{
    if (SPI0->INTFLAGS & SPI_INTFLAGS_DREIF)
        __interrupt_spi0_dreif();
    if (SPI0->INTFLAGS & SPI_INTFLAGS_RXCIF)
        __interrupt_spi0_rxcif();
}

void spi0_init(void)
{
    SPI0->CTRLB = SPI_CONF_MODE;
    SPI0->CTRLA = SPI_CTRLA_MASTER | SPI_CTRLA_PRESC_DIV64 | SPI_CTRLA_ENABLE;
}

static inline void spi0_start(void)
{
    spi0_done = false;
    SPI0->INTCTRL = SPI_INTCTRL_RXCIE | SPI_INTCTRL_DREIE | SPI_INTCTRL_IE;
    __interrupt_spi0_dreif();
    slpctrl_idle_until(&spi0_done);
    SPI0->INTCTRL = 0;
}

uint8_t spi0_rxtx_byte(uint8_t wval)
{
    spi0_wbuf = &wval, spi0_wsz = 1;
    spi0_start();
    return spi0_rval;
}

void spi0_write(uint8_t const *wbuf, size_t wsz)
{
    spi0_wbuf = wbuf, spi0_wsz = wsz;
    spi0_start();
}
