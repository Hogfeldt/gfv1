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
#include <math.h>
// The next section of code borrowed from the url: 
// https://stackoverflow.com/questions/2689028/need-fastest-way-to-convert-2s-complement-to-decimal-in-c?rq=1
// =====================================================================

//I nedenstående kode udregnes to kompliment
int binTwosComplementToSignedDecimal(char binary[],int significantBits) 
{
    int power = pow(2,significantBits-1);
    int sum = 0;
    int i;

    for (i=0; i<significantBits; ++i)
    {
        if ( i==0 && binary[i]!='0')
        {
            sum = power * -1;
        }
        else 
        {
            sum += (binary[i]-'0')*power;//The -0 is needed
        }
        power /= 2;
    }

    return sum;
}

void readTemp(uint8 addr) {
    uint8 temp;                     //bruges til hel-tal
    uint8 temphalf;                 //bruges til halve, f.eks. 0."5"
    uint8 status;                   //bruges til at fejlfinde
    char buffer[256];               //bruges til at konvertere modtaget data over i 
    
    status = I2C_1_MasterSendStart(addr,1);
    
    if(status == I2C_1_MSTR_NO_ERROR){                      //tjekkes om der er fejl
        
        //læser første og anden byte, og skriver tilbage med hhv. ACK og NAK
        temp = I2C_1_MasterReadByte(I2C_1_ACK_DATA);        
        temphalf = I2C_1_MasterReadByte(I2C_1_NAK_DATA);    
        
        I2C_1_MasterSendStop(); //stopper kommunikationen
        
        int realTemp = binTwosComplementToSignedDecimal(buffer,8);
      
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
    I2C_1_Start();
    
    UART_1_Start();
    
    for(;;)
    {
        readTemp(72);
        CyDelay(1000);
        readTemp(79);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
