// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#include "switch.h"
#include "keypad.h"
#include "adc.h"


#define CLR 0x01

#define RUN_LED LATDbits.LATD2
#define STP_LED LATDbits.LATD0
#define RUN TRISDbits.TRISD2
#define STP TRISDbits.TRISD0

#define SWT_T TRISDbits.TRISD5
#define SWT PORTDbits.RD5

#define RST_T TRISDbits.TRISD6
#define RST PORTDbits.RD6

#define ROW_1 LATDbits.LATD12
#define ROW_2 LATDbits.LATD6
#define ROW_3 LATDbits.LATD5
#define ROW_4 LATDbits.LATD11

#define COL_1 PORTGbits.RG0
#define COL_2 PORTGbits.RG13
#define COL_3 PORTGbits.RG12


// ******************************************************************************************* //

typedef enum RS_enum {
    wait, check, write, changeM1, changeM2
}status;

volatile int q = 0;
volatile int d = 0;
volatile int line = 1;
volatile unsigned int val = 0;
volatile unsigned int digitalValue = 0;
volatile char k = -1;
volatile int x = 0;
volatile char password[5] = {' ', ' ', ' ', ' ', '\0'};
volatile int place = 0;

volatile char setCheck[5] = {'*', '*', ' ', ' ', '\0'};
volatile char invalid1 = '*';
volatile char invalid2 = '#';

volatile status state = wait;
volatile status next;

int main(void)
{
    enableInterrupts();
    
    
    SYSTEMConfigPerformance(10000000);
    STP = 0;
    RUN = 0;
    int i;
    
    LATDbits.LATD0 = 1;
    initTimer2();
    initLCD();
    initADC();
    delayMs(1000);
    LATDbits.LATD0 = 0;

    TRISDbits.TRISD0 = 0;
    
    writeCMD(CLR);
    //clearLCD();
    moveCursorLCD(0,2);
    testLCD();
    
    LATDbits.LATD0 = 1;
    delayMs(1000);
            
    while(1)
    {       
        if(val!=0) {
            digitalValue=(1023*val)/3.3;
            printStringLCD("Found Something");
            LATDbits.LATD0 = 0;
        }
        
    }
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    val = ADC1BUF0;
}
