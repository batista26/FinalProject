/* 
Contains all appropriate code and functions to drive the: 
- Thermocouple
- Thermistor 
- Potentiometer 
*/

#include "System.h"
#include "Sensors.h"

#define THERMISTOR_CHANNEL    6  // P1.6, A6
#define THERMOCOUPLE_CHANNEL  3  // P1.3, A3
#define POT_CHANNEL           5  // P1.5, A5

char ADCFinished = 0;
unsigned int ADCResult = 0;

// Reads and returns the ADC value from the thermistor (connected to A6/P1.6)
unsigned int readThermistor() {
    return readADC(THERMISTOR_CHANNEL);
}

// Reads and returns the ADC value from the thermocouple (connected to A3/P1.3)
unsigned int readThermocouple() {
    return readADC(THERMOCOUPLE_CHANNEL);
}

// Reads and returns the ADC value from the potentiometer (connected to A5/P1.5)
unsigned int readPot() {
    return readADC(POT_CHANNEL);
}

// Initializes ADC and related pins for all analog sensors (Thermistor, Thermocouple, Potentiometer)
void adcInit() {
    // Test Point 1.1 (A1), Thermocouple P1.3 (A3), Pot P1.5 (A5), Thermistor P1.6 (A6)
    P1SEL0 |= BIT1 | BIT3 | BIT5 | BIT6;
    P1SEL1 |= BIT1 | BIT3 | BIT5 | BIT6;

    // Enable internal reference voltage (1.5V)
    PMMCTL0_H = PMMPW_H;             // Unlock PMM registers
    PMMCTL2 |= INTREFEN;            // Enable internal 1.5V reference
    __delay_cycles(400);            // Wait for reference to settle

    // Configure ADC settings
    ADCCTL0 |= ADCSHT_2 | ADCON;    // ADC ON, sample-and-hold time = 16 ADC clocks
    ADCCTL1 |= ADCSHP;              // Use sampling timer
    ADCCTL2 &= ~ADCRES;             // Clear ADC resolution bits
    ADCCTL2 |= ADCRES_2;            // 12-bit conversion results
    ADCIE |= ADCIE0;                // Enable ADC interrupt
}

/*
Sensor ADC Read Routine
This function takes a channel number (1, 3, 5, or 6) and returns the ADC conversion result.
*/
unsigned int readADC(char adcChannel) {
    // Select ADC input channel
    switch(adcChannel) {
        case 1: ADCMCTL0 = ADCINCH_1 | ADCSREF_1; break;
        case 3: ADCMCTL0 = ADCINCH_3 | ADCSREF_1; break;
        case 5: ADCMCTL0 = ADCINCH_5 | ADCSREF_1; break;
        case 6: ADCMCTL0 = ADCINCH_6 | ADCSREF_1; break;
        default: return 0; // Invalid channel
    }

    // Start ADC conversion
    ADCCTL0 |= ADCENC | ADCSC;

    // Wait for conversion to complete
    while ((ADCIFG & ADCIFG0) == 0);

    return ADCMEM0; // Return ADC result
}

// NOTE: ADC interrupt vector is not used in this implementation. Conversion is done synchronously.
