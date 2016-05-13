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
        TurnWheels(-12);
        LcdPuts("Obstacle on the\r right");
    }
    else if(!flags.IR_c && flags.IR_l && !flags.IR_r)
    {
        MoveForward(SLOW);
        TurnWheels(12);
        LcdPuts("Obstacle on the\r left");
    }
    else if(flags.IR_c && flags.IR_l && !flags.IR_r)
    {
        MoveBackward(SLOW);
        TurnWheels(-20);
        LcdPuts("Let's found a way\r on the right");
        __delay_ms(1250);
    }
    else if(flags.IR_c && !flags.IR_l && flags.IR_r)
    {
        MoveBackward(SLOW);
        TurnWheels(20);
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

void AutoBodyGuard(void)
{
    if(!flags.IR_c && !flags.IR_l && !flags.IR_r)
    {
        /* No obstacle detected */
          switch(flags.US_f)
          {
              case 0b00 :
                  StopMotor();
                  LcdPuts("Clear : Please \rmove forward");
                  break;
              case 0b01:
                  MoveBackward(SLOW);
                  LcdPuts("");
                  break;
              case 0b11:
                  MoveForward(SLOW);
                  LcdPuts("");
                  break;
          }
    }
    else if(!flags.IR_c && !flags.IR_l && flags.IR_r)
    {
        /* Obstacle detected on the right */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("Something on the\r right");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("Something on the\r right");
                break;
            case 0b11 :
                MoveForward(SLOW);
                LcdPuts("Something on the\r right");
                break;
        }
    }
    else if(!flags.IR_c && flags.IR_l && !flags.IR_r)
    {
        /* Obstacle detected on the left */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("Something on the\r left");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("Something on the\r left");
                break;
            case 0b11 :
                MoveForward(SLOW);
                LcdPuts("Something on the\r left");
                break;
        }
    }
}

void DebugIR(u16* average)
{
    LcdPuts("L");
    LcdGoto(3,1);
    DisplayADCIR(average[IR_L]);

    LcdGoto(9,1);
    LcdPuts("C");
    LcdGoto(11,1);
    DisplayADCIR(average[IR_C]);

    LcdGoto(1,2);
    LcdPuts("R");
    LcdGoto(3,2);
    DisplayADCIR(average[IR_R]);
}