#include <msp430.h>
#include "rgbled.h"

// Sets the RGB LED color using 8-bit values
// Each color value is scaled to 10-bit PWM by left-shifting by 2
void setRGBLED(char Red, char Green, char Blue)
{
    TB3CCR3 = Red << 2;   // Red output on CCR3
    TB3CCR2 = Green << 2; // Green output on CCR2
    TB3CCR1 = Blue << 2;  // Blue output on CCR1
}

// Set the LED to red (used for retry flame state indication)
void setRed()
{
    setRGBLED(255, 0, 0);
}

// Set the LED to green (used for flame operational indication)
void setGreen()
{
    setRGBLED(0, 255, 0);
}

// Set the LED to blue (used for standby mode indication)
void setBlue()
{
    setRGBLED(0, 0, 255);
}