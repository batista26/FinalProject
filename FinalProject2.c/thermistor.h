#ifndef THERMISTOR_H_
#define THERMISTOR_H_

#include <stdint.h>

// Initialize the ADC hardware for thermistor reading
void therm_Init(void);

// Get the latest ADC result from the thermistor
uint16_t therm_GetResult(void);

#endif /* THERMISTOR_H_ */