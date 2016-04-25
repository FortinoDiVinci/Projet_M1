/*
 * File:   lcd.c
 * Author: Cyril
 *
 * Created on April 7, 2016, 21:31
 */
 
#include "lcd.h"

/* This variable is used for the conversion from hexa to ASCII */
const char *h="0123456789ABCDEF";


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
void LcdPutFloat(float data,u8 decimal)
{
    
    u8 i;
    u32 dec, dec10=10;
    
    /* Display a sign minus if data is negative and set data as positive */
    if(data<0)
    {
        LcdPutch('-');
        data*=-1;
        
    }
    /* dec10=10^(decimal+1) */
    for(i=0;i<decimal;i++)
    {
        dec10*=10;
    }
    /* Decimal part with (decimal+1) figures */
    dec=dec10*(data-(u32)data);
    /* Round to upper value */
    if(dec%10>=5)
    {
        dec+=10;
    }
    /* If Overflow, add 1 to the entire part of data and 
       set the decimal part to 0 */
    if(dec>dec10-1)
    {
        data+=1;
        dec=0;
    }
    /* Display the entire part of data */
    LcdConvAscii(data);
    
    /*In the case  we want to display the decimal part */
    if(decimal!=0)
    {
        /* Display a coma */
        LcdPutch(',');
        /* dec10=10^(decimal-1)*/
        dec10/=100;
        /* The decimal part of dec is set to (decimal) figures*/
        dec/=10;
        while(dec/dec10==0 && decimal>1)
        {
            /* Display the zero on the left of the decimal part */
            LcdPutch('0');
            dec10/=10;
            decimal--;
        }
        LcdConvAscii(dec);
    }
}
void LcdConvAscii(u32 number)
{
    u8 i=0;//counter
    static u8 buf[32];
    
    
    /* Fill buff with the corresponding  ASCII code of each figure of data */
    do{
       /*Conversion Hexa/ASCII from the end to the beginning*/
        buf[i]=h[number%10];
        number/=10;
        i++;
    }while(number);
    
    /* Display the buffer from the end to the beginning */
    do{
        i--;
        LcdPutch(buf[i]);
    }while(i>0);
    
}