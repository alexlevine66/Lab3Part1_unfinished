/* 
 * File:   switch.c
 * Author: gvanhoy
 *
 * Created on September 3, 2015, 10:15 AM
 */

#include <xc.h>
#include "switch.h"

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0

void initSW(){
    TRISDbits.TRISD5 = 1; // J10 Pin 13
    CNCONDbits.ON = 1;
    CNENDbits.CNIED5 = 1;
    CNPUDbits.CNPUD5 = 1;
    IFS1bits.CNDIF = 0;
    IPC8bits.CNIP = 7;
    IEC1bits.CNDIE = 1; 
    TRISDbits.TRISD6 = 1; // J10 Pin 13
    CNENDbits.CNIED6 = 1;
    CNPUDbits.CNPUD6 = 1;
    TRISGbits.TRISG12 = 0; //J10 Pin 1
    TRISGbits.TRISG15 = 0; //J10 Pin 3
    TRISDbits.TRISD0 = 0;
    
}