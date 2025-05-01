#ifndef LED_H_
#define LED_H_

#include <stdint.h>

// Initializes the LED pin (e.g., P4.0) as output
void LED_init(void);

// Toggles the LED state (on/off)
void LED_toggle(void);

// Turns the LED on
void LED_on(void);

// Turns the LED off
void LED_off(void);

#endif /* LED_H_ */
