/* 
 * File:   lcd.h
 * Author: Cyril
 *
 * Created on 7 April 2016, 21:31
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
#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "user.h"
#include <libpic30.h>


#ifndef LCD_H
#define	LCD_H

/******************************************************************************/
/* LCD Level #define Macros                                                   */
/******************************************************************************/
#define LCD_RS LATBbits.LATB13	// Register select
#define LCD_EN LATBbits.LATB10	// Enable
#define LCD_D4 LATAbits.LATA2	// Data bits
#define LCD_D5 LATAbits.LATA3	// Data bits
#define LCD_D6 LATBbits.LATB4	// Data bits
#define LCD_D7 LATAbits.LATA4	// Data bits
#define	LCD_STROBE	((LCD_EN = 1),(LCD_EN=0))


/******************************************************************************/
/* LCD Function Prototypes                                                   */
/******************************************************************************/
void InitLcd();
/*LcdInit function 
 -------------------
 */
void LcdClear();
/*LcdClear function 
 -------------------
 */

void LcdWriteCtrl(u8);
/*LcdWrite function for instruction
 -------------------
 */

void LcdWriteData(u8);
/*LcdWrite function for data 
 -------------------
 */
void LcdPuts(u8*);
/*LcdPuts function 
 -------------------
 */
void LcdPutch(u8);
/*LcdPutch function 
 -------------------
 */
void LcdGoto(u8, u8);
/*LcdGoto function 
 -------------------
 */
void LcdOnOff(u8);
/*LcdOnOff function 
 -------------------
 */
void LcdPutFloat(float,u8);
/*LcdPutFloat function 
 -------------------
 */
void LcdConvAscii(u32);
/*LcdConversionAscii function
    -------------------
 */
#endif	/* LCD_H */

