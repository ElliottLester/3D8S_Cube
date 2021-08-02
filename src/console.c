#include <console.h>
#include <gpio.h>
#include <serial.h>

#include <ctype.h>
#include <string.h>
#include <utils.h>


void console_parse_command(
    const char *cmd,
    const uint8_t cmd_sz)
{
    BYTE value = 0;
    BYTE mode = MODE_NONE;
    char buf[4] = {0};

    if (cmd_sz < 3 || cmd_sz % 3 )
    {
        return;
    }
    
    char* cur = cmd;
    uint8_t sz = cmd_sz;
    
    while(sz > 0)
    {
        switch (toupper(cur[0]))
        {
            case 'D':
                mode = MODE_DATA;
                break;
            case 'L':
                mode = MODE_LATCH;
                break;
            case 'P':
                mode = MODE_PLANE;
                break;
            default:
                mode = MODE_NONE;
        }
        if (mode != MODE_NONE)
        {
            value = hex2int(cur[1]);
            value = value << 4;
            value |= hex2int(cur[2]);
            setPort(mode, value);
        }
        
        sz -= 3;
        cur +=3;
    }
}
