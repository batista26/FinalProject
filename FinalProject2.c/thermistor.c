#include <msp430.h>
#include "thermistor.h"

// Global variable to store the most recent ADC conversion result
volatile static uint16_t thermistor_ADC_Result = 0;

// Initializes the GPIO pin and ADC settings for thermistor input (P1.6 -> A6)
void therm_Init(void)
{
    // Configure P1.6 as ADC input (A6)
    P1SEL0 |= BIT6;
    P1SEL1 |= BIT6;

    // Disable the GPIO power-on default high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // Configure internal reference voltage
    PMMCTL0_H = PMMPW_H;         // Unlock power management module
    PMMCTL2 |= INTREFEN;         // Enable internal 1.5V reference
    __delay_cycles(400);         // Allow reference to settle

    // Configure ADC settings
    ADCCTL0 |= ADCSHT_2 | ADCON; // ADC ON, sample-and-hold time = 16 ADC clocks
    ADCCTL1 |= ADCSHP;           // Use sampling timer
    ADCCTL2 &= ~ADCRES;          // Set to 8-bit resolution
    ADCMCTL0 |= ADCINCH_6 | ADCSREF_1; // Input channel A6, reference = 1.5V
    ADCIE |= ADCIE0;             // Enable ADC interrupt
}

// Returns the latest thermistor ADC result
uint16_t therm_GetResult(void)
{
    return thermistor_ADC_Result;
}

// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADCIV, ADCIV_ADCIFG))
    {
        case ADCIV_ADCIFG:
            thermistor_ADC_Result = ADCMEM0;          // Store conversion result
            __bic_SR_register_on_exit(LPM0_bits);     // Exit low power mode
            break;
        default:
            break;
    }
}
