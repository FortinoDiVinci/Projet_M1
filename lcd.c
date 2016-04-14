/*
 * File:   lcd.c
 * Author: Cyril
 *
 * Created on April 7, 2016, 21:31
 */
 
#include "lcd.h"

/* initialize the LCD - put into 4 bit mode */

void LcdInit()
{
	LCD_RS = 0;	// write control bytes

	__delay_ms(30);// power on delay

	LCD_D4 = 1;	// init!	
	LCD_D5 = 1; //
	LCD_STROBE;	
	LcdWrite(0x2C);// Display on, mode 2 lines
    __delay_us(10);
	LcdWrite(0x0C);// display on, cursor off, blink off
    __delay_us(10);
    LcdWrite(0x01); // send the instruction
	__delay_ms(2);
	LcdWrite(0x07);// increment mode on, entire shift on
}

void LcdWrite(u8 c)
{
    //Write the letter bit by bit
	if(c & 0x80) LCD_D7=1; else LCD_D7=0;
	if(c & 0x40) LCD_D6=1; else LCD_D6=0;
	if(c & 0x20) LCD_D5=1; else LCD_D5=0;
	if(c & 0x10) LCD_D4=1; else LCD_D4=0;
	LCD_STROBE;
	if(c & 0x08) LCD_D7=1; else LCD_D7=0;
	if(c & 0x04) LCD_D6=1; else LCD_D6=0;
	if(c & 0x02) LCD_D5=1; else LCD_D5=0;
	if(c & 0x01) LCD_D4=1; else LCD_D4=0;
	LCD_STROBE;	
	__delay_us(40);
}

/*
 * 	Clear and home the LCD
 */

void LcdClear()
{
	LCD_RS = 0; //  instruction mode

	LcdWrite(0x01); // send the instruction
	__delay_ms(2);
}

/* write a string of chars to the LCD */

void LcdPuts( u8 * s)
{
	LCD_RS = 1;	// data mode

	while(*s) LcdWrite(*s++);
}

/* write one character to the LCD */

void LcdPutch(u8 c)
{
	LCD_RS = 1;	// data mode

	LcdWrite(c);
}


/*
 * Go to the specified position
 */

void LcdGoto(u8 pos)
{
	LCD_RS = 0;

	LcdWrite(0x80 + pos);
}
