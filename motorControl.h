/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

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