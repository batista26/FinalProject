#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

// Initializes the ADC to read from P1.5 (A5 channel)
void adc_init(void);

// Starts an ADC conversion on P1.5 and returns the 12-bit result
unsigned int read_POT(void);

#endif // POTENTIOMETER_H