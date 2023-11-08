/*
 * File:   Interrupt.c
 * Author: bohle
 *
 * Created on 8 novembre 2023, 15:26
 */
#include <stdio.h>
#include <stdlib.h>

#include "xc.h"
#include "Interrupt.h"
#include "Buffer.h"

void __attribute__((__interrupt__, __auto_psv__))_T2Interrupt() {
    IFS0bits.T2IF = 0; //reset the flag
    T2CONbits.TON = 0; // stop timer2
    TMR2 = 0x00; //reset timer2
    // if the button is released
    LATBbits.LATB0 = 1; //switch on LED D3 for test
    if (PORTEbits.RE8 == 0x01) {
        S5_flag = 1; //flag to avoid doing too many things in the interrupt
    }
    IEC0bits.T2IE = 0x00;
}

void __attribute__((__interrupt__, __auto_psv__))_T1Interrupt() {
    IFS0bits.T1IF = 0; //reset the flag
    T1CONbits.TON = 0; // stop timer1
    TMR1 = 0x00; //reset timer1
    // if the button is released
    if (PORTDbits.RD0 == 0x01) {
        S6_flag = 1; //flag to avoid doing too many things in the interrupt
    }
    IEC0bits.T1IE = 0x00;
}

void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt() {
    IFS1bits.U2RXIF = 0; // Flag d'interruption RX UART
    char receivedData = U2RXREG;
    addToBuffer(receivedData);
}