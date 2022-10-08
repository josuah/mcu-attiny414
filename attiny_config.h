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

/* Compile-time fixed baudrate configuration for the UART0. */
#define CLK_USART0_HZ                   9600

// RTC

/* Number of cycles between two interrupts are triggered. */
#define RTC_CONF_CYCLES_BEFORE_IRQ      RTC_PITCTRLA_PERIOD_CYC1024

// VREF

/* Reference voltage used by the ADC. When the measured VIN=VREF then the result ADCRES=ADCMAX. */
#define VREF_CONF_ADC0_VOLT             VREF_CTRLA_ADC0REFSEL_4V3

// SPI

/** Combined Clock Phase (CPHA) and Clock Polarity (CPOL) config. */
#define SPI_CONF_MODE                   SPI_CTRLB_MODE_POSEDGE_SAMPLE

#endif
