#include <stdbool.h>
#include "attiny_spi.h"
#include "attiny_config.h"
#include "attiny_slpctrl.h"

// Read parameters.
static uint8_t *spi0_rbuf;
static size_t spi0_rsz;
static bool spi0_rdummy;

// Write parameters.
static uint8_t const *spi0_wbuf;
static size_t spi0_wsz;
static bool spi0_wdummy;

// Flag shared between interrupts and main thread.
static volatile bool spi0_done;

static void __interrupt_spi0_rxcif(void)
{
    if (spi0_rdummy) {
        spi0_rbuf[0] = SPI0->DATA;
    } else if (spi0_rsz > 0) {
        *spi0_rbuf++ = SPI0->DATA;
        spi0_rsz--;
    } else {
        SPI0->INTCTRL &= (uint8_t)~SPI_INTCTRL_RXCIE;
    }
}

static void __interrupt_spi0_dreif(void)
{
    if (spi0_wdummy) {
        SPI0->DATA = spi0_wbuf[0];
    } else if (spi0_wsz > 0) {
        SPI0->DATA = *spi0_wbuf++;
        spi0_wsz--;
    } else {
        SPI0->INTCTRL &= (uint8_t)~SPI_INTCTRL_DREIE;
    }
}

void __interrupt_spi0_int(void)
{
    if (SPI0->INTFLAGS & SPI_INTFLAGS_DREIF)
        __interrupt_spi0_dreif();
    if (SPI0->INTFLAGS & SPI_INTFLAGS_RXCIF)
        __interrupt_spi0_rxcif();
    spi0_done = spi0_rsz > 0 || spi0_wsz > 0;
}

void spi0_init(void)
{
    SPI0->CTRLB = SPI_CONF_MODE;
    SPI0->CTRLA = SPI_CONF_MASTER_SLAVE | SPI_CONF_DIV | SPI_CTRLA_ENABLE;
}

void spi0_read_write(uint8_t *rbuf, size_t rsz, uint8_t const *wbuf, size_t wsz)
{
    spi0_done = false;
    spi0_rdummy = false, spi0_rbuf = rbuf, spi0_rsz = rsz;
    spi0_wdummy = false, spi0_wbuf = wbuf, spi0_wsz = wsz;

    SPI0->INTCTRL = SPI_INTCTRL_RXCIE | SPI_INTCTRL_DREIE | SPI_INTCTRL_IE;
    slpctrl_idle_until(&spi0_done);
    SPI0->INTCTRL = 0;
}

void spi0_read(uint8_t *rbuf, size_t rsz, uint8_t wval)
{
    spi0_done = false;
    spi0_rdummy = false, spi0_rbuf = rbuf, spi0_rsz = rsz;
    spi0_wdummy = true, spi0_wbuf = &wval, spi0_wsz = 0;

    SPI0->INTCTRL = SPI_INTCTRL_RXCIE | SPI_INTCTRL_DREIE | SPI_INTCTRL_IE;
    slpctrl_idle_until(&spi0_done);
    SPI0->INTCTRL = 0;
}

void spi0_write(uint8_t const *wbuf, size_t wsz)
{
    uint8_t rval;

    spi0_done = false;
    spi0_rdummy = true, spi0_rbuf = &rval, spi0_rsz = 0;
    spi0_wdummy = false, spi0_wbuf = wbuf, spi0_wsz = wsz;

    SPI0->INTCTRL = SPI_INTCTRL_RXCIE | SPI_INTCTRL_DREIE | SPI_INTCTRL_IE;
    slpctrl_idle_until(&spi0_done);
    SPI0->INTCTRL = 0;
}
