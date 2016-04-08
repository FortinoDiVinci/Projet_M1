/* 
 * File:   lcd.h
 * Author: CYRIM
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
#include <libpic30.h>

#ifndef LCD_H
#define	LCD_H

/******************************************************************************/
/* LCD Level #define Macros                                                   */
/******************************************************************************/
#define LCD_RS LATBbits.LATB11	// Register select
#define LCD_EN LATBbits.LATB10	// Enable
#define LCD_D4 LATAbits.LATA2	// Data bits
#define LCD_D5 LATAbits.LATA3	// Data bits
#define LCD_D6 LATBbits.LATB4	// Data bits
#define LCD_D7 LATAbits.LATA4	// Data bits
#define	LCD_STROBE	((LCD_EN = 1),(LCD_EN=0))
#define U8 unsigned char
#define U16 unsigned short
#define U32 unsigned long
#define S8 signed char
#define S16 signed short
#define S32 signed long


/******************************************************************************/
/* LCD Function Prototypes                                                   */
/******************************************************************************/
void lcd_clear(void);
void lcd_write(U8 c);
void lcd_puts(U8 * s);
void lcd_putch(U8 c);
void lcd_goto(U8 pos);
void lcd_init(void);

#endif	/* LCD_H */

