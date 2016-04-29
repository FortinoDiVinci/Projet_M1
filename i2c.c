/*
 * File:   i2c.c
 * Author: Vincent
 *
 * Created on April 18, 2016, 09:45
 */

#include "i2c.h"
#include "system.h" 
#include <libpic30.h>

void I2cReadData(void)
{
    static u16 mag_x = 0;
    static u16 mag_y = 0;
    /* Mode register default value is single-measurement mode */
    SSP1CON2bits.SEN = 1;                /* Start I2C */
    while(SSP1CON2bits.SEN);             /* Wait until the start transmit  */
    SSP1BUF = 0x1C;                 /* Slave address  + write bit */
    while(SSP1CON2bits.ACKDT != 1); /* Wait until the ack bit is set */
    SSP1BUF = 0x02;                 /* Mode register (0x02) */
    while(SSP1CON2bits.ACKDT != 1); /* Wait until the ack bit is set */
    SSP1BUF = 0x01;                 /* single mode measurement */
    
    __delay_ms(6);
    /* Read data */
    
    /* Read X MSB */
    mag_x = I2cReadByte() * 0x100;  /* Get the most significative 8-bits */
    
    /* Read X LSB */
    mag_x += I2cReadByte();         /* Get the least significative 8-bits */
    
    /* Moves data pointer */
    SSP1CON2bits.SEN = 1;                /* Start I2C */
    while(SSP1CON2bits.SEN);             /* Wait until the start transmit  */
    SSP1BUF = 0x1C;                 /* Slave address  + write bit */
    while(SSP1CON2bits.ACKDT != 1); /* Wait until the ack bit is set */
    SSP1BUF = 0x06;                 /* Moves the @ pointer to register 6 */
    while(SSP1CON2bits.ACKDT != 1); /* Wait until the ack bit is set */
    
    /* Read Y MSB */
    mag_y = I2cReadByte() * 0x100;  /* Get the most significative 8-bits */
    
    /* Read Y LSB */
    mag_y += I2cReadByte();         /* Get the least significative 8-bits */
}

u8 I2cReadByte(void)
{
    SSP1CON2bits.SEN = 1;                /* Start I2C */
    while(SSP1CON2bits.SEN);             /* Wait until the start transmit  */
    SSP1BUF = 0x1D;                 /* Slave address  + read bit */
    while(SSP1CON2bits.ACKSTAT != 1); /* Wait until the ack bit is set */
    SSP1BUF = 0x01;                 /* 1 byte is read  (which are X values)*/
    while(SSP1CON2bits.ACKSTAT != 1); /* Wait until the ack bit is set */
    return SSP1BUF;
}

void I2cStop(void)
{
    
}

void I2cInit()
{
    SSP1CON1bits.SSPEN = 0;         /* Disable IC2 */
    SSP1CON1bits.SSPM = 0b1000;     /* SPI Master mode, Clock = FOSC/2 */
    SSP1ADDbits.I2CADD = 0x9F;      /* Set the baud rate speed 100kb (Fosc = 32MHz) */
    SSP1STATbits.SMP = 1;           /* Slew rate (for 100kb) */
    
    SSP1CON1bits.SSPEN = 1;         /* Enable I2C */
    
    /* Configuration register A */
    SSP1CON2bits.SEN = 1;                /* Start I2C */
    while(SSP1CON2bits.SEN);             /* Wait until the start transmit  */
    SSP1BUF = 0x1C;                      /* Slave address  + write bit */
    while(SSP1CON2bits.ACKSTAT != 1);    /* Wait until the ack bit is set */
    SSP1BUF = 0x00;                      /* Configuration register A (0x00) */
    while(SSP1CON2bits.ACKSTAT != 1);    /* Wait until the ack bit is set */
    SSP1BUF = 0x71;                      /* 8-average, 15 Hz default, positive self test measurement */
    while(SSP1CON2bits.ACKSTAT != 1);    /* Wait until the ack bit is set */
    
    /* Configuration register B */
    SSP1CON2bits.SEN = 1;           /* Start I2C */
    SSP1BUF = 0x1C;                 /* Slave address  + write bit */
    while(SSP1CON2bits.ACKSTAT != 1); /* Wait until the ack bit is set */
    SSP1BUF = 0x01;                 /* Configuration register B (0x01) */
    while(SSP1CON2bits.ACKSTAT != 1); /* Wait until the ack bit is set */
    SSP1BUF = 0xA0;                 /* Gain = 5 */
    while(SSP1CON2bits.ACKSTAT != 1); /* Wait until the ack bit is set */
    
    /* Mode register default value is single-measurement mode 
     * the register 0x02 will have to be initialized for each measurement */
    SSP1BUF = 0x1C;                 /* Slave address  + write bit */
    SSP1CON2bits.SEN = 1;           /* Start I2C */
    while(SSP1CON2bits.ACKSTAT != 1); /* Wait until the ack bit is set */
    SSP1BUF = 0x02;                 /* Mode register (0x02) */
    while(SSP1CON2bits.ACKSTAT != 1); /* Wait until the ack bit is set */
    SSP1BUF = 0x01;                 /* single mode measurement */
}
