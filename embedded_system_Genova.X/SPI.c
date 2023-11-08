/*
 * File:   SPI.c
 * Author: bohle
 *
 * Created on 8 novembre 2023, 14:14
 */
#include "xc.h"
#include "SPI.h"

void initSPI() {
    SPI1CONbits.MSTEN = 1; // master mode
    SPI1CONbits.MODE16 = 0; // 8 bit mode
    SPI1CONbits.PPRE = 3; // 1:1 primary prescaler
    SPI1CONbits.SPRE = 3; // 5:1 secondary prescaler
    SPI1STATbits.SPIEN = 1; // enable SPI
}

void sendSPI(char data) {
    while (SPI1STATbits.SPITBF == 1); // wait until not full
    SPI1BUF = data; // send the byte containing the value data
}
