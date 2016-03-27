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
#include "pwm.h"
#include <stdlib.h>


#define CLR 0x01

#define RUN_LED LATDbits.LATD2
#define STP_LED LATDbits.LATD0
#define RUN TRISDbits.TRISD2
#define STP TRISDbits.TRISD0

#define SWT_T TRISDbits.TRISD5
#define SWT PORTDbits.RD5

#define RST_T TRISDbits.TRISD6
#define RST PORTDbits.RD6

#define INPUT1 LATDbits.LATD1
#define INPUT2 LATDbits.LATD3
#define INPUT3 LATDbits.LATD9
#define INPUT4 LATDbits.LATD12





// ******************************************************************************************* //

typedef enum RS_enum {
    wait, idle, wait2, forward, wait3, backward, wait4, idle2, 
}status;

volatile int q = 0;
volatile int d = 0;
volatile int line = 1;
volatile unsigned int val;
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
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    double analog=0;
    int i;
    TRISDbits.TRISD6=0;
    LATDbits.LATD0 = 1;
    INPUT1=0;
    INPUT2=0;
    INPUT3=0;
    INPUT4=0;
    initTimer2();
    initLCD();
    initADC();
    initPWM();
    delayMs(10);
    LATDbits.LATD0 = 0;
    val=0;
    TRISDbits.TRISD0 = 0;
    int radix=10;
    writeCMD(CLR);
    //clearLCD();
    moveCursorLCD(0,2);
    testLCD();
    char buf[5];
    const char* string;
    
    status state=idle;
           
    while(1)
    {       
        clearLCD();
        if(IFS0bits.AD1IF == 1)
        {
            
            val=ADC1BUF0;
            printStringLCD("Voltage= ");
           
            analog=(3.3*val)/1023;
            if(val<511 && val!=0) {
                OC2RS=1023;
                OC4RS=val/3.3;
            }
            else if(val>=511) {
                OC2RS=val/3.3;
                OC4RS=1023;
            }
            //OC2RS=val;
            //OC4RS=val;
            sprintf(buf, "%1.1f", analog);
            string=buf;
            printStringLCD(string);
            IFS0bits.AD1IF = 0;
            delayMs(100);
        }
        
        switch(state) {
            
            case(idle):
                OC2CONbits.ON=0;
                OC4CONbits.ON=0;
                if(PORTDbits.RD6 == 0) {
                    state=wait;
                }
                break;
            
            case(wait):
                if(PORTDbits.RD6 == 1) {
                    state=forward;
                }
                break;
                
            case(forward):
                
                OC2CONbits.ON=0;
                OC4CONbits.ON=0;
                INPUT1=0;
                INPUT2=0;
                INPUT3=0;
                INPUT4=0;
                delayUs(10);
                RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1
                RPD3Rbits.RPD3R = 0b1011; // map OC4 to RD3
                RPD12Rbits.RPD12R=0;  
                RPD9Rbits.RPD9R=0; 
                delayUs(10);
                INPUT1=1;
                INPUT2=0;
                INPUT3=1;
                INPUT4=0;
                OC2CONbits.ON=1;
                OC4CONbits.ON=1;
                if(PORTDbits.RD6 == 0) {
                    state=wait2;
                }
                break;
            
            case(wait2):
                if(PORTDbits.RD6 == 1) {
                        state=idle2;
                    }
                break;
                
            case(idle2):
                
                OC2CONbits.ON=0;
                OC4CONbits.ON=0;
                if(PORTDbits.RD6 == 0) {
                    state=wait3;
                }
                break;
            
            case(wait3):
                if(PORTDbits.RD6 == 1) {
                        state=backward;
                    }
                break;
                
            case(backward):
                OC2CONbits.ON=0;
                OC4CONbits.ON=0;
                INPUT1=0;
                INPUT2=0;
                INPUT3=0;
                INPUT4=0;
                delayUs(10);
                RPD1Rbits.RPD1R = 0;        
                RPD3Rbits.RPD3R = 0;        
                RPD12Rbits.RPD12R=0b1011;   // map OC2 to RD12
                RPD9Rbits.RPD9R=0b1011;     // map OC4 to RD6
                delayUs(10);
                INPUT1=0;
                INPUT2=1;
                INPUT3=0;
                INPUT4=1;
                delayMs(10);
                OC2CONbits.ON=1;
                OC4CONbits.ON=1;
                if(PORTDbits.RD6 == 0) {
                    state=wait4;
                }
                
                break; 
            case(wait4):
                if(PORTDbits.RD6 == 1) {
                    state=idle;
                }
        }
       delayMs(10); 
    }
    return 0;
}

//void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(){
  //  IFS0bits.AD1IF = 0;
  //  val = ADC1BUF0;
//}
