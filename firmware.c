#include <stdbool.h>
#include "attiny_spi.h"
#include "attiny_port.h"

int main(void)
{
    PORTA->DIRSET = 0xFF;

    spi0_init();

    // Interrupts used by drivers of most peripherals above.
    __asm__("sei");

    for (;;)
        spi0_rxtx_byte('.');

    return 0;
}
