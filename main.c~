//main.c
#include "init.h"
#include "uart.h"
#include <math.h>

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings. 
//
// Make sure "Configuration Bits set in code." option is checked in MPLAB.
// This option can be set by selecting "Configuration Bits..." under the Configure
// menu in MPLAB.

_FOSC(OSCIOFNC_ON & FCKSM_CSDCMD & POSCMD_NONE);	//Oscillator Configuration (clock switching: disabled;
							// failsafe clock monitor: disabled; OSC2 pin function: digital IO;
							// primary oscillator mode: disabled)
_FOSCSEL(FNOSC_FRCPLL);					//Oscillator Selection PLL
_FWDT(FWDTEN_OFF);					//Turn off WatchDog Timer
_FGS(GCP_OFF);						//Turn off code protect
_FPOR(FPWRT_PWR1);					//Turn off power up timer

//holds the char sent
volatile char uart_rcvd_char;
//flag indicating char has been rcvd
volatile char uart_rcvd;

//stores the word
volatile char word_rcvd[80];
//starts putting the rcvd chars into the word
volatile char word_mode;


int main()
{

    //initialize everything
    uart_rcvd_char = 0;
    uart_rcvd = 0;

    word_mode = 0;
    int word_length = 0;
    int i;

    InitClock();
    InitUART1();

    while(1) {

        if (uart_rcvd == 1) {

            //word mode fills up the string then sends when a newline comes
            if (word_mode == 1) {

                //word is done, now send it and restart
                if(uart_rcvd_char == '\n') {
                    for (i = 0; i < word_length; i++) {
                        send(word_rcvd[i]);
                    }
                    word_length = 0;
                    word_mode = 0;
                }
                //just keep filling up the word
                else {
                    word_rcvd[word_length] = uart_rcvd_char;
                    word_length++;
                }
            }
            else {
                //test sendFloat
                if (uart_rcvd_char == 'f') {
                    sendFloat(3.1415);
                }
                //test sendDouble
                else if (uart_rcvd_char == 'd') {
                    sendDouble(1.618);
                }
                //test sendShort
                else if (uart_rcvd_char == 's') {
                    sendShort(42);
                }
                //test send
                else if(uart_rcvd_char == 'c') {
                    send('a');
                }
                //start up word mode
                else if(uart_rcvd_char == 'w') {
                    word_mode = 1;
                }
            }

            //reset flag
            uart_rcvd = 0;
        }
    }

    return 1;
}

void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void)
{

	// Clear interrupt flag
	IFS0bits.U1RXIF = 0;
        //let the main loop know we received a char
        uart_rcvd = 1;
        //load the char
        uart_rcvd_char = U1RXREG;
}