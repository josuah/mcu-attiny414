#include <stdbool.h>
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
#define LIM_ISENSE_MONOCLE_CHARGING     0x0100 // 0x0000=0V 0x03FF=VBAT_POS

/**
 * ADC result under which the case battery is too low for charging the Monocle.
 */
#define LIM_VBAT_CASE_DISCHARGED        0x0100 // 0x0000=0V 0x03FF=VREF

/**
 * Deep sleep duration when the case battery is too low for charging the Monocle.
 */
#define LOW_BATTERY_SLEEP_MS            1000

/**
 * Deep sleep duration when the battery is high enough for charging the Monocle.
 */
#define HIGH_BATTERY_SLEEP_MS           1000

#ifndef NDEBUG
#define LOG_DEBUG(msg) { put(msg); put("\r\n"); }
#else
#define LOG_DEBUG(msg)
#endif

static uint32_t sleep_duration_ms;

uint16_t read_adc_isense(void)
{
    uint16_t isense;

    ADC0->MUXPOS = PIN_ISENSE;
    isense = adc0_read();
    LOG_DEBUG(fmtd(isense));
    return isense;
}

/**
 * Read the ISENSE pin voltage and test if a monocle is drawing current.
 * @return True if the monocle is detected.
 */
bool is_monocle_charging(void)
{
    uint16_t isense;

    ADC0->MUXPOS = PIN_ISENSE;
    isense = adc0_read();
    LOG_DEBUG(fmtd(isense));

    if (isense > LIM_ISENSE_MONOCLE_CHARGING) {
        LOG_DEBUG("isense=charging");
        return true;
    } else {
        LOG_DEBUG("isense=none");
        return false;
    }
}

/**
 * Read the VBAT current and test if there is enough battery.
 * @return True if enough battery for charging.
 */
bool is_case_battery_too_low(void)
{
    uint16_t vbat;

    ADC0->MUXPOS = PIN_VBAT_POS;
    vbat = adc0_read();
    LOG_DEBUG(fmtd(vbat));

    if (vbat < LIM_VBAT_CASE_DISCHARGED) {
        LOG_DEBUG("case=charging");
        return true;
    } else {
        LOG_DEBUG("case=charged");
        return false;
    }
}

void buck_turn_off()
{
    LOG_DEBUG("buck=off");
    PORTA->DIRCLR = 1 << PIN_BEN;
}

void buck_turn_on()
{
    LOG_DEBUG("buck=on");
    PORTA->DIRSET = 1 << PIN_BEN;
}

void hibernate_ms(uint32_t ms)
{
    LOG_DEBUG("hibernate");
    for (volatile uint32_t i = 0; i < ms; i++);
}

int main(void)
{
    PORTB->DIRSET = 1 << 2;

    // Input pins.
    PORTA->DIRCLR = 1 << PIN_VBAT_POS;
    PORTA->DIRCLR = 1 << PIN_ISENSE;

    // Output pins.
    PORTB->DIRSET = 0xFF; // 1 << PIN_USART_TX;
    PORTA->DIRSET = 1 << PIN_BEN;
    PORTA->DIRSET = 1 << PIN_MK_CHG_N;

#ifndef NDEBUG
    // UART used only for debug output, disabled with the usual -DNDEBUG.
    usart0_init();
#endif

    // ADC used for all voltage sensing.
    adc0_init();

    // Timer-Counter B used for waking-up the device while sleeping.
    //tcb0_init();

    // Interrupts used by drivers of most peripherals above.
    __interrupts_enable();

    for (;;) {
        if (is_case_battery_too_low()) {
            buck_turn_off();
            sleep_duration_ms = LOW_BATTERY_SLEEP_MS;
        } else {
            buck_turn_on();
            sleep_duration_ms = HIGH_BATTERY_SLEEP_MS;
            PORTA->DIRSET = 1 << PIN_BEN;
            if (!is_monocle_charging())
                buck_turn_off();
        }
        hibernate_ms(sleep_duration_ms);
    }

    return 0;
}
