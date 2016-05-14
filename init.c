#include "init.h"

void InitUART1() {

    //Page 181 of dsPIC33FJ datasheet. This ties RP7 to UART1 RX
    RPINR18bits.U1RXR = 7;

    // Page 189 of dsPIC33FJ datasheet. This ties RP6 to UART1 TX
    //Table 11-2 lists the decoded values for this register pg 167
    RPOR3bits.RP6R = 3;

    U1MODEbits.STSEL = 0; //1 stop bit
    U1MODEbits.PDSEL = 0; //8 bit data, no parity
    U1MODEbits.ABAUD = 0; //auto-baud disabled
    U1MODEbits.BRGH = 0; //standard speed mode

    //check ref manual uart section for calculation
    if (BAUDRATE == 115200)
        U1BRG = 20;
    else if (BAUDRATE == 9600)
        U1BRG = 256;
    else
        U1BRG = 0xFF;

    //not using interrupts for transmit, polling instead
    //U1STAbits.UTXISEL0 = 0;
    //U1STAbits.UTXISEL1 = 0;
    //IEC0bits.U1TXIE = 1;

    //interrupt after one character is rcvd
    U1STAbits.URXISEL = 0;
    
    //clear flag then enable interrupts
    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;

    U1MODEbits.UARTEN = 1; //enable uart
    U1STAbits.UTXEN = 1; //transmitter enabled

    //IFS0bits.U1TXIF = 0;

}

void InitClock() {
    /* Configure Oscillator to operate the device at 40Mhz
       Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
       Fosc= 7.37*(43)/(2*2)=80Mhz for Fosc, Fcy = 40Mhz */
    PLLFBD = 41; // M = 43
    CLKDIVbits.PLLPOST = 0; // N1 = 2
    CLKDIVbits.PLLPRE = 0; // N2 = 2
    OSCTUN = 0;
    RCONbits.SWDTEN = 0;

    // Clock switch to incorporate PLL
    __builtin_write_OSCCONH(0x01); // Initiate Clock Switch to
    // FRC with PLL (NOSC=0b001)
    __builtin_write_OSCCONL(0x01); // Start clock switching
    while (OSCCONbits.COSC != 0b001); // Wait for Clock switch to occur

    while (OSCCONbits.LOCK != 1) {
    };
}