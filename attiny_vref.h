#ifndef ATTINY_VREF_H
#define ATTINY_VREF_H
#include <stdint.h>

#define VREF ((hw_vref_t *)0x00A0)

typedef struct {
    volatile uint8_t CTRLA;             // 0x00 
#define VREF_CTRLA_ADC0REFSEL_Pos                 4
#define VREF_CTRLA_ADC0REFSEL_Msk       (0x07u << 4)
#define VREF_CTRLA_ADC0REFSEL_0V55      (0x00u << 4)
#define VREF_CTRLA_ADC0REFSEL_1V1       (0x01u << 4)
#define VREF_CTRLA_ADC0REFSEL_2V5       (0x02u << 4)
#define VREF_CTRLA_ADC0REFSEL_4V3       (0x03u << 4)
#define VREF_CTRLA_ADC0REFSEL_1V5       (0x04u << 4)
#define VREF_CTRLA_DAC0REFSEL_Pos                 0
#define VREF_CTRLA_DAC0REFSEL_Msk       (0x07u << 0)
#define VREF_CTRLA_DAC0REFSEL_0V55      (0x00u << 0)
#define VREF_CTRLA_DAC0REFSEL_1V1       (0x01u << 0)
#define VREF_CTRLA_DAC0REFSEL_2V5       (0x02u << 0)
#define VREF_CTRLA_DAC0REFSEL_4V3       (0x03u << 0)
#define VREF_CTRLA_DAC0REFSEL_1V5       (0x04u << 0)
    volatile uint8_t CTRLB;             // 0x01 
#define VREF_CTRLB_ADC0REFEN            (0x01u << 1)
#define VREF_CTRLB_DAC0REFEN            (0x01u << 0)
} hw_vref_t;

void vref_init_adc0(void);

#endif
