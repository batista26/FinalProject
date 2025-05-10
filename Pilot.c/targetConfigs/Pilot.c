#include "pilot.h"
#include <msp430.h>  // Adjust based on your MCU

void pilot_Init(void) {
    // Set P5.4 as output
    P5DIR |= BIT4;     // Set bit 4 of Port 5 Direction Register
    P5OUT &= ~BIT4;    // Make sure the pin starts LOW (pilot light OFF)
}

void pilot_On(void) {
    // Set P5.4 high
    P5OUT |= BIT4;
}

void pilot_Off(void) {
    // Set P5.4 low
    P5OUT &= ~BIT4;
}