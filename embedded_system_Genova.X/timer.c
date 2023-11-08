/*
 * File:   timer.c
 * Author: bohle
 *
 * Created on 8 novembre 2023, 14:15
 */
#include <stdio.h>
#include <stdlib.h>

#include "xc.h"
#include "timer.h"


void tmr_setup_period(int timer, int ms) {
    if (timer == TIMER1) {
        PR1 = ((float) ms * ((float) 28789 / 1000.0));
        T1CONbits.TCKPS = 0x02; //set the prescaler as 64
        T1CONbits.TCS = 0x00; // Internal clock 
        T1CONbits.TON = 0x01; // set the timer ON
    } else if (timer == TIMER2) {
        PR2 = ((float) ms * ((float) 28789 / 1000.0));
        T2CONbits.TCKPS = 0x02; //set the prescaler as 64
        T2CONbits.TCS = 0x00; // Internal clock 
        T2CONbits.TON = 0x01; // set the timer ON
    } else if (timer == TIMER3) {
        PR3 = ((float) ms * ((float) 28789 / 1000.0));
        T3CONbits.TCKPS = 0x02; //set the prescaler as 64
        T3CONbits.TCS = 0x00; // Internal clock 
        T3CONbits.TON = 0x01; // set the timer ON
    } else if (timer == TIMER4) {
        PR4 = ((float) ms * ((float) 28789 / 1000.0));
        T4CONbits.TCKPS = 0x02; //set the prescaler as 64
        T4CONbits.TCS = 0x00; // Internal clock 
        T4CONbits.TON = 0x01; // set the timer ON
    }
}

void tmr_wait_period(int timer) {
    if (timer == TIMER1) {
        IFS0bits.T1IF = 0x00;
        while (IFS0bits.T1IF == 0x00);
    } else if (timer == TIMER2) {
        IFS0bits.T2IF = 0x00;
        while (IFS0bits.T2IF == 0x00);
    } else if (timer == TIMER3) {
        IFS0bits.T3IF = 0x00;
        while (IFS0bits.T3IF == 0x00);
    } else if (timer == TIMER4) {
        IFS1bits.T4IF = 0x00;
        while (IFS1bits.T4IF == 0x00);
    }
}

void tmr_wait_ms(int timer, int ms) {
    tmr_setup_period(timer, ms);
    tmr_wait_period(timer);
}
