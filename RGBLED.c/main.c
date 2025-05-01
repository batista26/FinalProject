<<<<<<< HEAD

#include <msp430.h>
#include "RGBLED.h" 
#include "intrinsics.h"
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    RGB_Init();

  

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    while(1)
    {
        setRBGLED(0,0, 255);
        _delay(100000)
           
    }
}
=======

#include <msp430.h>
#include "RGBLED.h" 
#include "intrinsics.h"
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    RGB_Init();

  

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    while(1)
    {
        setRBGLED(0,0, 255);
        _delay(100000)
           
    }
}
>>>>>>> eb48c2633ee349a0cdda829063f6979314add574
