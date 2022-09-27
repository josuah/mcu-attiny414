#include <stdint.h>

#ifndef ATTINY414_H
#define ATTINY414_H

#define PIN_USART_TX 1 // PORTA
#define PIN_USART_RX 2 // PORTA

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
#define USART_RXDATAH_RXCIF             (0x01u << 7)
#define USART_RXDATAH_BUFOVF            (0x01u << 6)
#define USART_RXDATAH_FERR              (0x01u << 2)
#define USART_RXDATAH_PERR              (0x01u << 1)
#define USART_RXDATAH_DATA8             (0x01u << 0)
    volatile uint8_t TXDATAL;           // 0x02
    volatile uint8_t TXDATAH;           // 0x03
#define USART_TXDATAH_DATA8             (0x01u << 0)
    volatile uint8_t STATUS;            // 0x04
#define USART_STATUS_RXCIF              (0x01u << 7)
#define USART_STATUS_TXCIF              (0x01u << 6)
#define USART_STATUS_DREIF              (0x01u << 5)
#define USART_STATUS_RXSIF              (0x01u << 4)
#define USART_STATUS_ISFIF              (0x01u << 3)
#define USART_STATUS_BDF                (0x01u << 1)
#define USART_STATUS_WFB                (0x01u << 0)
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
#define USART_CTRLB_RXEN                (0x01 << 7)
#define USART_CTRLB_TXEN                (0x01 << 6)
#define USART_CTRLB_SFDEN               (0x01 << 4)
#define USART_CTRLB_ODME                (0x01 << 3)
#define USART_CTRLB_RXMODE_Msk          (0x03 << 1)
#define USART_CTRLB_RXMODE_Pos                   1
#define USART_CTRLB_MPCM                (0x01 << 0)
    volatile uint8_t CTRLC;             // 0x07
#define USART_CTRLC_CMODE_Msk           (0x03u << 6)
#define USART_CTRLC_CMODE_Pos                     6
#define USART_CTRLC_PMODE_Msk           (0x03u << 4)
#define USART_CTRLC_PMODE_Pos                     4
#define USART_CTRLC_SBMODE              (0x01u << 3)
#define USART_CTRLC_CHSIZE_Msk          (0x07u << 0)
#define USART_CTRLC_CHSIZE_Pos                    0
    volatile uint8_t BAUD;              // 0x08
    volatile uint8_t RESERVED0[0x0B - 0x0A];
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

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
    volatile uint8_t CTRLB;             // 0x01
    volatile uint8_t CTRLC;             // 0x02
    volatile uint8_t CTRLD;             // 0x03
    volatile uint8_t CTRLE;             // 0x04
    volatile uint8_t RESERVED0[0x07 - 0x04];
    volatile uint8_t EVCTRLA;           // 0x08
    volatile uint8_t EVCTRLB;           // 0x09
    volatile uint8_t RESERVED1[0x0B - 0x09];
    volatile uint8_t INTCTRL;           // 0x0C
    volatile uint8_t INTFLAGS;          // 0x0D
    volatile uint8_t STATUS;            // 0x0E
    volatile uint8_t RESERVED2[0x10 - 0x0F];
    volatile uint8_t INPUTCTRLA;        // 0x10
    volatile uint8_t INPUTCTRLB;        // 0x11
    volatile uint8_t FAULTCTRL;         // 0x12
    volatile uint8_t RESERVED[0x14 - 0x13];
    volatile uint8_t DLYCTRL;           // 0x14
    volatile uint8_t DLYVAL;            // 0x15
    volatile uint8_t RESERVED3[0x18 - 0x16];
    volatile uint8_t DITCTRL;           // 0x18
    volatile uint8_t DITVAL;            // 0x19
    volatile uint8_t RESERVED4[0x1E - 0x1A];
    volatile uint8_t DBGCTRL;           // 0x1E
    volatile uint8_t RESERVED5[0x22 - 0x1F];
    volatile uint8_t CAPTUREA;          // 0x22
    volatile uint8_t CAPTUREB;          // 0x24
    volatile uint8_t RESERVED6[0x28 - 0x26];
    volatile uint8_t CMPASET;           // 0x28
    volatile uint8_t CMPACLR;           // 0x2A
    volatile uint8_t CMPBSET;           // 0x2C
    volatile uint8_t CMPBCLR;           // 0x2E
} hw_tca_t;
#define TCA0 ((hw_tca_t *)0x0A00)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
#define TCB_CTRLA_RUNSTDBY              (0x01u << 6)
#define TCB_CTRLA_SYNCUPD               (0x01u << 4)
#define TCB_CTRLA_CLKSEL_Msk            (0x03u << 1)
#define TCB_CTRLA_CLKSEL_Pos                      1
#define TCB_CTRLA_ENABLE                (0x01u << 0)
    volatile uint8_t CTRLB;             // 0x01
#define TCB_CTRLB_ASYNC                 (0x01u << 6)
#define TCB_CTRLB_CCMPINT               (0x01u << 5)
#define TCB_CTRLB_CCMPEN                (0x01u << 4)
#define TCB_CTRLB_CNTMODE_Msk           (0x07u << 0)
#define TCB_CTRLB_CNTMODE_Pos                     0
    volatile uint8_t RESERVED0[0x04 - 0x02];
    volatile uint8_t EVCTRL;            // 0x04
#define TCB_EVCTRL_FILTER               (0x01u << 6)
#define TCB_EVCTRL_EDGE                 (0x01u << 4)
#define TCB_EVCTRL_CAPTEI               (0x01u << 0)
    volatile uint8_t INTCTRL;           // 0x05
#define TCB_INTCTRL_CAPT                (0x01u << 0)
    volatile uint8_t INTFLAGS;          // 0x06
#define TCB_INTFLAGS_CAPT               (0x01u << 0)
    volatile uint8_t STATUS;            // 0x07
#define TCB_STATUS_RUN                  (0x01u << 0)
    volatile uint8_t DBGCTRL;           // 0x08
#define TCB_DBGCTRL_DBGRUN              (0x01u << 0)
    volatile uint8_t TEMP;              // 0x09
    volatile uint16_t CNT;              // 0x0A
    volatile uint16_t CCMP;             // 0x0C
} hw_tcb_t;
#define TCB0 ((hw_tcb_t *)0x0A40)

#endif
