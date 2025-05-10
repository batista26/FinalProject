#include <msp430.h>
#include "thermistor.h"

volatile unsigned int thermistor_adc_value = 0;  // Stores the ADC reading

void Thermistor_Init(void)
{
    // Configure P1.6 as analog input (A6)
    P1SEL0 |= BIT6;
    P1SEL1 |= BIT6;

    // Disable high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // Configure ADC
    ADCCTL0 |= ADCSHT_2 | ADCON;              // Sample time = 16 ADC clocks, ADC ON
    ADCCTL1 |= ADCSHP;                        // Use sampling timer
    ADCCTL2 &= ~ADCRES;                       // Clear resolution settings
    ADCCTL2 |= ADCRES_2;                      // 12-bit resolution
    ADCMCTL0 = ADCINCH_6 | ADCSREF_1;         // Input channel A6, Vref = 1.5V

    // Enable internal 1.5V reference
    PMMCTL0_H = PMMPW_H;
    PMMCTL2 |= INTREFEN;
    __delay_cycles(400);                      // Allow reference to settle

    ADCIE |= ADCIE0;                          // Enable interrupt for ADCMEM0
}

unsigned int Thermistor_Read(void)
{
    ADCCTL0 |= ADCENC | ADCSC;                // Enable and start ADC conversion
    __bis_SR_register(LPM0_bits | GIE);       // Enter LPM0 with interrupts
    return thermistor_adc_value;
}

// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR(void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADCIV, ADCIV_ADCIFG))
    {
        case ADCIV_ADCIFG:
            thermistor_adc_value = ADCMEM0;                   // Save result
            __bic_SR_register_on_exit(LPM0_bits);             // Exit LPM0
            break;
        default:
            break;
    }
}