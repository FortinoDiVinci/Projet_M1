/* 
 * File:   i2c.h
 * Author: CYRIM
 *
 * Created on 10 avril 2016, 21:11
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
void I2cInit(void);
/*I2cInit function 
 -------------------
 */
void I2cReadData(void);
/*I2cReadData function 
 -------------------
 */
u8 I2cReadByte(void);
/*I2cReadByte function 
 -------------------
 */
void I2cStop(void);








#endif	/* I2C_H */

