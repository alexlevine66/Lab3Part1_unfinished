#include <xc.h>
#include "adc.h"

void initADC(void){
    
    //ANSELBbits.ANSB0 = 0; 
    AD1CON1bits.FORM = 0; // 16 unsigned integer
    AD1CON1bits.SSRC = 7; // Auto-convert mode
    AD1CON1bits.ASAM = 1; // Auto-sampling
    AD1CON2bits.VCFG = 0; // Use board refernece voltages
    AD1CON2bits.CSCNA = 0; // Disable scanning
    AD1CON2bits.SMPI = 0; // 1 burrito
    AD1CON2bits.ALTS = 0; // Only Mux A
    AD1CON3bits.ADRC = 0; // Use PBCLK
    AD1CON3bits.SAMC = 2; // 2 Tad per sample
    AD1CON3bits.ADCS = 1; // 4 times the PBCLK
    AD1CHSbits.CH0NA = 0; // Use Vref- as negative reference
    AD1CHSbits.CH0SA = 0; // Scan AN0 at least
    IFS0bits.AD1IF = 0; // Put down ADC flag
    IPC5bits.AD1IP = 7;
    IEC0bits.AD1IE = 0;
    ADC1BUFF = 0;
    AD1CON1bits.ADON = 1; // turn on the ADC
    
}

int analogRead(void){
    AD1CON1bits.SAMP = 1;           // Begin sampling
    while( AD1CON1bits.SAMP );      // wait until acquisition is done
    while( ! AD1CON1bits.DONE );    // wait until conversion done
 
    return ADC1BUF0;                // result stored in ADC1BUF0
}