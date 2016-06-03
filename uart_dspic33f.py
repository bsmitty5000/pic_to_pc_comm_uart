# -*- coding: utf-8 -*-
"""
Testing out UART on dsPIC33f
"""
import serial
import struct    

ser = serial.Serial(port = '/dev/ttyUSB0', 
                    baudrate = 115200,
                    bytesize = 8,
                    parity = serial.PARITY_NONE,
                    stopbits = 1,
                    timeout = 3)

op = 'x'
rcvd = 'x'

def send_word():
    print(' ')
    print(' ')
    print('Type in a word. Must be less than 80 characters.')
    print('The stop tx char will automatically be inserted.')
    
    word_length = 81
    while word_length > 80:
        word_2_send = raw_input('Enter string (< 80 char): ')
        word_length = len(word_2_send)
    
    ser.write(word_2_send)
    #using new line to tell the PIC we're done
    ser.write('\n')
    
    rcvd = ser.read(len(word_2_send))
    
    print(' ')
    print(' ')
    print('Echo from PIC: ')
    print(rcvd)

def print_options():
    print(' ')
    print(' ')
    print('q - quit')
    print('f - test float')
    print('d - test double')
    print('s - test short')
    print('c - test char')
    print('w - send word')


while op != 'q':
    
    print_options()
    op = raw_input('Enter choice: ')
    if op != 'q':
        ser.write(op)
    if op == 'f' or op == 'd':
        rcvd = ser.read(4)
        rcvd = struct.unpack('f', rcvd)
        print(rcvd)
    elif op == 's':
        rcvd = ser.read(2)
        rcvd = struct.unpack('H', rcvd)
        print(rcvd)
    elif op == 'c':
        rcvd = ser.read()
        print(rcvd)
    elif op == 'w':
        send_word()
    
print('Thanks for playing!')
ser.close()

