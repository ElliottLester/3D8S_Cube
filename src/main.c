#include <main.h>
#include <serial.h>
#include <console.h>

// globals
unsigned short mode = 0;
BYTE hexChar = 0;
BYTE hexByte = 0;


void main()
{

//serialSendData("\r\nSTC12C5A60S2\r\n");
while(1)
{
    serialSetup();
    consoleLoop();
}
    
}
