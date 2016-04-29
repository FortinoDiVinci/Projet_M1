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

u16 main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitGPIO();
    InitADC();
    InitPWM();
    LcdInit();
    //LcdClear();
    //LcdPuts("Project in\rprogress... :)");
    
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    
    u16 ADC_values[NMB_SENSORS];
    u16 average[NMB_SENSORS];
    u8 i;
    u8 j;
    memset(ADC_values,0x00,sizeof(ADC_values));
    memset(average, 0x00,sizeof(average));
    /*
    for(i=0; i<NMB_SENSORS; i++) 
    {
        ADC_values[i]=0;
    }*/
    
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
        DisplayADCIR(average[1]);
        
        __delay_ms(5);
        

        
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
    }
    return 0;
}
