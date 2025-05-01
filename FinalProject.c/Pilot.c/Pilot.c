#include <msp430.h>
#include "pilot.h"

#define PILOT_PORT_DIR    P5DIR
#define PILOT_PORT_OUT    P5OUT
#define PILOT_PIN         BIT4   // Assuming P5.4 is connected to the Pilot control

void Pilot_Init(void) {
    PILOT_PORT_DIR |= PILOT_PIN;  // Set pin as output
    Pilot_Off();                  // Make sure it's off initially
}

void Pilot_On(void) {
    PILOT_PORT_OUT |= PILOT_PIN; // Set pin high to turn on solenoid
}

void Pilot_Off(void) {
    PILOT_PORT_OUT &= ~PILOT_PIN; // Set pin low to turn off solenoid
}



