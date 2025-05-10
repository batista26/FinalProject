#include "msp430fr2355.h"
#include <msp430.h>

void initServo() {
    // Configure P2.1 for TB2.1 output
    P2DIR |= BIT1;
    P2SEL0 |= BIT1;
    P2SEL1 &= ~BIT1;

    PM5CTL0 &= ~LOCKLPM5; //unlocks the magic

    // Timer B2 Setup
    TB2CCR0 = 20000 - 1;                  // PWM Period (20ms -> 50Hz)
    TB2CCTL1 = OUTMOD_7;                 // CCR1 reset/set output mode
    TB2CCR1 = 1500;                      // Initial 1.5ms pulse (middle position)
    TB2CTL = TBSSEL__SMCLK | MC__UP | TBCLR; // SMCLK, up mode, clear TBR
}

void setServo(unsigned int pulseWidth) {
    TB2CCR1 = pulseWidth;
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    initServo();
    
    while(1) {
        setServo(1000);         // Move to 0 degrees
        __delay_cycles(1000000);
        setServo(2000);         // Move to 180 degrees
        __delay_cycles(1000000);
        setServo(1500);         // Back to center
        __delay_cycles(1000000);
    }
}