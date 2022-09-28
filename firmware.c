#include "attiny_crt.h"
#include "attiny_usart.h"
#include "attiny_port.h"
#include "attiny_tcb.h"
#include "attiny_adc.h"
#include "put.h"

/**
 * Charging case firmware.
 *
 * This charging case acts as an external battery that charges the Monocle
 * while not in use. It helps with extending the battery life of the Monocle.
 *
 * The ATtiny202 microcontroller in the charging case has the purpose:
 *
 * - of keeping the buck converter turned off as long as there is no Monocle
 *   board present to avoid power leakage when not charging the Monocle.
 *
 * - to refuse to send power to the Monocle if there is not enough voltage left
 *   in the case battery.
 *
 * - Provide an LED indicator for the charge status.
 *
 * @file firmware.c
 */

/**
 * USART log debug output, disabled on production builds.
 * Digital output, active low.
 */
#define PIN_USART_TX                    1 // PORTB

/**
 * Buck converter enable pin. Up when current is measured via ISENSE.
 * Digital output, active high.
 */
#define PIN_BEN                         7 // PORTA

/**
 * Green LED bright when Monocle is charging out of the charging case.
 * Digital output, active low.
 */
#define PIN_MK_CHG_N                    1 // PORTA

/**
 * Positive pin of the case internal battery, high when charged.
 * Analog input.
 */
#define PIN_VBAT_POS                    3 // PORTA

/**
 * A 2 Ohm resistor converts current to .
 * High is current flowing toward the Monocle.
 * Analog input.
 */
#define PIN_ISENSE                      2 // PORTA, analog input

/**
 * ADC result above which a Monocle is considered present and drawing power
 * it uses
 */
#define ADC_RES_ISENSE_LIM              0x0100 // 0x0000=0V 0x03FF=VBAT_POS

/**
 * ADC result under which the charging case is considered discharged.
 */
#define ADC_RES_VBAT_LIM                0x0100 // 0x0000=0V 0x03FF=VREF

#ifndef NDEBUG
#define LOG_DEBUG(str) put(fmtd(str)); put("\r\n");
#else
#define LOG_DEBUG(str)
#endif

uint16_t
read_adc_isense(void)
{
//    ADC0->MUXPOS = PIN_ISENSE;
//    adc0_start();
//    return adc0_read();
}

int main(void)
{
    // Output pins.
    PORTB->DIRSET = 0xFF; // 1 << PIN_USART_TX;
    PORTA->DIRSET = 1 << PIN_BEN;
    PORTA->DIRSET = 1 << PIN_MK_CHG_N;

    // Input pins.
    PORTB->DIRCLR = 1 << PIN_VBAT_POS;
    PORTB->DIRCLR = 1 << PIN_ISENSE;

    // Initialization of peripherals.
    usart0_init();
//    adc0_init();
    __interrupts_enable();

    // Main application loop.
    for (;;) {
        uint16_t isense;

        isense = read_adc_isense();
        LOG_DEBUG(fmtd(isense));
    }

    return 0;
}
