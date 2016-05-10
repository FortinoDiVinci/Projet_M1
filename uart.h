/* 
 * File:   
 * Author: Fabian LAPOTRE
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UART_H
#define	UART_H


#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>
#include <string.h>
#include "user.h"

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

u8 GetChar();
void PutChar(u8);
void PutString(u8 *);

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#endif	/*  UART_H */

