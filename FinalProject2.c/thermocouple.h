#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

// Initializes the thermocouple ADC input
void thermocoupleInit(void);

// Reads the thermocouple ADC value
unsigned int readThermocouple(void);

#endif // THERMOCOUPLE_H