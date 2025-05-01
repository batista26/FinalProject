#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

#include <stdint.h>

// ADC channel definition for P1.3 (A3)
#define POT_ADC_CHANNEL ADC_INPUT_A3

void Potentiometer_init(void);
uint16_t Potentiometer_readRaw(void);
float Potentiometer_readVoltage(void);  // Optional if you want voltage

#endif /* POTENTIOMETER_H_ */
