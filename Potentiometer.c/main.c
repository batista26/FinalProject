#include <msp430.h>


// --- ADC Configuration ---
#define POT_PIN BIT5  // P1.5 is the analog input pin for the potentiometer
#define ADC_SAMPLE_HOLD_TIME 256 // Sample and hold time (in ADC12CLK cycles)

char txBuffer[64];  // Define a buffer for UART communication
volatile unsigned int txIndex = 0;
volatile unsigned int txLength = 0;

// Function declarations

void adc_init(void);
unsigned int read_adc(void);
void send_data(unsigned char data);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;        // Disable GPIO power-on default high-impedance mode

    
    adc_init();   // Initialize ADC to read the potentiometer value

    __enable_interrupt(); // Enable global interrupts

    while (1)
    {
        // Read the potentiometer value from ADC
        unsigned int adc_val = read_adc();

        // Convert ADC value to voltage (assuming a 3.3V reference voltage)
        float voltage = (adc_val * 3.3) / 4095.0;  // 12-bit ADC resolution (0-4095)

        // Send the voltage to the serial console (you can modify this part to output the potentiometer value)
        printf("Potentiometer Voltage: %.3f V\n", voltage);

        __delay_cycles(1000000); // Wait some time before taking the next reading
    }
}



// ADC initialization
void adc_init(void)
{
     // Set P1.4 as an analog input (Thermistor pin)
    P1DIR &= ~POT_PIN;  // Set P1.4 as input
    P1SEL0 |= POT_PIN;  // Enable analog function for P1.4

    // Configure the ADC
    ADCCTL0 = ADCSHT_3 | ADCON;  // Enable ADC, enable multiple conversions, sample-and-hold time 64, turn on ADC
    ADCCTL1 = ADCSHP;  // Use sampling timer, 12-bit resolution, select A1 (P1.4)
    ADCCTL2 &= ~(ADCRES);
    ADCCTL2 |= ADCRES_2;
    ADCMCTL0 = ADCINCH_5;
    ADCCTL0 |= ADCENC | ADCSC;  // Start ADC conversion
    __delay_cycles(10);         // Delay to ensure ADC starts
}

// Read the ADC value from P1.5 (Potentiometer)
unsigned int read_POT(void)
{
    ADCCTL0 |= ADCENC | ADCSC;  // Start ADC conversion
    while (ADCCTL1 & ADCBUSY);  // Wait until conversion is done

    // Check if ADC conversion completed
    if (ADCCTL0 & ADCIFG) {
        ADCCTL0 &= ~ADCIFG;  // Clear ADC interrupt flag
    }

    return ADCMEM0;  // Return ADC result
}
    


// Function to send data to the UART serial console
void send_data(unsigned char data)
{
    while (!(UCA0IFG & UCTXIFG));  // Wait for TX buffer to be ready
    UCA0TXBUF = data;              // Send the data
}
