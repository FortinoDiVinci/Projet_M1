/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ALGORITHMS_H
#define	ALGORITHMS_H

#include "user.h"
#include "system.h"
#include "motorControl.h"
#include "servomotor.h"
#include <xc.h> // include processor files - each processor file is guarded. 
#include <libpic30.h>


void AutoFlee(void);
/* Program that allows the car to move
 * on his own and avoid obstacles */

void AutoFLeeNoLeft(void);

#endif	/* ALGORITHMS_H */

