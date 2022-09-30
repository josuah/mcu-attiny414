#ifndef ATTINY_CONFIG_H
#define ATTINY_CONFIG_H
#include <stdint.h>

/* USART */

/* Compile-time fixed baudrate configuration for the UART0. */
#define USART0_BAUD_HZ                  9600

/* RTC */

/* Number of cycles between two interrupts are triggered. */
#define RTC_CYCLES_BEFORE_INTERRUPT     RTC_PITCTRLA_PERIOD_CYC1024

#endif
