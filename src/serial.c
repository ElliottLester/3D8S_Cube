/*-------------------------------------------------------------------------------*/
/* --- STC MCU International Limited -----------------------------------*/
/* --- STC12C5Axx Series MCU UART (8-bit/9-bit)Demo ----------*/
/* If you want to use the program or the program referenced in the */
/* article, please specify in which data and procedures from STC */
/*-------------------------------------------------------------------------------*/
#include <serial.h>

__bit busy;
BYTE received = 0x0;

void serialSetup()
{
    #if (PARITYBIT == NONE_PARITY)
    SCON = 0x50; //8-bit variable UART
    #elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda; //9-bit variable UART, parity bit initial to 1
    #elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd5; //9-bit variable UART, parity bit initial to 0
    #endif
    
    TMOD = 0x20; //Set Timer1 as 8-bit auto reload mode. TH1 holds a value which is to be reloaded into TL1 each time it overflows.
    AUXR = 0x40; //Set T1x12 = 1 to remove the /12 from the timer calulation
    //TH1 = TL1 = -(FOSC/12/32/BAUD);  //Set auto-reload value
    TH1 = TL1 = -(FOSC/32/BAUD);  //Set auto-reload value
    TR1 = 1; //Timer1 start run
    ES = 1; //Enable UART interrupt
    EA = 1; //Open master interrupt switch
}


/*----------------------------
 * UART interrupt service routine
 * ----------------------------*/
//void Uart_Isr() interrupt 4 using 1
INTERRUPT_USING(Uart_Isr, 4, 1)
{
    if (RI)
    {
        RI = 0;     //Clear receive interrupt flag
        received = SBUF;
    }
    if (TI)
    {
        TI = 0;     //Clear transmit interrupt flag
        busy = 0;   //Clear transmit busy flag
    }
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void serialSendData(BYTE dat)
{
    while (busy);   //Wait for the completion of the previous data is sent
    ACC = dat;      //Calculate the even parity bit P (PSW.0)
    if (P)
    {
        #if (PARITYBIT == ODD_PARITY)
        TB8 = 0;    //Set parity bit to 0
        #elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;    //Set parity bit to 1
        #endif
    }
    else
    {
        #if (PARITYBIT == ODD_PARITY)
        TB8 = 1;    //Set parity bit to 1
        #elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;    //Set parity bit to 0
        #endif
    }
    busy = 1;
    SBUF = ACC;     //Send data to UART buffer
}


/*----------------------------
 * Send a string to UART
 * Input: s (address of string)
 * Output:None
 * ----------------------------*/
void serialSendString(char *s)
{
    while (*s)          //Check the end of the string
    {
        serialSendData(*s++); //Send current char and increment string ptr
    }
}

