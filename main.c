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
//#include <stdlib>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "motorControl.h"
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
    InitApp();
    InitADC();
    InitPWM();
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    u16 ADC_values[] = {0,0,0,0};
    u8 i;
    while(1)
    {
        /* SENSORS SAMPLING */
        for(i=0; i<NMB_SENSORS; i++)
        {
            StartADC(ADC_values);
        }
        
        if(ADC_values[US]<D1)
        {
            moveForward(SLOW);
        }
        else if((ADC_values[US]<D2 )&&(ADC_values[US]>D1))
        {
            moveForward(MEDIUM);
        }
        else if((ADC_values[US]<D3)&&(ADC_values[US]>D2))
        {
            moveForward(FAST);
        }
    }
}
