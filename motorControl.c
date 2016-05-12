/*
 * File:   motorControl.c
 * Author: Fabian
 *
 * Created on April 6, 2016, 6:38 PM
 */



#include "motorControl.h"

void MoveForward(u8 speed)
{
    CCP2RB=0;
    CCP2CON1Lbits.CCPON = 0;
    CCP2CON2Hbits.OCAEN = 1;
    CCP2CON2Hbits.OCBEN = 0;
    switch(speed)
    {
        //Sets the PWM frequency to 1 kHz.
        case SLOW:
            //Set the PWM duty cycle to 50%
            CCP2RA = (DUTY_SLOW)*CCP2PRL; 
            
            break ;
        case MEDIUM :
            //Set the PWM duty cycle to 60%
           CCP2RA = (DUTY_MEDIUM)*CCP2PRL;
            break ;
        case FAST :
            //Set the PWM duty cycle to 70%
            CCP2RA = (DUTY_FAST)*CCP2PRL; 
           /*  */
            break ;
        default :
            break ;
              /* should not happen, show and a LCD an error */  
    }   
    LATAbits.LATA7 = 1;      /* H bridge enable */
    CCP2CON1Lbits.CCPON = 1; /* Turn on MCCP module  */ 
     
}

void MoveBackward(u8 speed)
{
    CCP2RA=0;
    CCP2CON1Lbits.CCPON = 0;
    CCP2CON2Hbits.OCAEN = 0;
    CCP2CON2Hbits.OCBEN = 1;
    switch(speed)
    {
    //Sets the PWM frequency to 1 kHz.
        case SLOW:
            //Set the PWM duty cycle to 50%
            CCP2RB = (DUTY_SLOW)*CCP2PRL;    
            break ;
        case MEDIUM :
            //Set the PWM duty cycle to 60%
           CCP2RB = (DUTY_MEDIUM)*CCP2PRL; 
            break ;
        case FAST :
            //Set the PWM duty cycle to 70%
            CCP2RB = (DUTY_FAST)*CCP2PRL;
            break ;
        default :
            break ;
              /* should not happen, show and a LCD an error */  

    }  
    LATAbits.LATA7 = 1;      /* H bridge enable */
    CCP2CON1Lbits.CCPON = 1; /* Turn on MCCP module */              
}

void StopMotor()
{ 
    LATAbits.LATA7 = 1;      /* PWM enable */
    CCP2CON1Lbits.CCPON = 0;
    CCP2CON2Hbits.OCBEN = 0;
    CCP2CON2Hbits.OCAEN = 0;   
}
