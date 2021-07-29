#pragma once
#include "stc12.h"
#include <stdlib.h>
#include <stdbool.h>

//#define FOSC 18432000L //System frequency 18.432MHZ
//#define FOSC 24000000L //System frequency 24MHZ
#define FOSC 23962000L //System frequency 23.962MHZ

typedef unsigned char BYTE;
typedef unsigned int WORD;

// globals
extern unsigned short mode;
extern BYTE hexChar;
extern BYTE hexByte;
