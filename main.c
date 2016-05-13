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
#include <math.h>
#include "algorithms.h"
#include <libpic30.h>

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

u16 main(void)
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
       angle=((-atan2(x,y)*180)/3.14)+180;
        /* Computes the angle using the arctan2 which provides an angle
        * between -180° and 180°, then converts the result that is in radian
        * into degree (*180/pi) and in the end add 180° so the angle is between
        * 0° and 360° */
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
#if 0    
    while(1){
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
        
        LcdPuts("L");
        LcdGoto(2,1);
        DisplayADCIR(average[IR_L]);
        
        LcdGoto(8,1);
        LcdPuts("C");
        LcdGoto(10,1);
        DisplayADCIR(average[IR_C]);
        
        LcdGoto(1,2);
        LcdPuts("R");
        LcdGoto(3,2);
        DisplayADCIR(average[IR_R]);
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
        
        /* Set Flags */       
        ObjectReaction(average);        
        //DistanceFlag(average[US]);
        
        
        AutoFLee();
#if 0
        // IR algo
        if(flags.IR_c)
        {
            /* All 3 sensors detects objects */
            MoveBackward(SLOW);
            LcdClear();
            LcdPuts("Object in front");
            TurnWheels(10);
            __delay_ms(1000);
        }
        else if(//flags.US_f==2 && 
                flags.IR_l && !flags.IR_c && !flags.IR_r)
        {
            /* Obstacle only on the left and target is close */
            TurnWheels(20);
            MoveForward(MEDIUM);
            LcdClear();
            LcdPuts("Object on the\rright");
        }
        else if(//flags.US_f==2 && 
                flags.IR_r && !flags.IR_c && !flags.IR_l)
        {
            /* Obstacle only on the right and target is close */
            TurnWheels(-20);
            MoveForward(MEDIUM);
            LcdClear();
            LcdPuts("Object on the\rleft");
        }
        else if(//flags.US_f==2 && 
                !flags.IR_r && !flags.IR_c && !flags.IR_l)
        {
            /* no obstacle and target is close */
            MoveForward(FAST);
            LcdClear();
            LcdPuts("Fast speed baby");
        }
#if 0
        else if(flags.US_f==1)
        {
            /* Target is lost or too far */
            MoveBackward(MEDIUM);
            LcdClear();
            LcdPuts("Going back !");
        }
        else if(flags.US_f==0)
        {
            StopMotor();
        }
#endif
        else
        {
            MoveForward(SLOW);
            LcdClear();
            LcdPuts("Error ?");
        }
        
        flags.IR_r = 0;
        flags.IR_c = 0;
        flags.IR_l = 0;
        
#endif
        
        #if 0 
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
        
        #endif
        
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
            /* should not happened :
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

#endif
    }
#endif
    return 0;
}
