#include <msp430.h>
#include "thermostat.h"
#include "potentiometer.h"
#include "thermistor.h"
#include "rgbled.h"
#include "pilot.h"
#include "servo.h"
#include "led.h"
#include "thermocouple.h"

// -------- PIN ASSIGNMENTS --------
// Potentiometer:    P1.5 (ADC input)
// Thermistor:       P1.6 (ADC input)
// Thermocouple:     P1.3 (ADC input for flame sensing)
// Servo Motor:      P2.1 (PWM output to control airflow valve)
// Pilot Control:    P5.4 (Digital output to control ignitor)
// Red LED:          P5.0 (Blinking error/status LED)
// RGB LED:          P6.0 (Red), P6.1 (Green), P6.2 (Blue)
// Call for Heat:    P3.0 (Digital input, 24mV signal reduced for MCU-safe use)

#define FLAME_THRESHOLD 500           // ADC value for flame detection
#define SERVO_OPEN_ANGLE 90           // Valve open angle
#define SERVO_CLOSE_ANGLE 0           // Valve closed angle

// Simple delay in seconds
void delay_seconds(unsigned int sec) {
    while (sec--) {
        __delay_cycles(1000000);      // ~1 second at 1 MHz
    }
}

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Unlock GPIOs for use
    PM5CTL0 &= ~LOCKLPM5;

    // Initialize all connected components
    thermostat_Init();       // Thermistor on P1.6
    potentiometer_Init();    // Potentiometer on P1.5
    thermistor_Init();       // (Optional) P1.6
    thermocouple_Init();     // Flame detection on P1.3
    pilot_Init();            // Pilot control on P5.4
    servo_Init();            // Servo motor control on P2.1 (PWM)
    led_Init();              // Red LED on P5.0
    rgbled_Init();           // RGB LED on P6.0, P6.1, P6.2

    // Declare variables
    unsigned int flame = 0;
    unsigned int potVal = 0;
    float thresholdC = 0;
    float tempC = 0;

    while (1)
    {
        // ----------- READ SETPOINT -----------
        potVal = potentiometer_Read();              // Read potentiometer on P1.5
        thresholdC = (potVal * 50.0f) / 4095.0f;    // Map ADC to 0–50°C

        // ----------- READ CURRENT TEMPERATURE -----------
        tempC = thermostat_ReadCelsius();           // From thermistor on P1.6

        // ----------- RGB LED INDICATES STATE -----------
        if (tempC > thresholdC) {
            rgbled_SetColor(RED);                   // Over temperature
        } else if (tempC > thresholdC - 5) {
            rgbled_SetColor(YELLOW);                // Near setpoint
        } else {
            rgbled_SetColor(GREEN);                 // Below setpoint
        }

        // ----------- IGNITION SEQUENCE -----------
        pilot_On();                                 // Start ignitor (P5.4)
        servo_SetAngle(SERVO_OPEN_ANGLE);           // Open airflow valve (P2.1)
        delay_seconds(2);                           // Wait for flame to ignite

        flame = thermocouple_Read();                // Read flame sensor (P1.3)

        // ----------- MONITOR HEATING STATE -----------
        while (flame > FLAME_THRESHOLD) {
            tempC = thermostat_ReadCelsius();       // Update temperature

            if (tempC > thresholdC) {
                break;                               // Too hot, shut down
            }

            flame = thermocouple_Read();            // Check flame again
        }

        // ----------- SHUTDOWN SEQUENCE -----------
        pilot_Off();                                // Turn off ignitor (P5.4)
        servo_SetAngle(SERVO_CLOSE_ANGLE);          // Close valve (P2.1)

        led_On();                                   // Blink red LED (P5.0)
        delay_seconds(1);
        led_Off();

        // ----------- OPTIONAL: IDLE OR LOW POWER -----------
        // _bis_SR_register(LPM0_bits + GIE);
    }
}
