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
#include <libpic30.h>

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

u8 data='b';
u16 main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();
   
    /* Program for the bracelet */
    
#ifdef PROTECTED
    
    /* Initialize IO ports and peripherals */
    InitGPIO();
    InitUART();
    InitI2c();
    InitI2cCompass();
    
    s16 x;
    s16 y;
    
    x = 0;
    y = 0;
    
    u8 i;
    for(i=0; i<=127; i++)
       PutChar('G');   
    while(1)
    {

    }
    
#endif
    
    /* Program for the bodyguard*/
    
#ifdef BODY_GUARD
    

    /* Initialize IO ports and peripherals */
    InitGPIO();
    InitADC();
    InitPWM();
    InitUART();
    InitLcd();

    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    
    u16 ADC_values[NMB_SENSORS];
    u16 average[NMB_SENSORS];
    u8 i;
    u8 j;
    char T[5];
    
    
    memset(ADC_values,0x00,sizeof(ADC_values));
    memset(average, 0x00,sizeof(average));

    /*
    for(i=0; i<NMB_SENSORS; i++) 
    {
        ADC_values[i]=0;
    }*/
    LcdClear();
    while(1)
    {
    }
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
        DisplayADCIR(average[US]);
        LcdGoto(0,2);
        
        
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
        
        
#if 0      
        if(average[US]* PIC_VOLTAGE / 1023 > D_120_CM)
        {
            LcdPuts("UP Fast");
            MoveForward(FAST);
        }
        else if((average[US]* PIC_VOLTAGE / 1023 > D_130_CM )&&( average[US]* PIC_VOLTAGE / 1023 < D_120_CM))
        {
            LcdPuts("UP Medium");
            MoveForward(MEDIUM);
        }
        else if(average[US]* PIC_VOLTAGE / 1023 > MIN_DISTANCE_WITHOUT_DANGER)
        {
            LcdPuts("UP Slow");
            MoveForward(SLOW);
        }
        else if(average[US] * PIC_VOLTAGE / 1023 < D_160_CM)
        {
            LcdPuts("down slow");
            MoveBackward(MEDIUM);
        }
        else if((average[US] * PIC_VOLTAGE / 1023 > D_160_CM)&&(average[US] * PIC_VOLTAGE / 1023 < MAX_DISTANCE_WITHOUT_DANGER))
        {
            LcdPuts("down medium");
            MoveBackward(SLOW);
        }
        else if((average[US]* PIC_VOLTAGE / 1023 > MAX_DISTANCE_WITHOUT_DANGER)&&(average[US] * PIC_VOLTAGE / 1023 < MIN_DISTANCE_WITHOUT_DANGER))
        {
            LcdPuts("stop!");
           StopMotor(); 
        }
        else
        {
            LcdPuts("error");
            /* should not happend :
             * print error on the LCD
             */       
        }
#endif
        
#if 0
        
        /* Object detection */
        
        if((average[1] * PIC_VOLTAGE / 1023 >= 0.400)&&(average[1] * PIC_VOLTAGE / 1023 <= 0.800))
        {
            LcdGoto(1,2);
            LcdPuts("Normal speed.");
            MoveForward(MEDIUM);
        }
        else if((average[1] * PIC_VOLTAGE / 1023 >= 0.800)&&(average[1] * PIC_VOLTAGE / 1023 <= 1.300) )
        {
            /* If the IR detects an object closer than 30 cm, motor slows down */
            LcdGoto(1,2);
            LcdPuts("SLOW...");
            MoveForward(SLOW);
        }
        else if(average[1] * PIC_VOLTAGE / 1023 >= 1.300)
        {
            /* If the IR detects an object closer than 10 cm, motor stops  */
            LcdGoto(1,2);
            LcdPuts("STOP !");
            StopMotor();
        }
        else 
        {
            LcdGoto(1,2);
            LcdPuts("Fast speed baby !");
            MoveForward(FAST);
        }
        
        /* ULTRASON need to be changed
        if(ADC_values[US]<D1)
        {
            MoveForward(SLOW);
        }
        else if((ADC_values[US]<D2 )&&(ADC_values[US]>D1))
        {
            MoveForward(MEDIUM);
        }
        else if((ADC_values[US]<D3)&&(ADC_values[US]>D2))
        {
            MoveForward(FAST);
        }
        */
#endif
    }
#endif
    return 0;
}
