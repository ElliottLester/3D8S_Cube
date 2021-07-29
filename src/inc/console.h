#pragma once
#include <main.h>

#define MODE_NONE 0
#define MODE_DATA 1
#define MODE_PLANE 2
#define MODE_LATCH 3
#define MODE_AUTO 4

unsigned int parseMode(BYTE input);
BYTE parseHexByte (BYTE a);
void consoleLoop();
