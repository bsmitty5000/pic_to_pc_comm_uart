#include "uart.h"

void send(unsigned char data)
{
	U1TXREG = data;
	while(U1STAbits.TRMT == 0);
}

void sendShort(unsigned short data)
{
	unsigned char temp;

        //sending lsb first
	temp = data;
	U1TXREG = temp;
	while(U1STAbits.TRMT == 0);
	temp = data >> 8;
	U1TXREG = temp;
	while(U1STAbits.TRMT == 0);
	
}

void sendDouble(double data)
{
	union convUnion myUnion;
	myUnion.d = data;
/*
	U1TXREG = myUnion.bytes[3];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[2];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[1];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[0];
	while(U1STAbits.TRMT == 0);*/

        U1TXREG = myUnion.bytes[0];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[1];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[2];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[3];
	while(U1STAbits.TRMT == 0);
	
}

void sendFloat(float data)
{
	union convUnion myUnion;
	myUnion.f = data;

	U1TXREG = myUnion.bytes[0];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[1];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[2];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[3];
	while(U1STAbits.TRMT == 0);

	/*U1TXREG = myUnion.bytes[3];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[2];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[1];
	while(U1STAbits.TRMT == 0);
	U1TXREG = myUnion.bytes[0];
	while(U1STAbits.TRMT == 0);*/
	
}