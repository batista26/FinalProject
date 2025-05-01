#include <msp430.h>
#include <driverlib.h>
#include "potentiometer.h"

int main(void)
{
    WDT_A_hold(WDT_A_BASE); // Stop watchdog

    // Initialize potentiometer (ADC on P1.3)
    Potentiometer_init();

    while (1)
    {
        uint16_t potValue = Potentiometer_readRaw();

        // Simple breakpoint placeholder to inspect value
        __no_operation();  // Place a breakpoint here to see potValue

        // Optional: short delay between reads
        for (volatile uint32_t i = 0; i < 5000; i++);
    }
}
