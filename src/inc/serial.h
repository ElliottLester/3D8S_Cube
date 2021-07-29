#pragma once
#include <main.h>

// #define BAUD 9600 //UART baudrate
#define BAUD 57600
/*Define UART parity mode*/
#define NONE_PARITY 0 //None parity
#define ODD_PARITY 1 //Odd parity
#define EVEN_PARITY 2 //Even parity
#define MARK_PARITY 3 //Mark parity
#define SPACE_PARITY 4 //Space parity

#define PARITYBIT NONE_PARITY //Set mode None parity

extern BYTE received;

void serialSetup();
void serialSendData(BYTE dat);
void serialSendString(char *s);
