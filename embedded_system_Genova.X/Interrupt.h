/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
  
#ifndef INTERRUPT_H
#define	INTERRUPT_H

#include <xc.h> // include processor files - each processor file is guarded.  

void __attribute__((__interrupt__, __auto_psv__))_T2Interrupt();
void __attribute__((__interrupt__, __auto_psv__))_T1Interrupt();
void __attribute__((__interrupt__, __auto_psv__))_U2RXInterrupt();