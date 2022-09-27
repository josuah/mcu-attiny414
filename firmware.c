#include "attiny414.h"

#define PIN 1

int main(void)
{
    // Test to export the clock.
    CLKCTRL->MCLKCTRLA |= CLKCTRL_MCLKCTRLA_CLKOUT;

    __sei();
    PORTA->DIRSET |= 1u << PIN;
    for (;;) {
        PORTA->OUTSET = 1u << PIN;
        PORTA->OUTCLR = 1u << PIN;
    }
    return 0;
}
