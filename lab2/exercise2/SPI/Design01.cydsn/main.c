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


uint8_t fromSlave = 76;
CY_ISR(isr_1);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    
    UART_1_PutString("\r\nProgram is running.\r\n");
    UART_1_PutString("L: Turn on LED on slave. \r\n");
    UART_1_PutString("N: Turn off LED on slave. \r\n");
    
    SPIM_1_Start();
    isr_1_StartEx(isr_1);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
        /*SPIM_1_ClearTxBuffer();
        UART_1_PutString("\r\nAsking for switch status: t\r\n");
        SPIM_1_WriteTxData('s');
        uint8_t data = SW_Read();
        char buf[256];
        sprintf(buf,"data: %d \r\n",data);
        UART_1_PutString(buf);*/
        
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
    if(fromSlave == 48){fromSlave = 0;}
    else if(fromSlave == 49){fromSlave = 1;}
    char tempBuf[256];
    sprintf(tempBuf,"Recieved data: %d \r\n",fromSlave);
    
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
    SPIM_1_ClearRxBuffer();
  
}

void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case 't' :
        {
            turnOnLED();
        }
        break;
        case 'n' :
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
    SPIM_1_ClearTxBuffer();
    SPIM_1_WriteTxData('t');
    UART_1_PutString("\r\nMessage sent to slave: t\r\n");
    /*while(!SPIM_1_ReadRxStatus()){
            fromSlave = SPIM_1_ReadRxData();
            SPIM_1_ClearRxBuffer();
        }
        CyDelay(1000);*/
}

void turnOffLED()
{
    SPIM_1_ClearTxBuffer();
    SPIM_1_WriteTxData('n');
    UART_1_PutString("\r\nMessage sent to slave: n\r\n");
    //while(!SPIM_1_ReadRxStatus()){
      //      fromSlave = SPIM_1_ReadRxData();
        //    SPIM_1_ClearRxBuffer();
        //}
        //CyDelay(1000);
}

/* [] END OF FILE */
