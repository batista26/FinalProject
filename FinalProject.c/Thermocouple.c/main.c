#include <msp430.h>
#include "thermocouple.h"

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    thermocouple_init();       // Initialize ADC and thermocouple setup

    while (1)
    {
        unsigned int temp = thermocouple_read();  // Read thermocouple ADC value
        __no_operation();                         // Place breakpoint here to inspect 'temp'
    }
}

