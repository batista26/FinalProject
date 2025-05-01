#include <msp430.h>
#include <driverlib.h>

int main(void) {

    volatile uint32_t i;

    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // Set P4.0 to output direction
    GPIO_setAsOutputPin(
        GPIO_PORT_P4,
        GPIO_PIN0
    );

    // Disable the GPIO power-on default high-impedance mode
    PMM_unlockLPM5();

    while(1)
    {
        // Toggle P4.0 output
        GPIO_toggleOutputOnPin(
            GPIO_PORT_P4,
            GPIO_PIN0
        );

        // Delay 
        for(i=10000; i>0; i--);
    }
}