#include <msp430.h>
#include "thermostat.h"

int main(void) {
    // Turn off the watchdog timer so it doesn't reset the program
    WDTCTL = WDTPW | WDTHOLD;

    // Set up the thermostat (pins and settings)
    thermostat_init();

    // Keep checking the thermostat forever
    while (1) {
        // Run the thermostat code
        thermostat();

        // Wait a short time before checking again
        __delay_cycles(10000);
    }
}
