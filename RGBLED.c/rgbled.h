#ifndef RGBLED_H
#define RGBLED_H

// Sets RGB LED brightness using 8-bit values (0-255)
// Red, Green, and Blue each control a PWM channel
void setRGBLED(char Red, char Green, char Blue);

// Convenience functions to set specific colors
void setRed();    // Set LED to red (retry flame)
void setGreen();  // Set LED to green (flame operational)
void setBlue();   // Set LED to blue (standby mode)

#endif // RGBLED_H