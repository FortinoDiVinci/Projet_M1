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
#include <string.h> 
#include "lcd.h"
#include "user.h"            /* variables/params used by user.c */
#include "system.h"
#include "servomotor.h"
#include "motorControl.h"
#include <libpic30.h>

struct flag flags = {0, 0, 0, 0};

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitGPIO(void)
{
    /* Setup analog functionality and port direction */
    
#ifdef BODY_GUARD
    
    /* INFRARED SETTINGS */
    TRISAbits.TRISA0 = 1;       /* AN0 set as input : IR_2  */
    ANSAbits.ANSA0 = 1;         /*     set to analog : IR_2 */
    TRISBbits.TRISB0 = 1;       /* AN2 set as input : IR_1 */
    ANSBbits.ANSB0 = 1;         /*     set to analog : IR_1 */
    TRISBbits.TRISB1 = 1;       /* AN5 set as input : IR_3 */
    ANSBbits.ANSB1 = 1;         /*     set to analog : IR_3 */

    
    /* ULTRASOUND SETTINGS */
    TRISBbits.TRISB3 = 1;       /* AN3 set as input : US*/
    ANSBbits.ANSB3 = 1;         /* AN3 set to analog : US */
    
    
    /* PWM SETTINGS */
        /* MoveForward */
    TRISBbits.TRISB12 = 0;      /* RB13 set as output : PWM -> */     
    ANSBbits.ANSB12 = 0;        /*      set as digital */
        /* BackForward */
    TRISBbits.TRISB11 = 0;      /* RB11 set as output : PWM <- */
    
    TRISAbits.TRISA7 = 0;       /* RA7 set as output : PWM EN */
    
    
    /* LCD SETTINGS */
    TRISBbits.TRISB13 =	0;      /* Register select set as output */
    ANSBbits.ANSB13 = 0;        /*                 set as digital */
    TRISBbits.TRISB10 = 0;      /* Enable set as output */
                                /* (only digital) */
    TRISAbits.TRISA2 = 0;       /* Data bits set as output */
    ANSAbits.ANSA2 = 0;         /*           set as digital */
    TRISAbits.TRISA3 = 0;       /* Data bits set as output */
    ANSAbits.ANSA3 = 0;         /*           set as digital */
    TRISBbits.TRISB4 = 0;       /* Data bits set as output */
    ANSBbits.ANSB4 = 0;         /*           set as digital */
    TRISAbits.TRISA4 = 0;       /* Data bits set as output */
    ANSAbits.ANSA4 = 0;         /*           set as digital */
    
    
    /* SERVOMOTOR SETTINGS */
    TRISAbits.TRISA1 = 0;       /* Data bits set as output */
    ANSAbits.ANSA1 = 0;         /*           set as digital */
#endif
    
    /* I2C SETTINGS */
    TRISBbits.TRISB8 = 1;       /* SLC1 set as input */
    ANSBbits.ANSB8 = 0;         /*      set as digital */
    TRISBbits.TRISB9 = 1;       /* SDA1 set as input (will change) */
    ANSBbits.ANSB9 = 0;         /*      set as digital */
    
    
    /* UART SETTINGS*/
    ANSBbits.ANSB2=0;           /* set RB2 as digital */
    TRISBbits.TRISB2=1;         /* set RB2 as input */
    
    ANSBbits.ANSB7=0;           /* set RB7 as digital */
    TRISBbits.TRISB7=0;         /* set RB7 as output */
    
    /* Initialize peripherals */
#ifdef PROTECTED
    
    ANSAbits.ANSA2=0;  /*set RA4 as digital */
    TRISAbits.TRISA2=0; /* set RA4 as output */
    
#endif
    
}

#ifdef BODY_GUARD

void InitADC()
{    
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
    for (i=0; i<NMB_SENSORS; i++) /* only IR sensors */
    {
        average[i] += ADCValues[i];
    }
    /* Data is treated every 20 samples */
    if (count == NMB_MEASURES)
    {
        for(i=0; i<NMB_SENSORS; i++)
        {
            average[i] = average[i] / count;
        }
        /* RESET count */
        count = 0;
    }
    ObjectReaction(average);
}

void ObjectReaction(const u16* average)
{

        if(average[0] * PIC_VOLTAGE / 1023 >= 1.300) 
        {
            /* If the left IR detects an object closer than x cm */
            flags.IR_l = 1;
        }
        if(average[1] * PIC_VOLTAGE / 1023 >= 1.300)
        {
            /* If the front IR detects an object closer than x cm */
            flags.IR_c = 1;
        }
        if(average[2] * PIC_VOLTAGE / 1023 >= 1.300)
        {
            /* If the right IR detects an object closer than x cm */
            flags.IR_r = 1;
        }
}

