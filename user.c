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

void ObjectDetection(int* ADCValues, int* average, int count)
{
    int i;
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
            if((average[i] <= IR_DISTANCE_80)&&(average[i]) >= IR_DISTANCE_50)
            {
                obstacle[i] = 1;
            }
            if((average[i] < IR_DISTANCE_50)&&()average[i] >= IR_DISTANCE_40)
            {
                obstacle[i] = 2;
            }
            if((average[i] < IR_DISTANCE_40)&&()average[i] >= IR_DISTANCE_30)
            {
                obstacle[i] = 3;
            }
            if((average[i] < IR_DISTANCE_30)&&()average[i] >= IR_DISTANCE_20)
            {
                obstacle[i] = 4;
            }
        }
        /* RESET count */
        count = 0;
    }
}