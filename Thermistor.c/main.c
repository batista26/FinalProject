#include <msp430.h>

volatile unsigned int ADC_Result = 0;   // Stores the ADC result for thermistor on P1.6 (A6)

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // ------------------ Configure P1.6 for ADC ------------------
    // Set P1.6 as analog input (A6)
    P1SEL0 |= BIT6;
    P1SEL1 |= BIT6;

    // ------------------ Disable high-impedance mode ------------------
    // Required to activate port settings
    PM5CTL0 &= ~LOCKLPM5;

    // ------------------ Configure ADC ------------------
    ADCCTL0 |= ADCSHT_2 | ADCON;         // Sampling time = 16 ADC clocks, ADC ON
    ADCCTL1 |= ADCSHP;                   // Use sampling timer (pulse mode)
    ADCCTL2 &= ~ADCRES;                  // Clear resolution settings
    ADCCTL2 |= ADCRES_2;                 // Set 12-bit resolution (0–4095)
    ADCMCTL0 = ADCINCH_6 | ADCSREF_1;    // Input channel = A6 (P1.6), Vref = internal 1.5V

    // ------------------ Configure internal voltage reference ------------------
    PMMCTL0_H = PMMPW_H;                 // Unlock PMM registers
    PMMCTL2 |= INTREFEN;                 // Enable internal 1.5V reference
    __delay_cycles(400);                 // Wait for reference to stabilize

    // ------------------ Enable ADC interrupt ------------------
    ADCIE |= ADCIE0;                     // Enable interrupt for ADCMEM0

    while(1)
    {
        // Start single ADC conversion
        ADCCTL0 |= ADCENC | ADCSC;

        // Enter low-power mode 0 and enable global interrupts
        __bis_SR_register(LPM0_bits | GIE);

        // After interrupt, CPU wakes up here
        __no_operation(); // For debugger breakpoint
    }
}

// ------------------ ADC Interrupt Service Routine ------------------
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
            ADC_Result = ADCMEM0;                      // Read conversion result from A6
            __bic_SR_register_on_exit(LPM0_bits);      // Exit LPM0
            break;
        default:
            break;
    }
}