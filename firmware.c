#include "attiny414.h"

uint8_t global = 0xFF;

int main(void)
{
    PORTA->DIR |= 0xFF;
    for (;;) {
        PORTA->OUT = global;
        PORTA->OUT = 0x00;
    }
    return 0;
}
