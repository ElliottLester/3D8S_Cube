#include <main.h>
#include <serial.h>
#include <console.h>
#include <string.h>

char _cmd_data[32] = {0};           // Bytes recived buffer
uint8_t _cmd_data_index = 0;        // Where we are upto

void main()
{

serial_setup();
serial_puts("STC12C5A60S2\n");

while(1)
{
    if (_cmd_data_index != 0)
    {
        console_parse_command(_cmd_data,_cmd_data_index);
        memset(_cmd_data, 0, sizeof(_cmd_data));
        _cmd_data_index = 0;
    }
}

}
