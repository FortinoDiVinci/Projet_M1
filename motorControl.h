/* 
 * File:   
 * Author: LAPOTRE Fabian
 * Comments: this file as been created to control the motor
 * Revision history: 
 * - duty cycle calculation 
 * - settings
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

#define D_170_CM 1.9
#define D_120_CM 2.2

#define TARGET_DISTANCE_WITHOUT_DANGER 10 // this value in mV is a distance of 145 cm(value between the first car and the user)
#define MAX_DISTANCE_WITHOUT_DANGER 1.40 // this value in mV is a distance of 150 cm(value between the first car and the user)
#define MIN_DISTANCE_WITHOUT_DANGER 1.50 //  this value in mV is a distance of 140 cm(value between the first car and the user)

/* DIFFERENT SPEEDS */
#define SLOW 1
#define MEDIUM 2
#define FAST 3

#define DUTY_SLOW 0.42
#define DUTY_MEDIUM 0.60
#define DUTY_FAST 0.70

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

void MoveForward(u8 speed);
/* moveForward function 
 -------------------
 */
void MoveBackward(u8);
/* backForward function 
 -------------------
 */

#endif	/* MOTOR_CONTROL_H */