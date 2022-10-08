#include "attiny_rtc.h"
#include "attiny_clkctrl.h"

#include "attiny_port.h"

void __interrupt_rtc_pit(void)
{
    RTC->PITINTFLAGS = RTC_PITINTFLAGS_PI;
}

void rtc_init_periodic_interrupt(void)
{
    // The RTC can be used internally at startup.
    while (RTC->PITSTATUS & RTC_PITSTATUS_CTRLBUSY);
    while (RTC->STATUS & RTC_STATUS_CTRLBUSY);
    // Use the slowest mode of the ultra-low-power clock.
    RTC->CLKSEL = RTC_CLKSEL_CLKSEL_INT1K;
    // Run in standby mode.
    RTC->CTRLA = RTC_CTRLA_RUNSTDBY | RTC_CTRLA_RTCEN;
    // Periodic interrupt with lowest rate.
    RTC->PITCTRLA = RTC_CONF_CYCLES_BEFORE_IRQ | RTC_PITCTRLA_PITEN;
    // Enable this slow interrupt right away.
    RTC->PITINTCTRL = RTC_PITINTCTRL_PI;
    // Wait for configuration synchronisation.
    while (RTC->PITSTATUS & RTC_PITSTATUS_CTRLBUSY);
}
