#ifndef ATTINY_SLPCTRL_H
#define ATTINY_SLPCTRL_H
#include <stdint.h>

#define SLPCTRL ((hw_slpctrl_t *)0x0050)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00
#define SLPCTRL_CTRLA_SMODE_Pos         (0x03u << 1)
#define SLPCTRL_CTRLA_SMODE_Msk                   1
#define SLPCTRL_CTRLA_SMODE_IDLE        (0x00u << 1)
#define SLPCTRL_CTRLA_SMODE_STANDBY     (0x01u << 1)
#define SLPCTRL_CTRLA_SMODE_PDOWN       (0x01u << 1)
#define SLPCTRL_CTRLA_SEN               (0x01u << 0)
} hw_slpctrl_t;

void slpctrl_standby(void);

#endif
