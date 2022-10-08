#include "attiny_vref.h"
#include "attiny_config.h"

void vref_init_adc0(void)
{
    VREF->CTRLA &= (uint8_t) ~VREF_CTRLA_ADC0REFSEL_Msk;
    VREF->CTRLA |= VREF_CONF_ADC0_VOLT;
}
