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
#include "SPI.h"

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
