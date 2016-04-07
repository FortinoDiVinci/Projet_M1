/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
/* Variables types simplification */

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define s8 signed char
#define s16 signed short
#define s32 signed long

#define IR1 0 /* First infrared AN2 */
#define IR2 1 /* Second infrared AN0 */
#define IR3 2 /* Third infrared AN5 */
#define US 3 /* Ultrasound AN3 */

#define START_SAMPLING(x)( \
{ if(x==IR2) {AD1CON1bits.ADON = 0; AD1CHSbits.CH0SA = 0X00; } \
if(x==IR1) {AD1CON1bits.ADON = 0; AD1CHSbits.CH0SA = 0x02; } \
if(x==IR3) {AD1CON1bits.ADON = 0; AD1CHSbits.CH0SA = 0x05; } \
if(x==US) {AD1CON1bits.ADON = 0; AD1CHSbits.CH0SA = 0x03; } \
AD1CON1bits.ADON = 1;})

#define NMB_SENSORS 4
#define NMB_MEASURES 20

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

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void InitADC();             /* Initialize Analog to Digital Converter */
void InitPWM(void);         /* Initialize PWM */
void StartADC(u16*);        /* Samples et converts the analog inputs */
void ObjectDetection(const u16*, u16*);    /* Detect if an object is seen by one of the infrared */
