/* 
 * File:   
 * Author: LAPOTRE Fabian
 * Comments: this file as been created to control the motor
 * Revision history: 
 */
 
#ifndef MOTOR_CONTROL_H
#define	MOTOR_CONTROL_H

// TODO Insert appropriate #include <>

#include <xc.h> // include processor files - each processor file is guarded.  
#include "user.h"
#include "lcd.h"
/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* DISTANCES */
#define D1 0x000
#define D2 0x00F
#define D3 0x0FF

/* DIFFERENT SPEEDS */
#define SLOW 1
#define MEDIUM 2
#define FAST 3

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

void MoveForward(u8 speed);
/* moveForward function 
 -------------------
 */
void BackForward(u8);
/* backForward function 
 -------------------
 */

#endif	/* MOTOR_CONTROL_H */