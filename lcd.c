/*
 * File:   lcd.c
 * Author: Cyril
 *
 * Created on April 7, 2016, 21:31
 */
 
#include "lcd.h"

/* initialize the LCD - put into 4 bit mode */
/*
void LcdInit()
{
    
    __delay_ms(40);// power on delay
	LCD_RS = 0;	// write control bytes

	LCD_D4 = 1;	// initialize
	LCD_D5 = 1; //
	LCD_STROBE;	
	LcdWrite(0x2C); // Display on, mode 2 lines
    __delay_us(40);
	LcdWrite(0x0C);// display on, cursor off, blink off
    __delay_us(40);
    LcdWrite(0x01); // send the instruction
	__delay_ms(2);
	LcdWrite(0x07);// increment mode on, entire shift on
}*/

void LcdInit(void)
{
    LCD_RS = 0;	// write control bytes
    __delay_ms(15);	// power on delay
    LCD_D7 = 0; // attention!
    LCD_D6 = 0;
    LCD_D5 = 1;
    LCD_D4 = 1;
    LCD_STROBE;
    __delay_ms(5);
    LCD_STROBE;
    __delay_us(100);
    LCD_STROBE;
    __delay_ms(5);
    LCD_D7 = 0;	// set 4 bit mode
    LCD_D6 = 0;
    LCD_D5 = 1;
    LCD_D4 = 0;
    LCD_STROBE;
    __delay_ms(40);
    LcdWriteCtrl(0x28);	// 4 bit mode, 1/16 duty, 5x8 font
    LcdWriteCtrl(0x08);	// display off
    LcdWriteCtrl(0x0C);	// display on, blink cursor on
    LcdWriteCtrl(0x06);	// entry mode cursor off
}

void LcdWriteCtrl(u8 c)

{
    LCD_RS=0; //Instruction mode
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
void LcdWriteData(u8 d)

{
    LCD_RS=1; //Data mode
    //Write the letter bit by bit
	if(d & 0x80) LCD_D7=1; else LCD_D7=0;
	if(d & 0x40) LCD_D6=1; else LCD_D6=0;
	if(d & 0x20) LCD_D5=1; else LCD_D5=0;
	if(d & 0x10) LCD_D4=1; else LCD_D4=0;
	LCD_STROBE;
	if(d & 0x08) LCD_D7=1; else LCD_D7=0;
	if(d & 0x04) LCD_D6=1; else LCD_D6=0;
	if(d & 0x02) LCD_D5=1; else LCD_D5=0;
	if(d & 0x01) LCD_D4=1; else LCD_D4=0;
	LCD_STROBE;	
	__delay_us(40);
}
/*
 * 	Clear and home the LCD
 */

void LcdClear()
{
	LcdWriteCtrl(0x01); // send the instruction
	__delay_ms(2);
}

/* write a string of chars to the LCD */

void LcdPuts( u8 * s)
{
	while(*s!='\0')
    {
       if(*s=='\r')
       {
            LcdGoto(1,2);
       }
       else
       {
            LcdWriteData(*s); //écriture sur le LCD d'un caractère du message.
       }
        s++;
    }
        
}

/* write one character to the LCD */

void LcdPutch(u8 c)
{
	LcdWriteData(c);
}


/*
 * Go to the specified position
 */

void LcdGoto(u8 posX, u8 posY)
{
	
    if (posY==1)
        LcdWriteCtrl(0x80+posX-1); //positionne la ligne 1 aux coordonnées (x, 1).
    if (posY==2)
        LcdWriteCtrl(0xC0+posX-1); //positionne la ligne 2 aux coordonnées (x, 2).
}

void LcdOnOff(u8 onoff)
{
    
    if(onoff==1)
    {       
        /* LCD on */
        LcdWriteCtrl(0x0C);
        
    }
    else
    {
         /* LCD off */
         LcdWriteCtrl(0x08);
    }
    
}