#include <serial.h>
#include <console.h>

#include <string.h>

#define BAUD 115200
// Due to removeing x12 and Enabling of clk doubleing on BRT_CLK 
// (see AUXR_BRTx12_bit && PCON_SMOD_bit )
#define BAUD_CLKS (CPU_CLK_HZ / 16 / BAUD)

#define PCON_SMOD0_bit (1 << 6) // Double Baud rate of the UART CLK
#define PCON_SMOD_bit (1 << 7)  // Frame Error select

#define AUXR_S1BRS_bit (1 << 0) // The baud-rate generator of UART1 select bit.
#define AUXR_BRTx12_bit (1 << 2)// Dedicated Baud-Rate Timer counter control bit.
#define AUXR_BRTR_bit (1 << 4)  // Dedicated Baud-Rate Timer run control bit

static volatile __bit _serial_busy;     // Are we currently sending data
static volatile __bit _serial_need_nl;  // Should we add a /r
static char _serial_data[32];           // Bytes recived buffer
static uint8_t _serial_data_index;      // Where we are upto in _serial_data

void serial_setup(void)
{
    EA = 0; //close master interrupt switch
    
    uint8_t temp;
    // Clear bytes recived buffer and reset index
    memset(_serial_data, 0, sizeof(_serial_data));
    _serial_data_index = 0;
    
    // clear flags
    _serial_busy = 0;
    _serial_need_nl = 0;
    
    // setup dedicated baud-rate timer clk
    BRT = (256 - BAUD_CLKS) & 0xff;
    
    // Setup UART1 into Mode 1
	SM0 = 0;
	SM1 = 1;
	SM2 = 0;


    // PCON_SMOD    = 1 // Enable double Baud rate of the UART
    // PCON_SMOD0   = 0 // Frame Error select disabled
    temp = PCON;
    temp &= ~(PCON_SMOD0_bit | PCON_SMOD_bit);
    temp |= PCON_SMOD_bit;
    PCON = temp;
    
    // AUXR_S1BRS_bit   = 1 Connect the BRT_CLK to UART1
    // AUXR_BRTR_bit    = 1 Start the BRT_CLK
    // AUXR_BRTx12_bit  = 1 BRT_CLK ticks every system clk (not every 12)
    temp = AUXR;
    temp &= ~(AUXR_S1BRS_bit | AUXR_BRTR_bit | AUXR_BRTx12_bit);
    temp |= AUXR_S1BRS_bit | AUXR_BRTR_bit | AUXR_BRTx12_bit;
    AUXR = temp;

    REN = 1; // Enable serial reception
    ES = 1; //Enable UART interrupt
    EA = 1; //Open master interrupt switch
}

void serial_dispatch_cmd()
{
    if(_cmd_data_index == 0){
        memcpy(_cmd_data, _serial_data, _serial_data_index);
        _cmd_data_index = _serial_data_index;
    }
}

INTERRUPT_USING(serial_isr, SI0_VECTOR, 1)
{
    char temp = 0x0;
    if (TI)
    {
        TI = 0;     //Clear transmit interrupt flag
        if(_serial_need_nl == 1)
        {
            SBUF='\n';
            _serial_need_nl = 0;
        }
        else 
        {
            _serial_busy = 0;
        }
    }
    
    if (RI)
    {
        RI = 0;     //Clear receive interrupt flag
        temp = SBUF;
        
        if (temp == '\r' || temp == '\n') {
            serial_dispatch_cmd();
            memset(_serial_data, 0, sizeof(_serial_data));
            _serial_data_index = 0;
        }
        else if (_serial_data_index < 31)
        {
            _serial_data[_serial_data_index] = temp;
            _serial_data_index++;
        }
    }

}

void serial_putc(char c)
{
    while (_serial_busy);   //Wait for the completion of the previous data is sent  
    _serial_busy = 1;
    
    // insert a \r before \n
    if (c == '\n') {
        _serial_need_nl = 1;
        SBUF = '\r';
        return;
    }
    
    SBUF = c;     //Send data to UART buffer
}

void serial_puts(const char *s)
{
    while (*s)          //Check the end of the string
    {
        serial_putc(*s); //Send current char and increment string ptr
        s++;
    }
}

// void serial_puts(__code const char *s)
// {
//     while (*s)          //Check the end of the string
//     {
//         serial_putc(*s++); //Send current char and increment string ptr
//     }
// }

