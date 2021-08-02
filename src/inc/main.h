#pragma once
#include "stc12.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//#define FOSC 18432000L //System frequency 18.432MHZ
#define FOSC 24000000L //System frequency 24MHZ
//#define FOSC 23962000L //System frequency 23.962MHZ

#define M(X) ((X) * 1000000)
#define K(X) (Hz(X) * 1000)
#define Hz(X) (X)

#define CPU_CLK_HZ M(Hz(24))
#define TIMER_CLK_HZ (CPU_CLK_HZ / 12)

typedef unsigned char BYTE;
typedef unsigned int WORD;

extern char _cmd_data[32];           // Bytes recived buffer
extern uint8_t _cmd_data_index;      // Where we are upto
