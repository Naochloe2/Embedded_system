/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef BUFFER_H
#define	BUFFER_H

#include <xc.h> // include processor files - each processor file is guarded.  

/*
void CircularBufferReveive(char data);
void CircularBufferTransmit();*/
void initCircularBuffer();
void addToBuffer(char data);

#endif	/* BUFFER_H */
