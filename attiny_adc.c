#include <stdbool.h>
#include "attiny_adc.h"
#include "attiny_slpctrl.h"

volatile bool adc0_done;
uint16_t adc0_result;

void __interrupt_adc0_resrdy(void)
{
    adc0_result = ADC0->RES;
    adc0_done = 1;
}

void adc0_init(void)
{
    ADC0->INTCTRL |= ADC_INTCTRL_RESRDY;
    ADC0->CTRLA = ADC_CTRLA_ENABLE;
}

uint16_t adc0_read(uint8_t pin)
{
    ADC0->MUXPOS = pin;
    adc0_done = 0;
    ADC0->COMMAND = ADC_COMMAND_STCONV;
    slpctrl_standby_until(&adc0_done);
    return adc0_result;
}
