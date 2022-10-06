#include <stdbool.h>
#include "attiny_crt.h"
#include "attiny_usart.h"
#include "attiny_port.h"
#include "attiny_adc.h"
#include "attiny_rtc.h"
#include "attiny_clkctrl.h"
#include "attiny_slpctrl.h"
#include "put.h"

int main(void)
{
    PORTA->DIRSET = 0xFF;
    PORTA->OUTSET = 0x55;

    // Interrupts used by drivers of most peripherals above.
    __asm__("sei");

    return 0;
}
