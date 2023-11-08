/*
 * File:   UART_Buffer.c
 * Author: bohle
 *
 * Created on 8 novembre 2023, 14:40
 */
#include <stdio.h>
#include <stdlib.h>

#include "xc.h"
#include "UART.h"

void initUART() {
    U2BRG = 11; // (7372800 / 4) / (16*9600)?1
    U2MODEbits.UARTEN = 1; // enable UART
    U2STAbits.UTXEN = 1; // enable U1TX (must be after UARTEN)
    U2STAbits.UTXISEL = 1; // 1st mode of interrupt, go to page 7
    U2STAbits.URXISEL = 0; // interrupt flag whenever a character is received   
}

void sendUARTbuff(char buffer[]) {
    // CHECK THE BUFFER ISNT FULL - LIKE FOR SPI  <- TODO //////////////////////////////////////////////////////
    int j = 0;
    while (buffer[j] != '\0') {
        U2TXREG = buffer[j];
        j++;
    }
}

