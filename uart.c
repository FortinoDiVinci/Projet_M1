/*
 * File:   UART.C
 * Author: fabian
 *
 * Created on April 19, 2016, 5:54 PM
 */

#include "uart.h"

/* the function GetChar() has been made to get a char from the UART */
u8 GetChar()
{
    u8 c;
    c=U1RXREG;
    return c;
}

/* This is the same fonction that above but in an other way.
void GetChar(char *c)
{
    *c=U1RXREG;
}
 */

/* the function PutChar() has been made to send a char trough the UART */
void PutChar(u8 c)
{
    while(U1STAbits.UTXBF == 1);
    U1TXREG=c;
}

/* the function PutString() has been made to send a string trough the UART */

void PutString(u8 *c)
{
    int i = 0;
    while(c!='\0')
    {
        PutChar(*c++);       
    }
}

#if 0

/* Fabian weird way of coding */

void PutString(char *c)
{
    int j=0;
    int i=strlen(c);
    j=-i;
    for(i;i>0;i--)
    { 
        PutChar(*(c+(i+j)));
        j=j+2;
    }
}

#endif