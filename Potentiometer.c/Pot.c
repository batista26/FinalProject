#include "potentiometer.h"
#include <driverlib.h>

void Potentiometer_init(void)
{
    // Configure P1.3 as ADC input (A3)
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN3, GPIO_TERTIARY_MODULE_FUNCTION);

    // Initialize ADC
    ADC_init(ADC_BASE,
             ADC_SAMPLEHOLDSOURCE_SC,
             ADC_CLOCKSOURCE_ADCOSC,
             ADC_CLOCKDIVIDER_1);

    ADC_enable(ADC_BASE);

    ADC_configureMemory(ADC_BASE,
                        POT_ADC_CHANNEL,
                        ADC_VREFPOS_AVCC,
                        ADC_VREFNEG_AVSS);

    ADC_clearInterrupt(ADC_BASE, ADC_COMPLETED_INTERRUPT);
    ADC_enableInterrupt(ADC_BASE, ADC_COMPLETED_INTERRUPT);
}

uint16_t Potentiometer_readRaw(void)
{
    ADC_startConversion(ADC_BASE, ADC_SINGLECHANNEL);
    while (!ADC_getInterruptStatus(ADC_BASE, ADC_COMPLETED_INTERRUPT));
    return ADC_getResults(ADC_BASE);
}

float Potentiometer_readVoltage(void)
{
    uint16_t raw = Potentiometer_readRaw();
    return (raw / 1023.0f) * 3.3f;  // Assuming AVCC = 3.3V
}