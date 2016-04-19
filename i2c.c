#include "i2c.h"


void I2cStart(void)
{
    SSP1CON2bits.SEN = 1;           /* Initiate start condition */
    /* SSP1IF is set The MSSP module will wait the required 
     * start time before any other operation takes place. */
    /*
    SSP1BUF = 0x00;                 // loads the slave address to transmit 
    while(SSP1CON2bits.ACKSTAT);    // waits until acknowledge is received by slave 
    */
    
}


void I2cStop(void)
{

}

void I2cInit()
{
    SSP1CON1bits.SSPEN = 0;         /* Disable IC2 */
    SSP1CON1bits.SSPM = 0b0000;     /* SPI Master mode, Clock = FOSC/2 */
    SSP1ADDbits.I2CADD = 0x0;       /* Set the baud rate speed ??? */
    SSP1CON1bits.SSPEN = 1;         /* Enable I2C */
}
