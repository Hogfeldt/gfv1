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

enum driveMode{full};

enum driveMode mode;    

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);
void decreaseSpeed(void);
void increaseSpeed(void);
void driveForwards(void);
void driveBackwards(void);
void ChangeDriveMode(void);
void stop(void);


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    
    
    UART_1_PutString("DC-Motor-PWM application started\r\n");
    UART_1_PutString("0: Stop\r\n");
    UART_1_PutString("1: Drive forwards\r\n");
    UART_1_PutString("2: Drive backwards\r\n");
    UART_1_PutString("q: Decrease speed\r\n");
    UART_1_PutString("w: Increase speed\r\n");

    mode = full;
    
    for(;;)
    {
        /* Place your application code here. */
        Pin_1_a_Write(1);  
        Pin_1_b_Write(0);
        Pin_2_a_Write(0);
        Pin_2_b_Write(0);
        CyDelay(10);
        
        Pin_1_a_Write(0);  
        Pin_2_a_Write(1);
        CyDelay(10);
          
        Pin_2_a_Write(0);
        Pin_1_b_Write(1);
        CyDelay(10);
        
        Pin_1_b_Write(0);
        Pin_2_b_Write(1);
        CyDelay(10);
        
        Pin_2_b_Write(0); // secure overlap
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

void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case 'q' :
        {
            decreaseSpeed();
        }
        break;
        case 'w' :
        {
            increaseSpeed();
        }
        break;
        case '1' :
        {
            driveForwards();
        }
        break;
        case '2' :
        {
            driveBackwards();
        }
        break;
        case 'C' :
        {
            ChangeDriveMode();
        }
        break;
        case '0' :
        {
            stop();
            
        }
        break;
        default :
        {
            // nothing
        }
        break;
    }
}

void decreaseSpeed()
{
    UART_1_PutString("Decreasing speed\r\n");
}

void increaseSpeed()
{
    UART_1_PutString("Increasing speed\r\n");
}

void driveForwards()
{
    UART_1_PutString("Set direction: forwards\r\n");
}

void driveBackwards()
{
    UART_1_PutString("Set direction: backwards\r\n");
}

void ChangeDriveMode()
{    
}

void stop()
{
    UART_1_PutString("Stop\r\n");
}

/* [] END OF FILE */
