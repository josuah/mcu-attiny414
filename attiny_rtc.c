#include "attiny_rtc.h"
#include "attiny_clkctrl.h"

#include "attiny_port.h"

void __interrupt_rtc_pit(void)
{
    PORTB->DIRSET = 1 << 0;
    PORTB->OUT ^= 1 << 0;
    RTC->PITINTFLAGS = RTC_PITINTFLAGS_PI;
}

void rtc_init_periodic_interrupt(void)
{
    // Use the ultra-low-power clock.
    RTC->CLKSEL = RTC_CLKSEL_CLKSEL_INT1K;
    // Run in standby mode.
    RTC->CTRLA = 0
     | RTC_CTRLA_RUNSTDBY
     | RTC_CTRLA_RTCEN;
    // Periodic interrupt with lowest rate.
    RTC->PITCTRLA = 0
     | RTC_CYCLES_BEFORE_INTERRUPT
     | RTC_PITCTRLA_PITEN;
    // Enable this slow interrupt right away.
    RTC->PITINTCTRL = 0
     | RTC_PITINTCTRL_PI;
    // Wait for configuration synchronisation.
    while (RTC->PITSTATUS & RTC_PITSTATUS_CTRLBUSY);
}
