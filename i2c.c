/*
 * File:   i2c.c
 * Author: Vincent
 *
 * Created on April 18, 2016, 09:45
 */

#include "i2c.h"
#include "system.h" 
#include <libpic30.h>

void I2cReadData(u16* mag_x, u16* mag_y)
{
    u8 coordinates[6];
    
    /* Read data */
    
    I2cReadByte(coordinates);
    
    *mag_x = coordinates[0] * 0x100 + coordinates[1];
    *mag_y = coordinates[4] * 0x100 + coordinates[5];

    /* Moves data pointer */
    I2cStart();
    
    SSP1BUF = 0x3C;                      /* Slave address  + write bit */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */
    
    SSP1BUF = 0x03;                      /* Moves the @ pointer to register 3 */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */
 
#if 0    
    /* Read X MSB */
 //   *mag_x = (u16)I2cReadByte() * 0x100; /* Get the most significative 8-bits */       
 //   I2cStop();
    
    /* Read X LSB */
 //   *mag_x += (u16)I2cReadByte();        /* Get the least significative 8-bits */
 //   I2cStop();
    
    /* Moves data pointer */
    I2cStart();
    SSP1BUF = 0x3C;                      /* Slave address  + write bit */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */
    SSP1BUF = 0x06;                      /* Moves the @ pointer to register 6 */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    
    /* Read Y MSB */
    *mag_y = (u16)I2cReadByte() * 0x100; /* Get the most significative 8-bits */
    I2cStop();
    
    /* Read Y LSB */
    *mag_y += (u16)I2cReadByte();         /* Get the least significative 8-bits */
    I2cStop();
#endif
}

void I2cReadByte(u8* T)
{
    u8 i;
    I2cStart();
    
    SSP1BUF = 0x3D;                      /* Slave address  + read bit */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    SSP1BUF = 0x06;                      /* 1 byte is read  (which are X values)*/
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    for(i=0; i<6; i++)
    {
        SSP1CON2bits.RCEN = 1;               /*  */
        IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
        while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
        if(i==5)
        {
            SSP1CON2bits.ACKDT = 1;
        }
        else
        {
            SSP1CON2bits.ACKDT = 0;
            IFS1bits.SSP1IF = 0;             /* Clears the interruption  */
            while(!IFS1bits.SSP1IF);         /* Waits until the end of transmission */
        }

        T[i] = SSP1BUF;
    }
    // SSP1CON2bits.RCEN = 1;               /*  */

    I2cStop();

//    return SSP1BUF;
}

void I2cIdle(void)
{
    while((SSP1CON2 & 0x1F) || (SSP1STATbits.R_W));
    /*
     * Acknowledge sequence is Idle
     * Receive is Idle
     * Stop condition is Idle
     * Repeated Start condition is Idle
     * Clock stretching is disabled
     *           or
     * Transmit is not in progress
     */
}

void I2cStart(void)
{
    SSP1CON1bits.WCOL = 0; 
    I2cIdle();                           /* Waits */
    IFS1bits.SSP1IF = 0;
    SSP1CON2bits.SEN = 1;                /* Starts I2C */
    while(SSP1CON2bits.SEN);             /* Waits until the start transmit  */
}

void I2cStop(void)
{
    SSP1CON2bits.PEN = 1;                /* Ends transmission */
    while(SSP1CON2bits.PEN);             /* Waits until the transmission stops  */    
}

void I2cInit(void)
{
    //SSP1CON1bits.SSPEN = 0;         /* Disable IC2 */
    SSP1ADDbits.I2CADD = 0x9F;      /* Set the baud rate speed 100kb (Fosc = 32MHz) */
    
    SSP1CON1bits.WCOL = 0; 
    SSP1CON1bits.SSPOV = 0;
    SSP1CON1bits.CKP = 0;
    SSP1CON1bits.SSPM = 0b1000;     /* I2C Master mode, Clock = FOSC/2 */
    SSP1CON1bits.SSPEN = 1;         /* Enable I2C */
    
    SSP1CON2 = 0x00;
    
    SSP1STAT = 0x0;
    SSP1STATbits.SMP = 1;           /* Slew rate disabled for standard speed (100kb) */
}
   
s8 I2cACK(void)
{
    if(SSP1CON2bits.ACKSTAT)        /* If the communication failed */
    {
        return 1;
    }
    else return 0;
}

void I2cInitCompass(void)
{  
    /* Configuration register A */
    I2cStart();
    
    SSP1BUF = 0x3C;                      /* Slave address  + write bit */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    SSP1BUF = 0x00;                      /* Configuration register A (0x00) */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    SSP1BUF = 0x71;                      /* 8-average, 15 Hz default, positive self test measurement */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    I2cStop();
    
    /* Configuration register B */
    I2cStart();

    SSP1BUF = 0x3C;                      /* Slave address  + write bit */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    SSP1BUF = 0x01;                      /* Configuration register B (0x01) */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    SSP1BUF = 0xA0;                      /* Gain = 5 */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    I2cStop();
    
    /* Mode register continuous mode */
    I2cStart();
 
    SSP1BUF = 0x3C;                      /* Slave address  + write bit */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */
 
    SSP1BUF = 0x02;                      /* Mode register (0x02) */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    SSP1BUF = 0x00;                      /* continuous measurement mode */
    IFS1bits.SSP1IF = 0;                 /* Clears the interruption  */
    while(!IFS1bits.SSP1IF);             /* Waits until the end of transmission */
    if(I2cACK()) return;                 /* detects communication failure */

    I2cStop();    
}