/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include <stdint.h>          /* For uint32_t definition */
#include <stdbool.h>         /* For true/false definition */

#include "user.h"            /* variables/params used by user.c */
#include "system.h"
#include <libpic30.h>

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void)
{
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
}

void InitADC()
{
    /* INFRARED SETTING */
    TRISAbits.TRISA0 = 1; /* AN0 set as input */
    TRISBbits.TRISB0 = 1; /* AN2 set as input */
    TRISBbits.TRISB1 = 1; /* AN5 set as input */
    ANSAbits.ANSA0 = 1; /* AN0 set to analog : IR_2 */
    ANSBbits.ANSB0 = 1; /* AN2 set to analog : IR_1 */
    ANSBbits.ANSB1 = 1; /* AN5 set to analog : IR_3 */
    
    /* ULTRASOUND SETTING */
    TRISBbits.TRISB3 = 1; /* AN3 set as input */
    ANSBbits.ANSB3 = 1; /* AN3 set to analog : US */
    
    AD1CON1 = 0x0000; /* End sampling (clear) */
    AD1CSSL = 0;
    AD1CON3 = 0x0002; /* Manual Sample, Tad = 3Tcy */
    AD1CON2 = 0;
}

void ObjectDetection(const u16* ADCValues, u16* average)
{
    static u8 count = 0;
    char i;
    count ++;
    for (i=0; i<NMB_SENSORS-1; i++) /* only IR sensors */
    {
        average[i] += ADCValues[i];
    }
    /* Data is treated every 20 samples */
    if (count == NMB_MEASURES)
    {
        for(i=0; i<NMB_SENSORS; i++)
        {
            average[i] /= count;
        }
        int obstacle[NMB_SENSORS] = {0, 0, 0};
        for(i = 0; i<NMB_SENSORS; i++)
        {
            if((average[i] <= IR_DISTANCE_80)&&(average[i] >= IR_DISTANCE_50))
            {
                obstacle[i] = 1;
            }
            if((average[i] < IR_DISTANCE_50)&&(average[i] >= IR_DISTANCE_40))
            {
                obstacle[i] = 2;
            }
            if((average[i] < IR_DISTANCE_40)&&(average[i] >= IR_DISTANCE_30))
            {
                obstacle[i] = 3;
            }
            if((average[i] < IR_DISTANCE_30)&&(average[i] >= IR_DISTANCE_20))
            {
                obstacle[i] = 4;
            }
        }
        /* RESET count */
        count = 0;
    }
}

void StartADC(u16* ADCValues)
{
    static u8 active_sensor = 0;
    if(active_sensor == IR1)
        {
            START_SAMPLING(IR1);
        }
        if(active_sensor == IR2)
        {
            START_SAMPLING(IR2);
        }
        if(active_sensor == IR3)
        {
            START_SAMPLING(IR3);
        }
        if(active_sensor == US)
        {
            START_SAMPLING(US);
        }
        /* CONVERSION */

        AD1CON1bits.SAMP = 1; 
        __delay_ms(1);
        AD1CON1bits.SAMP = 0;
        while (!AD1CON1bits.DONE){}; 

        if(active_sensor == IR1)
        {
        ADCValues[0] = ADC1BUF0;
        }
         if(active_sensor == IR2)
        {
        ADCValues[1] = ADC1BUF0;
        }
         if(active_sensor == IR3)
        {
        ADCValues[2] = ADC1BUF0;
        }
         if(active_sensor == US)
        {
        ADCValues[3] = ADC1BUF0;
        }
        active_sensor = (active_sensor + 1)%4;
}

void InitPWM(void)
{
    // Set MCCP operating mode
    CCP2CON1Lbits.CCSEL = 0; // Set MCCP operating mode (OC mode)
    CCP2CON1Lbits.MOD = 0b0101; // Set mode (Buffered Dual-Compare/PWM mode)
    
    //Configure MCCP Timebase
    CCP2CON1Lbits.TMR32 = 0; // Set timebase width (16-bit)
    CCP2CON1Lbits.TMRSYNC = 0; // Set timebase synchronization (Synchronized)
    CCP2CON1Lbits.CLKSEL = 0b000; // Set the clock source (Tcy)
    CCP2CON1Lbits.TMRPS = 0b00; // Set the clock pre-scaler (1:1)
    CCP2CON1Hbits.TRIGEN = 0; // Set Sync/Triggered mode (Synchronous)
    CCP2CON1Hbits.SYNC = 0b00000; // Select Sync/Trigger source (Self-sync)
    
    //Configure MCCP output for PWM signal
    CCP2CON2Hbits.OCAEN = 1; // Enable desired output signals (OC1A)
    CCP2CON2Hbits.OCBEN = 1;
    CCP2CON3Hbits.OUTM = 0b000; // Set advanced output modes (Standard output)
    CCP2CON3Hbits.POLACE = 0; //Configure output polarity (Active High)
    CCP2CON3Hbits.POLBDF = 1; // Configure output polarity (Active Low)
    CCP2TMRL = 0x0000; //Initialize timer prior to enable module.
    CCP2PRL = 0xFFFF; //Configure timebase period
    CCP2RA = 0x1000; // Set the rising edge compare value
    CCP2RB = 0x8000; // Set the falling edge compare value
    CCP2CON1Lbits.CCPON = 1; // Turn on MCCP module
}