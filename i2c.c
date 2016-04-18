#include "i2c.h"


void I2cStart(void)
{
	
}


void I2cStop(void)
{

}
/*
void I2cInit(u16)
{
   int temp;

   // I2CBRG = 194 for 10Mhz OSCI with PPL with 100kHz I2C clock
   I2C1BRG = BRG;
   I2C1CONbits.I2CEN = 0;	// Disable I2C Mode
   I2C1CONbits.DISSLW = 1;	// Disable slew rate control
   IFS1bits.MI2C1IF = 0;	 // Clear Interrupt
   I2C1CONbits.I2CEN = 1;	// Enable I2C Mode
   temp = I2CRCV;	 // read buffer to clear buffer full
   reset_i2c_bus();	 // set bus to idle
}
*/