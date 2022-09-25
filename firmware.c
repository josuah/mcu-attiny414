#include "attiny414.h"

int main(void) {
    for (;;) {
        PORTA->DIRSET = 0xFF;
        PORTA->OUTSET = 0xFF;
    }
    return 0;
}
