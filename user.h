/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#ifndef USER_H
#define	USER_H

/* If body_guard car define BODY_GUARD
 * If person to protect define PROTECTED 
 * DO NOT DO BOTH */

#define BODY_GUARD
//#define PROTECTED

/* Variables types simplification */

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define s8 signed char
#define s16 signed short
#define s32 signed long

#define PIC_VOLTAGE 3.25

#define IR1 0 /* First infrared AN2 */
#define IR2 1 /* Second infrared AN0 */
#define IR3 2 /* Third infrared AN5 */
#define US 3  /* Ultrasound AN3 */

/* HF */

#define NUMBER_DATA_HF 2


#define START_SAMPLING(x)( \
{ if(x==IR2) {AD1CON1bits.ADON = 0; AD1CHSbits.CH0SA = 0X00; } \
if(x==IR1) {AD1CON1bits.ADON = 0; AD1CHSbits.CH0SA = 0x02; } \
if(x==IR3) {AD1CON1bits.ADON = 0; AD1CHSbits.CH0SA = 0x05; } \
if(x==US) {AD1CON1bits.ADON = 0; AD1CHSbits.CH0SA = 0x03; } \
AD1CON1bits.ADON = 1;})

#define NMB_SENSORS 4
#define NMB_MEASURES 10

/* INFRARED LEVELS */
#define IR_DISTANCE_6 0x03D /* 3,1V */
#define IR_DISTANCE_7 0x03B1 /* 3V */
#define IR_DISTANCE_8 0x0362 /* 2,75V */
#define IR_DISTANCE_10 0x02F4 /* 2,4V */
#define IR_DISTANCE_15 0x01F8 /* 1,6V */
#define IR_DISTANCE_20 0x01A9 /* 1,35V */
#define IR_DISTANCE_25 0x015A /* 1,1V */
#define IR_DISTANCE_30 0x011B /* 0,9V */
#define IR_DISTANCE_40 0x00EC /* 0,75V */
#define IR_DISTANCE_50 0x00BD /* 0,6V */
#define IR_DISTANCE_80 0x007E /* 0,4V */

#define PWM_FREQ 80000        /* 80kHz */
#define PWM_PER_SYS 400
/* TODO Application specific user parameters used in user.c may go here */

struct flag{
    u8 IR_l : 1; /* 1 bit for the left IR */
    u8 IR_c : 1; /* 1 bit for the front IR */
    u8 IR_r : 1; /* 1 bit for the right IR */
    /* 3 bits for the distance detected by the ultrasound sensor */
    u8 US_f : 1; /* Target is too close, needs to move Forward */
    u8 US_m : 1; /* Target is at a correct Middle position keep speed */
    u8 US_b : 1; /* Target is too far, needs to move Backward */
};

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitGPIO(void);             /* I/O and Peripheral Initialization */
void InitADC(void);                  /* Initialize Analog to Digital Converter */
void InitPWM(void);              /* Initialize PWM */
void StartADC(u16*);             /* Samples et converts the analog inputs */
void ObjectDetection(const u16*, u16*);    /* Detect if an object is seen by one of the infrared */
void ObjectReaction(const u16*); /* Set the flags according to IR dection */
void DisplayADCIR(u16);          /* Convert the data into a voltage level */
void InitUART(void);
void InitTimerServo(void);           /* Initialization of the timer for the servomotor */

#endif USER_H