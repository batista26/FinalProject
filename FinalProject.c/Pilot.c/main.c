#include <msp430.h>
#include "pilot.h"

void delay(unsigned int ms);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    Pilot_Init();

    while (1) {
        Pilot_On();             // Turn on solenoid
        delay(1000);            // Delay ~1 second

        Pilot_Off();            // Turn off solenoid
        delay(1000);            // Delay ~1 second
    }
}

// Simple delay function (approximate millisecond delay)
void delay(unsigned int ms) {
    while (ms--) {
        __delay_cycles(1000); // Assuming 1 MHz clock
    }
}
