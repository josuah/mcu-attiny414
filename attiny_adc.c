#include <stdbool.h>
#include "attiny_adc.h"
#include "attiny_port.h"

volatile bool adc0_done;
uint16_t adc0_result;

void adc0_init(void)
{
    ADC0->INTCTRL |= ADC_INTCTRL_RESRDY;
    ADC0->CTRLA = 0
     | ADC_CTRLA_ENABLE;
}

uint16_t adc0_read(void)
{
    adc0_done = 0;
    ADC0->COMMAND = ADC_COMMAND_STCONV;
    while (!adc0_done);
    return adc0_result;
}

void __interrupt_adc0_resrdy(void)
{
    adc0_result = ADC0->RES;
    adc0_done = 1;
}
