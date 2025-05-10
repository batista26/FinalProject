#include <driverlib.h>
#include "led.h"

void initLED(void)
{
    // Set P5.0 as output
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0);

    // Unlock GPIO power-on default high-impedance mode
    PMM_unlockLPM5();
}

void toggleLED(void)
{
    // Toggle P5.0
    GPIO_toggleOutputOnPin(GPIO_PORT_P5, GPIO_PIN0);
}
