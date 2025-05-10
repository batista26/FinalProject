#include <msp430.h>



void setRGBLED(char Red, char Green, char Blue);
void setRed();
void setGreen();
void setBlue();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer

    // Configure P6.0, P6.1, P6.2 for PWM output
    P6DIR |= BIT0 | BIT1 | BIT2;              
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);          
    P6SEL0 |= BIT0 | BIT1 | BIT2;

    // Unlock GPIOs
    PM5CTL0 &= ~LOCKLPM5;

    // Timer B3 setup
    TB3CCR0 = 1024 - 1;                        // PWM Period
    TB3CCTL1 = OUTMOD_3;                       // CCR1 set/reset (Blue)
    TB3CCR1 = 0;                               
    TB3CCTL2 = OUTMOD_3;                       // CCR2 set/reset (Green)
    TB3CCR2 = 0;
    TB3CCTL3 = OUTMOD_3;                       // CCR3 set/reset (Red)
    TB3CCR3 = 0;
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;   // SMCLK, up mode, clear timer

    while(1)
    {
        setRed();
        __delay_cycles(100000);

        setGreen();
        __delay_cycles(100000);

        setBlue();
        __delay_cycles(100000);
    }
}

// Generic PWM brightness control
void setRGBLED(char Red, char Green, char Blue)
{
    TB3CCR3 = Red << 2;   // Red on CCR3
    TB3CCR2 = Green << 2; // Green on CCR2
    TB3CCR1 = Blue << 2;  // Blue on CCR1
}

// Set specific colors
void setRed()
{
    setRGBLED(255, 0, 0);  //retry flame
}

void setGreen()
{
    setRGBLED(0, 255, 0); //flame operational
}

void setBlue()
{
    setRGBLED(0, 0, 255); //Standby mode
}
