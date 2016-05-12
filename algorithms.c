/*
 * File:   algorithms.c
 * Author: vfortineau
 *
 * Created on May 12, 2016, 4:45 PM
 */

#include "algorithms.h"

extern struct flag flags;

void AutoFLee()
{
    if(!flags.IR_c && !flags.IR_l && !flags.IR_r)
    {
        MoveForward(SLOW);
        TurnWheels(0);
        LcdPuts("Everything is\r OKAY !");
    }
    else if(!flags.IR_c && !flags.IR_l && flags.IR_r)
    {
        MoveForward(SLOW);
        TurnWheels(-15);
        LcdPuts("Obstacle on the\r right");
    }
    else if(!flags.IR_c && flags.IR_l && !flags.IR_r)
    {
        MoveForward(SLOW);
        TurnWheels(15);
        LcdPuts("Obstacle on the\r left");
    }
    else if(flags.IR_c && flags.IR_l && !flags.IR_r)
    {
        MoveBackward(SLOW);
        TurnWheels(-15);
        LcdPuts("Let's found a way\r on the right");
        __delay_ms(1250);
    }
    else if(flags.IR_c && !flags.IR_l && flags.IR_r)
    {
        MoveBackward(SLOW);
        TurnWheels(15);
        LcdPuts("Let's found a way\r on the left");
        __delay_ms(1250);
    }
    else if(flags.IR_c && flags.IR_l && flags.IR_r)
    {
        StopMotor();
        LcdPuts("No runaway !");
    }
    else
    {
        StopMotor();
        LcdPuts("We're screwed..");
    }
}

void AutoFLeeNoLeft()
{
    if(!flags.IR_c && !flags.IR_r)
    {
        MoveForward(SLOW);
        TurnWheels(0);
        LcdPuts("Everything is\r OKAY !");
    }
    else if(!flags.IR_c && flags.IR_r)
    {
        MoveForward(SLOW);
        TurnWheels(-15);
        LcdPuts("Obstacle on the\r right");
    }
    else if(flags.IR_c && flags.IR_r)
    {
        StopMotor();
        LcdPuts("Obstacle in front !");
    }
    else if(flags.IR_c && !flags.IR_r)
    {
        TurnWheels(20);
        MoveForward(SLOW);
        LcdPuts("Avoiding obs.");
    }
    else
    {
        StopMotor();
        LcdPuts("???");
    }
}
