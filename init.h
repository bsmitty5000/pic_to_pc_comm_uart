#ifndef INIT_H
#define INIT_H

#include <p33FJ64MC802.h>
#include <stdio.h>
#include <stdlib.h>


// ******************************************************************************************* //
// Defines to simply UART's baud rate generator (BRG) regiser
// given the osicllator freqeuncy and PLLMODE.

#define XTFREQ          7370000             // On-board Crystal frequency
#define PLLMODE         10.75               // On-chip PLL setting (Fosc)
#define FCY             (XTFREQ*PLLMODE)/2  // Instruction Cycle Frequency (Fosc/2)
#define FPWM		39000
#define BAUDRATE         115200

//#define DELAY_105us asm volatile ("REPEAT, #3869"); Nop(); // 105uS delay

void InitUART1();
void InitClock();


#endif