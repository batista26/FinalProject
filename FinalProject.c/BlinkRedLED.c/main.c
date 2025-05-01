#include <msp430.h>
#include <driverlib.h>
#include "led.h"

int main(void)
{
    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // Initialize LED
    LED_init();

    while (1)
    {
        // Toggle LED
        LED_toggle();

        // Fixed delay
        for (volatile uint32_t i = 0; i < 10000; i++);
    }
}
