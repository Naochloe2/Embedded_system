/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SPI_H
#define	SPI_H

#include <xc.h> // include processor files - each processor file is guarded.  

void initSPI();
void sendSPI(char data);
void sendSPIbuff(char buffer[]);

#endif	/* SPI_H */
