#ifndef THERMISTOR_H_
#define THERMISTOR_H_

// Initializes the ADC to read from thermistor on P1.6 (A6)
void Thermistor_Init(void);

// Starts a conversion and returns the 12-bit ADC result
unsigned int Thermistor_Read(void);

#endif /* THERMISTOR_H_ */
