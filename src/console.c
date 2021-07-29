#include <console.h>
#include <gpio.h>
#include <serial.h>

char buf[10];
BYTE autoP = 0;

BYTE parseHexByte (BYTE a)
{
    BYTE result = 0;
    switch(a)
    {
        case '1':
            result = 0x1;
            break;
        case '2':
            result = 0x2;
            break;
        case '3':
            result = 0x3;
            break;
        case '4':
            result = 0x4;
            break;
        case '5':
            result = 0x5;
            break;
        case '6':
            result = 0x6;
            break;
        case '7':
            result = 0x7;
            break;
        case '8':
            result = 0x8;
            break;
        case '9':
            result = 0x9;
            break;
        case 'A':
        case 'a':
            result = 0xA;
            break;
        case 'B':
        case 'b':
            result = 0xB;
            break;
        case 'C':
        case 'c':
            result = 0xC;
            break;
        case 'D':
        case 'd':
            result = 0xD;
            break;
        case 'E':
        case 'e':
            result = 0xE;
            break;
        case 'F':
        case 'f':
            result = 0xF;
            break;
        default:
            serialSendData('0');
            return 0;
    }
    serialSendData(a);
    return result;
}

unsigned int parseMode(BYTE input)
{
    switch (input)
    {
        case 'D':
        case 'd':
            serialSendString("\r\nDATA:");
            return MODE_DATA;
        case 'P':
        case 'p':
            serialSendString("\r\nPLANE:");
            return MODE_PLANE;
        case 'L':
        case 'l':
            serialSendString("\r\nLATCH:");
            return MODE_LATCH;
        case 'S':
        case 's':
            serialSendString("\r\nAUTO:");
            return MODE_AUTO;
        default:
            serialSendString("\r\nNONE");
            return MODE_NONE;
    }
}

void consoleLoop()
{
    if (received != 0x0 && mode != MODE_AUTO)
    {
        if (mode == MODE_NONE)
        {
            mode = parseMode(received);
            hexByte = 0;
            hexChar = 0;
            if (mode == MODE_AUTO)
            {
                setPort(MODE_LATCH, 0xff);
                delay(10);
                setPort(MODE_DATA, 0x81);
                delay(10);
                setPort(MODE_LATCH, 0x81);
                delay(10);
                setPort(MODE_DATA, 0xff);
                delay(10);
                setPort(MODE_LATCH, 0x00);
                delay(10);
                setPort(MODE_DATA, 0x00);
                delay(10);
            }
        }
        else
        {
            if (hexChar == 0)
            {
                // read the high byte
                hexByte = parseHexByte(received);
                hexByte = hexByte << 4;
            }
            else if (hexChar == 1)
            {
                hexByte |= parseHexByte(received); 
                if (setPort(mode, hexByte))
                {
                    serialSendString("\r\nSet:");
                    _uitoa(hexByte, buf, sizeof(buf));
                    serialSendString(buf);
                    serialSendString("\r\n");
                }
                else 
                {
                    serialSendString("\r\nFailed");
                }
                mode = MODE_NONE;
                hexByte = 0;
                hexChar = 0;
            }
            ++hexChar;
        }
        received = 0x0;
    }
    else
    {
        delay(150);
        if (autoP == 0)
            autoP = 1;
        setPort(MODE_PLANE, autoP);
        autoP = autoP << 1;
    }
    
}
