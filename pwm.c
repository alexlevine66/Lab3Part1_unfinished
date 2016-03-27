
#include <xc.h>
//#include <proc/p32x470f5121.h>
#include "pwm.h"


void initPWM(){
    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1
    RPD3Rbits.RPD3R = 0b1011; // map OC4 to RD3
    RPD12Rbits.RPD12R=0;  
    RPD9Rbits.RPD9R=0;     
    T3CONbits.TCKPS=0;
    PR3=1023;
    TMR3=0;
    T3CONbits.TON=1;
    OC2CONbits.OCTSEL=0;
    OC2CONbits.OCM=6;       // Configure for PWM mode
    OC2RS=500;
    OC2R=0;     // Initialize primary Compare Register
    
    OC4CONbits.OCTSEL=0;
    OC4CONbits.OCM=6;       // Configure for PWM mode
    OC4RS=500;
    OC4R=0;     // Initialize primary Compare Register
    
    OC2CONbits.ON=0;
    OC4CONbits.ON=0;
    
   // OC3CON = 0x0000; // Turn off OC1 while doing setup.
    //OC3R = 0x0000; // Initialize primary Compare Register
    //OC3RS = 0x0000; // Initialize secondary Compare Register
    //OC3CON = 0x0006; // Configure for PWM mode
    //OC3CONSET = 0x8000; // Enable OC1
}
