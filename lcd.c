#include "lcd.h"
void lcd_write(U8 c)
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

void lcd_clear(void)
{
	LCD_RS = 0; //  instruction mode

	lcd_write(0x01); // send the instruction
	__delay_ms(2);
}

/* write a string of chars to the LCD */

void lcd_puts( U8 * s)
{
	LCD_RS = 1;	// data mode

	while(*s) lcd_write(*s++);
}

/* write one character to the LCD */

void lcd_putch(U8 c)
{
	LCD_RS = 1;	// data mode

	lcd_write(c);
}


/*
 * Go to the specified position
 */

void lcd_goto(U8 pos)
{
	LCD_RS = 0;

	lcd_write(0x80 + pos);
}
	
/* initialise the LCD - put into 4 bit mode */

void lcd_init(void)
{
	LCD_RS = 0;	// write control bytes

	__delay_ms(30);// power on delay

	LCD_D4 = 1;	// init!	
	LCD_D5 = 1; //
	LCD_STROBE;	
	lcd_write(0x2C);// Display on, mode 2 lines
    __delay_us(10);
	lcd_write(0x0C);// display on, cursor off, blink off
    __delay_us(10);
    lcd_write(0x01); // send the instruction
	__delay_ms(2);
	lcd_write(0x07);// increment mode on, entire shift on
}

