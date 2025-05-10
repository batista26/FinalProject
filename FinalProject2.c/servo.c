#include <msp430.h>
#include "servo.h"

void initServo() {
    // Configure P2.1 for TB2.1 output (PWM to servo)
    P2DIR |= BIT1;           // Set P2.1 as output
    P2SEL0 |= BIT1;          // Select primary peripheral function for P2.1
    P2SEL1 &= ~BIT1;

    // Unlock GPIOs from high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // Timer B2 setup for PWM
    TB2CCR0 = 20000 - 1;                  // PWM period (20 ms -> 50 Hz)
    TB2CCTL1 = OUTMOD_7;                  // CCR1 in reset/set mode
    TB2CCR1 = 1500;                       // Start at 1.5 ms pulse (neutral)
    TB2CTL = TBSSEL__SMCLK | MC__UP | TBCLR; // SMCLK, up mode, clear timer
}

void setServo(unsigned int pulseWidth) {
    TB2CCR1 = pulseWidth;  // Set pulse width (in microseconds)
}