void StartADC(u16* ADCValues)
{
    static u8 active_sensor = 0; /* The initialization will only occurs once */
    switch(active_sensor)
    {
        case IR1 :
            START_SAMPLING(IR1);
            break;
        case IR2 :
            START_SAMPLING(IR2);
            break;
        case IR3 :
            START_SAMPLING(IR3);
            break;
        case US :
            START_SAMPLING(US);
            break;        
    }
        /* CONVERSION */

    AD1CON1bits.SAMP = 1; 
    __delay_ms(1);
    AD1CON1bits.SAMP = 0;
    while (!AD1CON1bits.DONE){}; 
    
    switch(active_sensor)
    {
        case IR1 :
            ADCValues[0] = ADC1BUF0;
            break;
        case IR2 :
            ADCValues[1] = ADC1BUF0;
            break;
        case IR3 :
            ADCValues[2] = ADC1BUF0;
            break;
        case US :
            ADCValues[3] = ADC1BUF0;
            break;        
    }
    active_sensor = (active_sensor + 1)%4;
}

void DisplayADCIR(u16 const ADCValue)
{
    float voltage;
    voltage = (ADCValue * PIC_VOLTAGE / 1023);
    LcdPutFloat(voltage,3);
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
    CCP2CON3Hbits.POLBDF = 0; // Configure output polarity (Active Low)
    CCP2TMRL = 0x0000; //Initialize timer prior to enable module.
    CCP2PRL = 200;             //Configure time base period
    /* (u16)((1/PWM_FREQ)/(4/SYS_FREQ) - 1) = 99 */
    CCP2RA = 0; // Set the rising edge compare value
    CCP2RB = 0; // Set the falling edge compare value
    CCP2CON1Lbits.CCPON = 1; // Turn on MCCP module  
}

void InitTimerServo()
{
    extern u16 servoPulseWidth;
    T1CON = 0x00; //Stops the Timer1 and reset control reg.
    TMR1 = 0x00; //Clear contents of the timer register
    T1CONbits.TCKPS=0b01; // Set the prescaler to 1:8
    PR1 =40083; //Load the Period register with the value for 20 ms signal
    servoPulseWidth=3006; //Load the period of the pulse for 1.5 ms
    IPC0bits.T1IP = 0x01; //Setup Timer1 interrupt priority level 1
    IFS0bits.T1IF = 0; //Clear the Timer1 interrupt status flag
    IEC0bits.T1IE = 1; //Enable Timer1 interrupts
    T1CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:8 and
    //clock source set to the internal instruction cycle
}

void Distance(const u16 *average)
{
    if(average[US] * PIC_VOLTAGE / 1023 < D_170_CM)
        {
            LcdPuts("down slow");
            MoveBackward(SLOW);
        }
        
        else if(average[US] * PIC_VOLTAGE / 1023 > D_120_CM)
        {
            MoveForward(SLOW);
            LcdPuts("UP slow");
        }
        else//((average[US]* PIC_VOLTAGE / 1023 < D_120_CM)&&(average[US] * PIC_VOLTAGE / 1023 > D_170_CM))
        {
            LcdPuts("stop!");
           StopMotor(); 
        }
}

#endif

void InitUART(void)
{
    U1BRG= 25; //(FCY /(16*38400))-1; //Set the value of Baudrate (38461)

    IPC3bits.U1TXIP = 0x4;      /* Set Uart TX Interrupt Priority */
    IPC2bits.U1RXIP = 0x4;      /* Set Uart RX Interrupt Priority */
    
    U1STA = 0x0;
    U1MODE = 0x0;               /* no parity, 1 STOP bit */
    
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;        /* Enable Transmit */
    IEC0bits.U1RXIE = 1;        /* Enable Receive Interrupt */
}
#ifdef PROTECTED
   
void InitTimerUS()
{
    T1CON = 0x00; //Stops the Timer1 and reset control reg.
    TMR1 = 0x00; //Clear contents of the timer register
    T1CONbits.TCKPS=0b00; // Set the prescaler to 1:1
    PR1 =200; //Load the Period register with the value for 20 ms signal
    IPC0bits.T1IP = 0x01; //Setup Timer1 interrupt priority level 1
    IFS0bits.T1IF = 0; //Clear the Timer1 interrupt status flag
    IEC0bits.T1IE = 1; //Enable Timer1 interrupts
    T1CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:8 and
    //clock source set to the internal instruction cycle
}
        
#endif
