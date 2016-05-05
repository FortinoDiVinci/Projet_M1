#include "servomotor.h"

u16 servoPulseWidth;


void TurnWheels(s16 degree)
{
    T1CONbits.TON = 0; //Stop Timer1 
    servoPulseWidth=20*degree+3006;
    T1CONbits.TON = 1; //Start Timer1 
}
