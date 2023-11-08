/*
 * File:   main.c
 * Author: Nabil
 *
 * Created on 24 octobre 2023, 11:44
 */


#include "xc.h"
#include "SPI.h"
#include "mainXC16.h"
#include "UART.h"
#include "timer.h"
#include "Interrupt.h"
#include "Buffer.h"

#include <stdio.h>
#include <stdlib.h>

// FOSC
#pragma config FPR = XT // Primary Oscillator Mode (XT)
#pragma config FOS = PRI // Oscillator Source (Primary Oscillator)
#pragma config FCKSMEN = CSW_FSCM_OFF // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16 // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512 // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64 // POR Timer Value (64ms)
#pragma config BODENV = BORV20 // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI // Low?side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI // High?side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

int counter_16;
int counter_char;
int S5_flag = 0;
int S6_flag = 0;


void initCircularBuffer() {
    uartBuffer.head = 0;
    uartBuffer.tail = 0;
    uartBuffer.count = 0;
}

void algorithm() {
    tmr_wait_ms(TIMER3, 7);
}

void sendSPIbuff(char buffer[]) {
    while (SPI1STATbits.SPITBF == 1); // wait until not full
    // SPI1BUF = 0x80; // position set to 1st row / 1st column
    int j = 0;
    while (buffer[j] != '\0') {
        while (SPI1STATbits.SPITBF == 1); // wait until not full
        sendSPI(buffer[j]);
        j++;
    }
}

void sendUARTbuff(char buffer[]) {
    // CHECK THE BUFFER ISNT FULL - LIKE FOR SPI  <- TODO //////////////////////////////////////////////////////
    int j = 0;
    while (buffer[j] != '\0') {
        U2TXREG = buffer[j];
        j++;
    }
}

void writingLCD(char cursor, char data) {
    sendSPI(cursor); // set the LCD cursor 1st row / 1st column
    sendSPI(data);
}

void clearLCD() {
    sendSPI(0x80);
    for (int i = 0; i < 16; i++) {
        sendSPI(' ');
    }
    sendSPI(0x80);
}

int main() {
    
    initSPI();
    initUART();
    initCircularBuffer()

    TRISBbits.TRISB0 = 0; //LED D3 as output for tests

    TRISEbits.TRISE8 = 1; //S5 as input
    TRISDbits.TRISD0 = 1; //S6 as input
    IEC0bits.T2IE = 0x01; // enable interruption T2

    // char str[16]; // à remplacer par le buffer circulaire
    char number_char[5]; // we assume that we don't go further 5 digits numbers of characters 


    char DataChar;
    char uart;
    counter_16 = 0;
    counter_char = 0;
    
    tmr_wait_ms(TIMER1, 1000);

    tmr_setup_period(TIMER4, 10);

    while (1) {
        algorithm();
        // code to handle the assignment

        // loop considering if the buffer is not empty instead of "a new character is available"
        if (uartBuffer.count > 0) {
            // We need to send DataChar by SPI to LCD instead of str
            DataChar = uartBuffer.data[uartBuffer.head]; 
            uartBuffer.head = (uartBuffer.head + 1) % BUFFER_SIZE;
            // overflow check
            if (U2STAbits.OERR == 0x01) {
                U2STAbits.OERR = 0;
            }

            // character counter
            counter_char++;
            sendSPI(0xC0);
            sprintf(str, "Char Recv: %d", counter_char);
            sendSPIbuff(str);

            uart = U2RXREG; //receive the character

            //send the character
            sendSPI((0x80 + counter_16));
            tmr_wait_ms(TIMER1, 1); // to be sure that the cursor is on the right spot

            sendSPI(uart);
            counter_16++;
            //if we finish the line
            if ((counter_16 == 17) || (uart == '\n') || (uart == '\r')) {
                counter_16 = 0;
                clearLCD();
                sendSPI(uart);
            }
            uartBuffer.count--;
        }
        // button S5 pressed
        if (PORTEbits.RE8 == 0) {
            tmr_setup_period(TIMER2, (20));
            IEC0bits.T2IE = 0x01; //enable timer2 interrupt
            T2CONbits.TON = 0x01; //starts the timer
        }
        //after antibouncing
        if (S5_flag == 1) {
            sprintf(number_char, "%d", counter_char);
            sendUARTbuff(number_char);
            S5_flag = 0;
        }

        //button S6 pressed
        if (PORTDbits.RD0 == 0) {
            tmr_setup_period(TIMER1, (20));
            IEC0bits.T1IE = 0x01; //enable timer1 interrupt
            T1CONbits.TON = 0x01; //starts the timer
        }
        //after antibouncing
        if (S6_flag == 1) {
            counter_char = 0;
            counter_16 = 0;
            clearLCD();
            sendSPI(0xC0);
            sendSPIbuff("Char Recv: 0     "); // clear the second row when S6 is pressed
            sendSPI(0x80);
            S6_flag = 0;
        }
        tmr_wait_period(TIMER4); //100 Hz frequency
    }
    return 0;
}
