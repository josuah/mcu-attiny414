#ifndef ATTINY_CONFIG_H
#define ATTINY_CONFIG_H
#include <stdint.h>

// CLK

/* Clocks sources, turned on or off, eventually prescaled. */
#define CLK_OSC20M_HZ                   20000000
#define CLK_PER_DIV                     6
#define CLK_OSCULP32K_HZ                32768

/* Values to update by hand when changing the clock configuration. */
#define CLK_MAIN_HZ                     CLK_OSC20M_HZ
#define CLK_PER_HZ                      (CLK_MAIN_HZ / CLK_PER_DIV)

// USART

/* Compile-time fixed baudrate configuration for the UART0. */
#define USART0_BAUD_HZ                  9600

// RTC

/* Number of cycles between two interrupts are triggered. */
#define RTC_CYCLES_BEFORE_INTERRUPT     RTC_PITCTRLA_PERIOD_CYC1024

// VREF

/* Reference voltage used by the ADC. When the measured VIN=VREF then the result ADCRES=ADCMAX. */
#define VREF_VOLTAGE_ADC0               VREF_CTRLA_ADC0REFSEL_4V3

#endif
