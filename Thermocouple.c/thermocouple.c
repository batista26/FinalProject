#include <msp430.h>
#include "Thermocouple.h"

void thermocoupleInit(void)
{
    // Configure P1.3 as ADC input (A3)
    P1SEL0 |= BIT3;
    P1SEL1 |= BIT3;

    // Disable high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // Enable internal 1.5V reference
    PMMCTL0_H = PMMPW_H;
    PMMCTL2 |= INTREFEN;
    __delay_cycles(400); // Wait for reference to settle

    // Configure ADC
    ADCCTL0 |= ADCSHT_2 | ADCON;     // ADC ON, sampling time = 16 ADC clocks
    ADCCTL1 |= ADCSHP;               // Use sampling timer
    ADCCTL2 &= ~ADCRES;              // Clear resolution bits
    ADCCTL2 |= ADCRES_2;             // 12-bit resolution
    ADCIE |= ADCIE0;                 // Enable ADC interrupt
}

unsigned int readThermocouple(void)
{
    ADCMCTL0 = ADCINCH_3 | ADCSREF_1;     // Channel A3 (P1.3), Vref = 1.5V
    ADCCTL0 |= ADCENC | ADCSC;           // Start ADC conversion
    while ((ADCIFG & ADCIFG0) == 0);     // Wait for conversion to finish
    return ADCMEM0;
}