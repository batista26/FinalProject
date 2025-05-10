#include <msp430.h>
#include "potentiometer.h"

#define POT_PIN BIT5  // P1.5 is the analog input pin for the potentiometer

void adc_init(void)
{
    // Set P1.5 as an analog input (Potentiometer pin)
    P1DIR &= ~POT_PIN;     // Set P1.5 as input
    P1SEL0 |= POT_PIN;     // Enable analog function
    P1SEL1 |= POT_PIN;

    // Configure ADC
    ADCCTL0 = ADCSHT_3 | ADCON;   // Sample and hold time 64 cycles, ADC on
    ADCCTL1 = ADCSHP;             // Use sampling timer
    ADCCTL2 &= ~(ADCRES);
    ADCCTL2 |= ADCRES_2;          // 12-bit resolution
    ADCMCTL0 = ADCINCH_5;         // Channel A5 (P1.5)
    ADCCTL0 |= ADCENC | ADCSC;    // Start conversion
    __delay_cycles(10);
}

unsigned int read_POT(void)
{
    ADCCTL0 |= ADCENC | ADCSC;          // Start conversion
    while (ADCCTL1 & ADCBUSY);          // Wait for completion

    if (ADCCTL0 & ADCIFG)
        ADCCTL0 &= ~ADCIFG;             // Clear flag if set

    return ADCMEM0;
}