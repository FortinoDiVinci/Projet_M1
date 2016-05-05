
/* 
 * File:   servomotor.h
 * Author: CYRIM
 *
 * Created on 4 mai 2016, 14:58
 */
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
#ifndef SERVOMOTOR_H
#define	SERVOMOTOR_H

#include "user.h"
/******************************************************************************/
/* Servomotor Level #define Macros                                            */
/******************************************************************************/
#define SERVO_PIN LATAbits.LATA1
#define SERVO_PERIOD 40083
/******************************************************************************/
/* Servomotor Function Prototypes                                             */
/******************************************************************************/
void TurnWheels(s16);


#endif	/* SERVOMOTOR_H */