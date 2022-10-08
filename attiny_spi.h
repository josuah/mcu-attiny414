#ifndef ATTINY_SPI_H
#define ATTINY_SPI_H
#include <stdint.h>
#include <stddef.h>

#define SPI0                            ((hw_spi_t *)0x0820)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
#define SPI_CTRLA_DORD                  (0x01u << 6)
#define SPI_CTRLA_MASTER                (0x01u << 5)
#define SPI_CTRLA_SLAVE                 (0x00u << 5)
#define SPI_CTRLA_CLK2X                 (0x01u << 4)
#define SPI_CTRLA_PRESC_Msk             (0x03u << 1)
#define SPI_CTRLA_PRESC_DIV4            (0x00u << 1)
#define SPI_CTRLA_PRESC_DIV16           (0x01u << 1)
#define SPI_CTRLA_PRESC_DIV64           (0x02u << 1)
#define SPI_CTRLA_PRESC_DIV128          (0x03u << 1)
#define SPI_CTRLA_ENABLE                (0x01u << 0)
    volatile uint8_t CTRLB;             // 0x01
#define SPI_CTRLB_BUFEN                 (0x01u << 7)
#define SPI_CTRLB_BUFWR                 (0x01u << 6)
#define SPI_CTRLB_SSD                   (0x01u << 2)
#define SPI_CTRLB_MODE_Msk              (0x03u << 0)
#define SPI_CTRLB_MODE_POSEDGE_SAMPLE   (0x03u << 0)
#define SPI_CTRLB_MODE_POSEDGE_SETUP    (0x02u << 0)
#define SPI_CTRLB_MODE_NEGEDGE_SETUP    (0x01u << 0)
#define SPI_CTRLB_MODE_NEGEDGE_SAMPLE   (0x00u << 0)
    volatile uint8_t INTCTRL;           // 0x02
#define SPI_INTCTRL_RXCIE               (0x01u << 7)
#define SPI_INTCTRL_TXCIE               (0x01u << 6)
#define SPI_INTCTRL_DREIE               (0x01u << 5)
#define SPI_INTCTRL_SSIE                (0x01u << 4)
#define SPI_INTCTRL_IE                  (0x01u << 0)
    volatile uint8_t INTFLAGS;          // 0x03
#define SPI_INTFLAGS_IF                 (0x01u << 7)
#define SPI_INTFLAGS_WRCOL              (0x01u << 6)
#define SPI_INTFLAGS_RXCIF              (0x01u << 7)
#define SPI_INTFLAGS_TXCIF              (0x01u << 6)
#define SPI_INTFLAGS_DREIF              (0x01u << 5)
#define SPI_INTFLAGS_SSIF               (0x01u << 4)
#define SPI_INTFLAGS_BUFOVF             (0x01u << 0)
    volatile uint8_t DATA;              // 0x04
} hw_spi_t;

void __interrupt_spi0_int(void);
void spi0_init(void);
uint8_t spi0_rxtx_byte(uint8_t wval);
void spi0_write(uint8_t const *wbuf, size_t wsz);

#endif
