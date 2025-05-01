/* 
Contains all appropriate code and function to drive the: 
- Thermocouple
- Thermistor 
- Potentiometer 


*/
#include "System.h"
#include "Sensors.h"
char ADCFinished = 0 ; 
unsigned int ADCResult = 0;
// 
unsigned int readThermistor () {
    result = readADC(THERMISTOR_CHANNEL);
  //Insert Remaining Code

  //Return what your function is expected to 

}
unsigned int readThermocouple(){
    result = readADC(THERMOCOUPLE_CHANNEL);
    //Insert Remaining Code
    
    //Return what your function is expected to 


}
unsigned int readPot(){
    result = readADC(POT_CHANNEL)
    //Insert Remaining Code

  //Return what your function is expected to 

}
void adcInit(){
    //Test Point 1.1, Thermocouple P1.3, Pot 1.5, Thermistor 1.6
    // Configure ADC Channel Pins (1.6, 1.3,1.1,1.5,1.6)
    //P1.1 --> A1, P1.3-->A3,  P1.5--> A5, P1.6 -->A6
    P1SEL0 |= BIT1 | BIT3| BIT5 | BIT6;
    P1SEL1 |= BIT1 |BIT3 | BIT5 | BIT6; 

    //Configure ADC
    ADCCTL0 |= ADCSHT_2 | ADCON;  // ADCON, S&H=16 ADC clks
    ADCCTL1 |= ADCSHP;           // ADCCLK = MODOSC; sampling timer
    ADCCTL2 &= ~ADCRES;            // clear ADCRES in ADCCTL
    ADCCTL2 |= ADCRES_2;        //12-bit coversation results 
    ADCMCTL0 |= ADCINCH_1 | ADCINCH_3; 
    ADCIE |= ADCIE0;            // Enable ADC conv complete interrupt
}

/*
Sensor INTERRUPT ROUTINES 
*/

unsigned int readADC(char adcChannel){
    switch(adcChannel){
        case 1: ADCMTL0 |= ADCINCH_1;
                break;
        case 3: ADCMTL0 |= ADCINCH_3;
                break; 
        case 5: ADCMTL0 |= ADCINCH_5;
                break; 
        case 6: ADCMTL0 |= ADCINCH_6;
                break; 

    }
    ADCCTL0 |= ADCENC | ADCSC; //Sampling and  conversion start
    while(ADCIV != ADCIV_ADCIFG); //Wait until reading is finished 
    while(ADC_Finished != 1)
    unsigned int result = ADCMEM0;
    return ADCMEM0;     // Return the contents of ADCMEM0

}
