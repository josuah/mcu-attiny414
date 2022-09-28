#ifndef ATTINY_USART_H
#define ATTINY_USART_H
#include <stdint.h>
#include <stddef.h>
#include "attiny_config.h"

#define USART0 ((hw_usart_t *)0x0800)

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
    volatile uint16_t BAUD;             // 0x08
    volatile uint8_t RESERVED0[0x0B - 0x0A];
    volatile uint8_t DBGCTRL;           // 0x0B
#define USART_DBGCTRL_DBGRUN            (0x01u << 0)
    volatile uint8_t EVCTRL;            // 0x0C
#define USART_EVCTRL_IREI               (0x01u << 0)
    volatile uint8_t TXPLCTRL;          // 0x0D
    volatile uint8_t RXPLCTRL;          // 0x0E
} hw_usart_t;

#define USART_BAUD_HZ(hz) ((float)(3333333 * 64 / (16 * (float)hz)) + 0.5)

void usart0_write(uint8_t const *buf, size_t len);
void usart0_init(void);


#endif
