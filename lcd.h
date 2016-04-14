/* 
 * File:   lcd.h
 * Author: Cyril
 *
 * Created on 7 avril 2016, 21:31
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
void LcdInit();
/*lcd_init function 
 -------------------
 */
void LcdClear();
/*lcd_clear function 
 -------------------
 */
void LcdWrite(u8);
/*lcd_write function 
 -------------------
 */
void LcdPuts(u8*);
/*lcd_puts function 
 -------------------
 */
void LcdPutch(u8);
/*lcd_putch function 
 -------------------
 */
void LcdGoto(u8);
/*lcd_goto function 
 -------------------
 */

#endif	/* LCD_H */

