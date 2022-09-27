ATtiny414 library
=================
In the meantime that AVR-libc reaches everyone, and to take advantage of the grouping of the registers, I am going my own way.

I prefer `STRUCT->REG` to access hardware registers from C, which feels natural and lightweight in the amount of `#define` involved.

Given it is `volatile uint8_t *` all the way, no need to worry about struct packing.

For instance:

```
typedef struct {
    volatile uint8_t DIR;               // 0x00
    volatile uint8_t DIRSET;            // 0x01
    volatile uint8_t DIRCLR;            // 0x02
    volatile uint8_t DIRTGL;            // 0x03
    volatile uint8_t OUT;               // 0x04
    volatile uint8_t OUTSET;            // 0x05
    volatile uint8_t OUTCLR;            // 0x06
    volatile uint8_t OUTTGL;            // 0x07
    volatile uint8_t IN;                // 0x08
    volatile uint8_t INTFLAGS;          // 0x09
    volatile uint8_t RESERVED0[0x0F - 0x0A];
    volatile uint8_t PINCTRL[8];
} hw_port_t;

#define PORTA ((hw_port_t *)0x0400)
#define PORTB ((hw_port_t *)0x0420)
#define PORTC ((hw_port_t *)0x0440)
```
