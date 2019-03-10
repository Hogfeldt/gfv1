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

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);
void turnOnLED(void);
void turnOffLED(void);


uint8_t fromSlave = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    
    UART_1_PutString("\r\nProgram is running.\r\n");
    UART_1_PutString("L: Turn on LED on slave. \r\n");
    UART_1_PutString("N: Turn off LED on slave. \r\n");
    
    SPIM_1_Start();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
        
    }
}

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

CY_ISR(isr_1)
{
    fromSlave = SPIM_1_ReadRxData();
    char tempBuf[256];
    sprintf(tempBuf,"Recieved data: %d \r\n",fromSlave);
    UART_1_PutString(tempBuf);
    if(fromSlave == 'N')
    {
        UART_1_PutString("LED is turn off.\r\n");
    }
    else if(fromSlave == 'O')
    {
        UART_1_PutString("LED is turned on.\r\n");
    }
    SPIM_1_ClearRxBuffer();
}

void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case 'L' :
        {
            turnOnLED();
        }
        break;
        case 'N' :
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
    SPIM_1_WriteByte(0b00000001);
    UART_1_PutString("\r\nMessage sent to slave: 0b00000001\r\n");
    /*while(!SPIM_1_ReadRxStatus()){
            fromSlave = SPIM_1_ReadRxData();
            SPIM_1_ClearRxBuffer();
        }
        CyDelay(1000);*/
}

void turnOffLED()
{
    SPIM_1_WriteByte(0b00000000);
    UART_1_PutString("\r\nMessage sent to slave: 0b00000000\r\n");
    //while(!SPIM_1_ReadRxStatus()){
      //      fromSlave = SPIM_1_ReadRxData();
        //    SPIM_1_ClearRxBuffer();
        //}
        //CyDelay(1000);
}

/* [] END OF FILE */
