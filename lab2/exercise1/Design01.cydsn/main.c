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
#include "twocomptodec.h"
#include <stdio.h>

#define FIRST_LM75 72
#define SECOND_LM75 79
#define DELAY 1000
#define BUFFER_SIZE 256

void readTemp(uint8 addr) {
    uint8 temp;                     //bruges til hel-tal
    uint8 temphalf;                 //bruges til halve, f.eks. 0."5"
    uint8 status;                   //bruges til at fejlfinde
    char buffer[BUFFER_SIZE];       //bruges til at konvertere modtaget data over i 
    
    // Prepare master to send
    status = I2C_1_MasterSendStart(addr,1);
    if(status == I2C_1_MSTR_NO_ERROR){      //tjekkes om der er fejl
        
        //læser første og anden byte, og skriver tilbage med hhv. ACK og NAK
        temp = I2C_1_MasterReadByte(I2C_1_ACK_DATA);        
        temphalf = I2C_1_MasterReadByte(I2C_1_NAK_DATA);    
        
        I2C_1_MasterSendStop(); //stopper kommunikationen
        
        // Konverter 2-complement til decimal
        int realTemp = binTwosComplementToSignedDecimal(buffer,8);
      
        // test om temperaturen er x,0 eller x,5
        uint8 half = (temphalf & 0b10000000) == 0b10000000; 
        if(half) {
        snprintf(buffer, sizeof(buffer),"Read from %d: %d,5\r\n", addr, temp);
        } else {
        snprintf(buffer, sizeof(buffer),"Read from %d: %d,0\r\n", addr, temp);
        }
        UART_1_PutString(buffer); 
    }
    else{
        I2C_1_MasterSendStop();
        UART_1_PutString("Failed to read\r\n");
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_PutString("Program starts \n");
    // Initalize I2C and UART
    I2C_1_Start();
    UART_1_Start();
   
    for(;;)
    {
        readTemp(FIRST_LM75);
        CyDelay(DELAY);
        readTemp(SECOND_LM75);
        CyDelay(DELAY);
    }
}
