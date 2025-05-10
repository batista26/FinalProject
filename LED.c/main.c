#include <driverlib.h>

int main(void) {

    volatile uint32_t i;

    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // Set P5.0 to output direction
    GPIO_setAsOutputPin(
        GPIO_PORT_P5,      // Changed from P1 to P5
        GPIO_PIN0
    );

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PMM_unlockLPM5();

    while(1)
    {
        // Toggle P5.0 output
        GPIO_toggleOutputOnPin(
            GPIO_PORT_P5,   // Changed from P1 to P5
            GPIO_PIN0
        );

        // Delay loop (not precise but good enough for a blink test)
        for(i = 10000; i > 0; i--);
    }
}
