#ifndef UART_H
#define UART_H

#include <p33FJ64MC802.h>
#include <stdio.h>
#include <stdlib.h>

void send(unsigned char data);
void sendShort(unsigned short data);
void sendDouble(double data);
void sendFloat(float data);

//used to send floats and doubles
union convUnion
{
	double d;
	float f;
	unsigned char bytes[4];
};

#endif