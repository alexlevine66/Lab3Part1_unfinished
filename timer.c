/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void initTimer2(){
    PR2 = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TCS = 0;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    IPC2bits.T2IP = 4;
    T2CONbits.ON = 0;
}

void delayUs(unsigned short t)
{
    T1CONbits.TCKPS = 1;
    T1CONbits.TCS = 0;
    IPC2bits.T2IP = 4;
    TMR1 = 0;
    T1CONbits.ON = 1;
    while(TMR1 < t);
    T1CONbits.ON = 0;    
} 

void delayMs(unsigned int delay){
    for(delay = delay; delay > 0; delay--) {
        delayUs(1000);
    }
}