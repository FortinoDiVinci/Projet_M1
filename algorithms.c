/*
 * File:   algorithms.c
 * Author: vfortineau
 *
 * Created on May 12, 2016, 4:45 PM
 */

#include "algorithms.h"

extern struct flag flags;

#ifdef BODY_GUARD
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
    if((flags.IR_c==0) && !flags.IR_l && !flags.IR_r)
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
                  LcdPuts("Clear : Please \rmove forward");
                  break;
              case 0b10:
                  MoveForward(SLOW);
                  LcdPuts("Clear : Please \rmove forward");
                  break;
          }
    }
    else if(((flags.IR_c==0)||(flags.IR_c==1)) && !flags.IR_l && flags.IR_r)
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
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("Something");
                break;
        }
    }
    else if(((flags.IR_c==0)||(flags.IR_c==1)) && flags.IR_l && !flags.IR_r)
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
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("Something on the\r left");
                break;
        }
    }
    else if((flags.IR_c==1) && !flags.IR_l && !flags.IR_r)
    {
        /* Obstacle detected on the left */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("we should change\rway, in fornt!");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("we should change\rway, in fornt!");
                break;
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("we should change\rway, in fornt!");
                break;
        }
    }
    else if((flags.IR_c==3) && !flags.IR_l && !flags.IR_r)
    {
        /* Obstacle detected on the left */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("Protecting you\r should wait");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("Protecting you\r should wait");
                break;
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("Protecting you\r should wait");
                break;
        }
    }
    else if((flags.IR_c==3) && flags.IR_l && !flags.IR_r)
    {
        /* Obstacle detected on the left */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("Protecting you\rcareful on left");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("Protecting you\rcareful on left");
                break;
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("Protecting you\rcareful on left");
                break;
        }
    }
    else if((flags.IR_c==3) && !flags.IR_l && flags.IR_r)
    {
        /* Obstacle detected on the left */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("Protecting you\rcareful on left");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("Protecting you\rcareful on left");
                break;
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("Protecting you\rcareful on left");
                break;
        }
    }
    else if((flags.IR_c==0) && flags.IR_l && flags.IR_r)
    {
        /* Obstacle detected on the left */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("we can path true\rcareful on sides");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("we can path true\rcareful on sides");
                break;
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("we can path true\rcareful on sides");
                break;
        }
    }
    else if((flags.IR_c==1) && flags.IR_l && flags.IR_r)
    {
        /* Obstacle detected on the left */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("we shoulde stop\r");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("whe should stop\r");
                break;
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("we should stop\r");
                break;
        }
    }
    else if((flags.IR_c==3) && flags.IR_l && flags.IR_r)
    {
        /* Obstacle detected on the left */
        switch(flags.US_f)
        {
            case 0b00 :
                StopMotor();
                LcdPuts("Protecting you\r we should stop");
                break;
            case 0b01 :
                MoveBackward(SLOW);
                LcdPuts("Protecting you\r we should stop");
                break;
            case 0b10 :
                MoveForward(SLOW);
                LcdPuts("Protecting you\r we should stop");
                break;
        }
    }
    else if(flags.IR_c==2)
    {
        LcdPuts("can not happened\rIR_c=2");
        __delay_ms(5000);
        LcdPuts("you have to\rrepair me");
        while(1);
    }
    else
    {
        LcdPuts("we screwed up");
        while(1);
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

void DebugUS(u16* average)
{
    LcdPuts("us: ");
    LcdGoto(5,1);
    DisplayADCIR(average[US]);
}


#endif

void ComputeAngle(u16* angle, const s16 x, const s16 y)
{
    *angle=((-atan2(x,y)*180)/3.14)+180;
        /* Computes the angle using the arctan2 which provides an angle
        * between -180° and 180°, then converts the result that is in radian
        * into degree (*180/pi) and in the end add 180° so the angle is between
        * 0° and 360° */
}