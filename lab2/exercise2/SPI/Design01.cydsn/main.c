/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

CY_ISR_PROTO(ISR_UART_rx_handler);  //UART interrupt
void handleByteReceived(uint8_t byteReceived);
void turnOnLED(void);
void turnOffLED(void);


uint8_t fromSlave;  //global variable til at læse i interruptrutiner fra SPI slaven.
CY_ISR(isr_1);      //SPI interrupt

int main(void)
{
    CyGlobalIntEnable;                          //Enable global interrupts.
    isr_uart_rx_StartEx(ISR_UART_rx_handler);   //UART interrupt enabled
    UART_1_Start();                             //UART initieres.
    
    /*I starten af programmet udskrives dette:*/
   
    UART_1_PutString("\r\nProgram is running.\r\n");
    UART_1_PutString("t: Turn on LED on slave. \r\n");
    UART_1_PutString("n: Turn off LED on slave. \r\n");
    
    SPIM_1_Start();                             //SPI master initieres.       
    isr_1_StartEx(isr_1);                       //SPI master interrupt initieres.
    
    /*I nedenstående for-loop, som kører i uendelig løkke, 
    spørges der hvert sekund efter switch-status på SPI slaven.*/
    for(;;)
    {
        SPIM_1_ClearTxBuffer();                 //SPI master clearer transmitter bufferen.
        UART_1_PutString("\r\nAsking for switch status: t\r\n");    //tekst til UARTen.
        SPIM_1_WriteTxData('s');                //Der transmiteres char'en "t" til slaven.
        CyDelay(1000);                          //delay på 1 sekund
    }
}

/*UART interrupt rutine, der håndtere kommunikation med samme PSoC, som agere SPI master.*/
CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize(); //Der spørges efter størrelsen af data, der skal læses
    while (bytesToRead > 0)                         //Hvis der er noget, går den ind i while-løkken
    {
        uint8_t byteReceived = UART_1_ReadRxData(); //Data læses og lægges i variable
        UART_1_WriteTxData(byteReceived);           // echo back
        
        handleByteReceived(byteReceived);           //funktionskald på baggrund af modtaget data.
        
        bytesToRead--;
    }
}

/*Nedenstående interruptrutine håndtere, når SPI masteren modtager data.*/
CY_ISR(isr_1)
{
    fromSlave = SPIM_1_ReadRxData();   //Data modtaget læses
    
    /*Hvis der er modtaget 48, overskrives værdien til 0. Det skyldes at 48 er char '0'.
    Hvis der er modtaget 49, overskrives variablen til 1. Det skyldes at 49 er char '1'.    
    */
    if(fromSlave == 48){fromSlave = 0;}
    else if(fromSlave == 49){fromSlave = 1;}
    
    char tempBuf[256];                  //buffer til konvertering
    sprintf(tempBuf,"Recieved data: %d \r\n",fromSlave);    //modtaget integer konverteret til char.
    
    /*  Udskrift til bruger via UART. */
    if(fromSlave == 'n')
    {
        UART_1_PutString("LED is turn off.\r\n");
    }
    else if(fromSlave == 't')
    {
        UART_1_PutString("LED is turned on.\r\n");
    }
    else{
        UART_1_PutString(tempBuf);
    }
    SPIM_1_ClearRxBuffer();             //Recieve buffer cleares.
  
}

/*  Nedenstående funktion er en state machine, som respondere på inputtet i UARTen. 
    Herfra kaldes andre funktioner, som skal agere på baggrund af inputtet i UARTen.
*/
void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case 't' :          //er der indtastet t til UARTen, kaldes funktionen "turnOnLED()"
        {
            turnOnLED();
        }
        break;
        case 'n' :          //er der indtastet n til UARTen, kaldes funktionen "turnOffLED()"
        {
            turnOffLED();
        }
        break;
        default :
        {
            // nothing
        }
        break;
    }
}

void turnOnLED()
{
    SPIM_1_ClearTxBuffer();     //Transmitterbuffer cleares, så der kan sendes ny data.
    SPIM_1_WriteTxData('t');    // der sendes et 't' til slaven.
    UART_1_PutString("\r\nMessage sent to slave: t\r\n");   //Status til UARTen og dermed brugeren.
    
}

void turnOffLED()
{
    SPIM_1_ClearTxBuffer();     //Transmitterbuffer cleares, så der kan sendes ny data
    SPIM_1_WriteTxData('n');    // der sendes et 'n' til slaven, for "not turn on".
    UART_1_PutString("\r\nMessage sent to slave: n\r\n");   //Status til UARTen og dermed brugeren.
    
}

/* [] END OF FILE */
