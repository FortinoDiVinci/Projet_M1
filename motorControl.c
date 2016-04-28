/*
 * File:   motorControl.c
 * Author: Fabian
 *
 * Created on April 6, 2016, 6:38 PM
 */



#include "motorControl.h"

void MoveForward(u8 speed)
{
   
    CCP2CON2Hbits.OCAEN = 1;
    CCP2CON2Hbits.OCBEN = 0;
    switch(speed)
    {
        //Sets the PWM frequency to 1 kHz.
        case SLOW:
            //Set the PWM duty cycle to 70%
            CCP2RA = 7; 
            
            break ;
        case MEDIUM :
            //Set the PWM duty cycle to 80%
           CCP2RA = 5; 
            break ;
        case FAST :
            //Set the PWM duty cycle to 90%
            CCP2RA = 2; 
            break ;
        default :
            break ;
              /* should not happen, show and a LCD an error */  
    }   
  
    CCP2CON1Lbits.CCPON =1; /* Turn on MCCP module  */ 
     
}

void MoveBackward(u8 speed)
{
    CCP2CON2Hbits.OCAEN = 0;
    CCP2CON2Hbits.OCBEN = 1;
    switch(speed)
    {
    //Sets the PWM frequency to 1 kHz.
        case SLOW:
            //Set the PWM duty cycle to 70%
            CCP2RB = 7; 
            
            break ;
        case MEDIUM :
            //Set the PWM duty cycle to 80%
           CCP2RB = 5; 
            break ;
        case FAST :
            //Set the PWM duty cycle to 90%
            CCP2RB = 3; 
            break ;
        default :
            break ;
              /* should not happen, show and a LCD an error */  

    }   
    CCP2CON1Lbits.CCPON =1; /* Turn on MCCP module */            
                    
    
}
