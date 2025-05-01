#include <msp430.h>
#include "thermocouple.h"

volatile unsigned int thermocouple_result = 0;
static volatile unsigned char adc_done = 0;

void thermocouple_init(void)
{
    // Configure pin P1.0 for analog input (A0)
    P1SEL0 |= BIT0;
    P1SEL1 |= BIT0;
    PM5CTL0 &= ~LOCKLPM5;  // Unlock GPIO

    // Enable internal reference voltage (1.5V)
    PMMCTL0_H = PMMPW_H;
    PMMCTL2 |= INTREFEN;
    __delay_cycles(400);  // Allow time for reference to settle

    // Configure ADC
    ADCCTL0 |= ADCSHT_2 | ADCON;            // 16 ADC clocks, ADC ON
    ADCCTL1 |= ADCSHP;                      // Sample-and-hold pulse mode
    ADCCTL2 &= ~ADCRES;                     // 8-bit resolution
    ADCMCTL0 = ADCINCH_0 | ADCSREF_1;       // Input A0, Vref = internal 1.5V
    ADCIE |= ADCIE0;                        // Enable ADC interrupt
}

unsigned int thermocouple_read(void)
{
    adc_done = 0;

    ADCCTL0 |= ADCENC | ADCSC;              // Enable and start conversion
    while (!adc_done);                      // Wait for ADC completion

    return thermocouple_result;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR(void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(ADCIV, ADCIV_ADCIFG))
    {
        case ADCIV_ADCIFG:
            thermocouple_result = ADCMEM0;
            adc_done = 1;
            break;
        default: break;
    }
}

