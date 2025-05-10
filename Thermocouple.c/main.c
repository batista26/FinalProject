#include <msp430.h>

volatile unsigned int thermocouple_ADC_Result = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    // Configure P1.3 as ADC input (A3)
    P1SEL0 |= BIT3;
    P1SEL1 |= BIT3;

    // Disable the GPIO power-on default high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // Configure internal reference voltage (1.5V)
    PMMCTL0_H = PMMPW_H;        // Unlock PMM registers
    PMMCTL2 |= INTREFEN;        // Enable internal reference
    __delay_cycles(400);        // Allow reference to settle

    // Configure ADC
    ADCCTL0 |= ADCSHT_2 | ADCON;             // ADC ON, sampling time = 16 ADC clocks
    ADCCTL1 |= ADCSHP;                       // Use sampling timer
    ADCCTL2 &= ~ADCRES;                      // Clear resolution bits
    ADCCTL2 |= ADCRES_2;                     // 12-bit resolution
    ADCMCTL0 |= ADCINCH_3 | ADCSREF_1;       // Channel A3 (P1.3), Vref = 1.5V
    ADCIE |= ADCIE0;                         // Enable ADC interrupt

    while(1)
    {
        ADCCTL0 |= ADCENC | ADCSC;           // Enable and start conversion
        __bis_SR_register(LPM0_bits | GIE);  // Enter LPM0 with interrupts enabled
        __no_operation();                    // For debug
    }
}

// ADC ISR
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
            thermocouple_ADC_Result = ADCMEM0;           // Read result
            __bic_SR_register_on_exit(LPM0_bits);        // Exit LPM0
            break;
        default:
            break;
    }
}