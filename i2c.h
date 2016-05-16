/* 
 * File:   i2c.h
 * Author: Vincent
 *
 * Created on 10 April 2016, 21:11
 */
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
#ifndef I2C_H
#define	I2C_H

#include "user.h"
/******************************************************************************/
/* I2C Level #define Macros                                                   */
/******************************************************************************/
#define SDA LATBbits.LATB9	//Data bus I2C
#define SCL LATBbits.LATB8	//Clock I2C


/******************************************************************************/
/* I2C Function Prototypes                                                    */
/******************************************************************************/
void InitI2c(void);
/*I2cInit function 
 -------------------
 */
void InitI2cCompass(void);
/*I2cInitCompass function
 -------------------
 */

void I2cReadData(s16*, s16*);
/*I2cReadData function 
 -------------------
 */
void I2cReadByte(u8*);
/*I2cReadByte function 
 -------------------
 */
void I2cStop(void);
/*I2cStop function 
 -------------------
 */
void I2cIdle(void);
/*I2cIdle function 
 -------------------
 */
void I2cStart(void);
/*I2cStart function 
 -------------------
 */
s8 I2cACK(void);
/*I2cACK function 
 -------------------
 */
void I2cMode(void);
/*I2cMode function 
 -------------------
 */
#endif	/* I2C_H */

