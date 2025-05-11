#include <msp430.h>
#include "thermostat.h"

// This sets up the input and output pins
void thermostat_init(void) {
    // Set pin P3.0 as input (this is for the button)
    P3DIR &= ~BIT0;

    // Turn on a pull-up resistor so the input stays high when the button is not pressed
    P3REN |= BIT0;
    P3OUT |= BIT0;

    // Set pin P5.0 as output (this is for the LED)
    P5DIR |= BIT0;

    // Make sure the LED is off to start
    P5OUT &= ~BIT0;
}

// This turns the LED on or off based on the button
void thermostat(void) {
    // Check if the button is pressed (P3.0 is low)
    if ((P3IN & BIT0) == 0) {
        // Turn on the LED (P5.0)
        P5OUT |= BIT0;
    } else {
        // Turn off the LED
        P5OUT &= ~BIT0;
    }
}
