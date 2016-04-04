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
#include <libpic30.h>

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    InitADC();
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    int ADCValues[] = {0,0,0,0};
    int active_sensor = 0;
    while(1)
    {
        /* SENSORS SAMPLING */

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
}
