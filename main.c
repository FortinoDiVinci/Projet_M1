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

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <string.h>        /* Inclues the string library                      */
#include <stdlib.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "motorControl.h"
#include "lcd.h"
#include "i2c.h"
#include "uart.h"
//#include <math.h>
#include "algorithms.h"
#include <libpic30.h>

// test branch GitHub

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

u8 data;

u16 angle=0;

extern struct flag flags;

int main(void)
{
    /* Configure the oscillator both devices */
    
    ConfigureOscillator();
    
    /* Initialize IO ports and peripherals for both devices */
   
    InitGPIO(); 
    InitUART();
    InitI2c();
    InitI2cCompass();
  
    /* Program for the bracelet */
    
#ifdef PROTECTED
    
    /* Initialize IO ports and peripherals */

      InitTimerUS();
 
    /* The values of the magnetic field will be save in x and y */
    s16 x = 0;
    s16 y = 0;   
    
    while(1)
    {
       I2cReadData(&x, &y);
       ComputeAngle(&angle, x, y);
       PutData16(angle);
       __delay_ms(500);
    }
    
#endif
    
    /* Program for the bodyguard*/
    
#ifdef BODY_GUARD
    

    /* Initialize IO ports and peripherals */
    InitADC();
    InitPWM();
    InitLcd();
    InitTimerServo();
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    
    u16 ADC_values[NMB_SENSORS];
    u16 average[NMB_SENSORS];
    u8 i;
    u8 j;
    
    /* The values of the magnetic field will be save in x and y */
    s16 x = 0;
    s16 y = 0;
    
    u16 angle2=0;
    
    char T[5];
    
    
    memset(ADC_values,0x00,sizeof(ADC_values));
    memset(average, 0x00,sizeof(average));

    /*
    for(i=0; i<NMB_SENSORS; i++) 
    {
        ADC_values[i]=0;
    }*/
    LcdClear();
    
#if MAGNETIC_SENSOR    
    while(1)
    {
       I2cReadData(&x, &y);
       angle2=((-atan2(x,y)*180)/3.14)+180;
        /* Computes the angle using the arctan2 which provides an angle
        * between -180° and 180°, then converts the result that is in radian
        * into degree (*180/pi) and in the end add 180° so the angle is between
        * 0° and 360° */
       //LcdPutFloat(angle2,0);
       LcdPutFloat(angle2,0);
       LcdGoto(1,2);
       LcdPutFloat(angle,0);
       __delay_ms(500);
       LcdClear();
        
    }
#endif

#ifdef BODY_GUARD_MODE
   while(1)
    { 
        
        for(j=0; j<NMB_MEASURES; j++)
        {
            /* SENSORS SAMPLING */
            for(i=0; i<NMB_SENSORS; i++)
            {
                StartADC(ADC_values);
            }
            ObjectDetection(ADC_values, average);
        }
        LcdClear();
        
        LcdPutFloat(CCP2RB, 0);
       
        //__delay_ms(1000);
        
        LcdClear();
        
        /* Set Flags */       
        ObjectReaction(average);        
        DistanceFlag(average[US]);
        
        /* react */
        
        AutoBodyGuard();

    }
#endif
               
#ifdef AUTO_FLEE
    while(1)
    { 
        
        for(j=0; j<NMB_MEASURES; j++)
        {
            /* SENSORS SAMPLING */
            for(i=0; i<NMB_SENSORS; i++)
            {
                StartADC(ADC_values);
            }
            ObjectDetection(ADC_values, average);
        }
        LcdClear();
        
        /* Set Flags */       
        ObjectReaction(average);        
        //DistanceFlag(average[US]);
        AutoFLee();

    }
    
#endif
#endif
    return 0;
}
