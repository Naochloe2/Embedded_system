/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef BUFFER_H
#define	BUFFER_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define BUFFER_SIZE 64 // Taille du tampon circulaire, à adapter

typedef struct {
    char data[BUFFER_SIZE];
    int head; // Indice de lecture (données à lire)
    int tail; // Indice d'écriture (données à écrire)
    int count; // Nombre d'octets dans le tampon
} CircularBuffer;

CircularBuffer uartBuffer;

/*
void CircularBufferReveive(char data);
void CircularBufferTransmit();*/
void initCircularBuffer();
void addToBuffer(char data);

#endif	/* BUFFER_H */
