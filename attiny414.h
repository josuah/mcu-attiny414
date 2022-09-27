#include <stdint.h>

#ifndef ATTINY104_H
#define ATTINY104_H

#ifndef CLK_MAIN_KHZ
#define CLK_MAIN_KHZ 16000
#endif

#ifndef CLK_PER_KHZ
#define CLK_PER_KHZ 2666
#endif

// In crt.S:
void __sei(void);
void __clk(void);

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
    volatile uint8_t PINCTRL[8];        // 0x0F
} hw_port_t;
#define PORTA ((hw_port_t *)0x0400)
#define PORTB ((hw_port_t *)0x0420)
#define PORTC ((hw_port_t *)0x0440)

typedef struct {
    volatile uint8_t RXDATAL;           // 0x00
    volatile uint8_t RXDATAH;           // 0x01
    volatile uint8_t TXDATAL;           // 0x02
    volatile uint8_t TXDATAH;           // 0x03
    volatile uint8_t STATUS;            // 0x04
#define USART_STATUS_RXCIF              (0x01u << 7)
#define USART_STATUS_TXCI               (0x01u << 6)
#define USART_STATUS_DREI               (0x01u << 5)
#define USART_STATUS_RXSI               (0x01u << 4)
#define USART_STATUS_ISFI               (0x01u << 3)
#define USART_STATUS_BD                 (0x01u << 1)
#define USART_STATUS_WF                 (0x01u << 0)
    volatile uint8_t CTRLA;             // 0x05
#define USART_CTRLA_RXCIE               (0x01u << 7)
#define USART_CTRLA_TXCIE               (0x01u << 6)
#define USART_CTRLA_DREIE               (0x01u << 5)
#define USART_CTRLA_RXSIE               (0x01u << 4)
#define USART_CTRLA_LBME                (0x01u << 3)
#define USART_CTRLA_ABEIE               (0x01u << 2)
#define USART_CTRLA_RS485_Msk           (0x03u << 0)
#define USART_CTRLA_RS485_Pos                     0
    volatile uint8_t CTRLB;             // 0x06
#define USART_CTRLB_RXEN                (0x01u << 7)
#define USART_CTRLB_TXEN                (0x01u << 6)
#define USART_CTRLB_SFDEN               (0x01u << 4)
#define USART_CTRLB_ODME                (0x01u << 3)
#define USART_CTRLB_RXMODE_Msk          (0x01u << 1)
#define USART_CTRLB_RXMODE_Pos                    1
#define USART_CTRLB_MPCM                (0x01u << 0)
    volatile uint8_t CTRLC;             // 0x07
#define USART_CTRLC_CMODE_Msk           (0x03u << 6)
#define USART_CTRLC_CMODE_Pos                     6
#define USART_CTRLC_PMODE_Msk           (0x03u << 4)
#define USART_CTRLC_PMODE_Pos                     4
#define USART_CTRLC_SBMODE              (0x01u << 3)
#define USART_CTRLC_CHSIZE_Msk          (0x07u << 0)
#define USART_CTRLC_CHSIZE_Pos                    0
    volatile uint16_t BAUD;             // 0x08
    volatile uint8_t RESERVED0[0x0A - 0x09];
    volatile uint8_t DBGCTRL;           // 0x0B
#define USART_DBGCTRL_DBGRUN            (0x01u << 0)
    volatile uint8_t EVCTRL;            // 0x0C
#define USART_EVCTRL_IREI               (0x01u << 0)
    volatile uint8_t TXPLCTRL;          // 0x0D
    volatile uint8_t RXPLCTRL;          // 0x0E
} hw_usart_t;
#define USART0 ((hw_usart_t *)0x0800)

typedef struct {
    volatile uint8_t MCLKCTRLA;         // 0x00
#define CLKCTRL_MCLKCTRLA_CLKOUT        (0x01u << 7)
#define CLKCTRL_MCLKCTRLA_CLKSEL_Msk    (0x03u << 0)
#define CLKCTRL_MCLKCTRLA_CLKSEL_Pos              0
    volatile uint8_t MCLKCTRLB;         // 0x01
#define CLKCTRL_MCLKCTRLB_PDIV_Msk      (0x0Fu << 1)
#define CLKCTRL_MCLKCTRLB_PDIV_Pos                1
#define CLKCTRL_MCLKCTRLB_PEN           (0x01u << 0)
    volatile uint8_t MCLKLOCK;          // 0x02
#define CLKCTRL_MCLKLOCK_LOCKEN         (0x01u << 0)
    volatile uint8_t MCLKSTATUS;        // 0x03
#define CLKCTRL_MCLKLOCK_EXTS           (0x01u << 7)
#define CLKCTRL_MCLKLOCK_XOSC32KS       (0x01u << 6)
#define CLKCTRL_MCLKLOCK_OSC32KS        (0x01u << 5)
#define CLKCTRL_MCLKLOCK_OSC20MS        (0x01u << 4)
#define CLKCTRL_MCLKLOCK_SOSC           (0x01u << 0)
    volatile uint8_t RESERVED0[0x0F - 0x03];
    volatile uint8_t OSC20MCTRLA;       // 0x10
    volatile uint8_t OSC20MCALIBA;      // 0x11
    volatile uint8_t OSC20MCALIBB;      // 0x12
    volatile uint8_t RESERVED1[0x17 - 0x12];
    volatile uint8_t OSC32KCTRLA;       // 0x18
    volatile uint8_t RESERVED2[0x1B - 0x18];
    volatile uint8_t XOSC32KCTRLA;      // 0x1C
} hw_clkctrl_t;
#define CLKCTRL ((hw_clkctrl_t *)0x0060)

#endif
