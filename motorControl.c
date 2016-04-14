/*
 * File:   motorControl.c
 * Author: Fabian
 *
 * Created on April 6, 2016, 6:38 PM
 */


#include "xc.h"
#include "motorControl.h"

void MoveForward(u8 speed)
{
    LATBbits.LATB12=0;
    CCP2CON2Hbits.OCAEN = 1;
    
    switch(speed)
    {
        case SLOW:
            CCP2TMRL = 0x0000; /* Initialize timer prior to enable module. */
            CCP2PRL = 0xFFFF; /* Configure timebase period */
            break ;
        case MEDIUM :
            CCP2TMRL = 0x0000; /* Initialize timer prior to enable module. */
            CCP2PRL = 0xFFFF; /* Configure timebase period */
            break ;
        case FAST :
            
            CCP2TMRL = 0x0000; /* Initialize timer prior to enable module. */
            CCP2PRL = 0xFFFF; /* Configure timebase period */
            break ;
        default :
            break ;
              /* should not happen, show and a LCD an error */  
    }      
    CCP2CON1Lbits.CCPON =1; /* Turn on MCCP module  */                
}

void MoveBackward(u8 speed)
{
    LATBbits.LATB11=0;
    CCP2CON2Hbits.OCBEN = 1;
    
    switch(speed)
    {
        case SLOW :
            CCP2TMRL = 0x0000; /* Initialize timer prior to enable module. */
            CCP2PRL = 0xFFFF; /* Configure timebase period */
            break;
        case MEDIUM :
            CCP2TMRL = 0x0000; /* Initialize timer prior to enable module. */
            CCP2PRL = 0xFFFF; /* Configure timebase period */
            break;
        case FAST :
            
            CCP2TMRL = 0x0000; /* Initialize timer prior to enable module. */
            CCP2PRL = 0xFFFF; /* Configure timebase period */
            break;
        default :
             break; /* should not happen, show and a LCD an error */
    }
            
    CCP2CON1Lbits.CCPON =1; /* Turn on MCCP module */            
                    
    
}
