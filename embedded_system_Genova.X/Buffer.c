/*
 * File:   Buffer.c
 * Author: bohle
 *
 * Created on 8 novembre 2023, 16:32
 */


#include "xc.h"
#include "Buffer.h"
#include "SPI.h"

void initCircularBuffer() {
    uartBuffer.head = 0;
    uartBuffer.tail = 0;
    uartBuffer.count = 0;
}

void addToBuffer(char data) {
    if (uartBuffer.count < BUFFER_SIZE) {
        uartBuffer.data[uartBuffer.tail] = data;
        uartBuffer.tail = (uartBuffer.tail + 1) % BUFFER_SIZE;
        uartBuffer.count++;
    } else {
        // Tampon plein --> données ignorées
        // On peut mettre un signal pour dire que le buffer est plein --> led allumé par ex
    }
}

/*
void CircularBufferReveive(char data){
    uartBuffer.data(uartBuffer.head) = data;
    if (uartBuffer.head == BUFFER_SIZE) {
        uartBuffer.head = 0;
    }
    else {
        uartBuffer.head ++
    }
}
void CircularBufferTransmit(){
    char data = uartBuffer.data(uartBuffer.tail);
    if (uartBuffer.tail == BUFFER_SIZE) {
        uartBuffer.tail = 0;
    }
    else {
        uartBuffer.tail ++
    }
    sendSPI(data);
}

int GetBuffer_RemainingSize(){
    if (uartBuffer.head >= uartBuffer.tail){
        int data_size = uartBuffer.head - uartBuffer.tail;
        return BUFFER_SIZE - data_size;
    } 
    else {
        return uartBuffer.tail - uartBuffer.head;
    }
}*/
