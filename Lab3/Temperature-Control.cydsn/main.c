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
#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include <math.h>
#include "PIDControl.h"

static char outputBuffer[256];
static float setPoint = 50; // degrees celcius. First 30 and stable, then 50 and stable.

#define SAMPLES_PER_SECOND 3
static uint16_t sampleWaitTimeInMilliseconds = 1000 / SAMPLES_PER_SECOND;


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

void readTemp(uint8 addr, char* buffer) {
    uint8 temp;                     //bruges til hel-tal
    uint8 temphalf;                 //bruges til halve, f.eks. 0."5"
    uint8 status;                   //bruges til at fejlfinde
    //char buffer[256];               //bruges til at konvertere modtaget data over i 
    
    status = I2C_1_MasterSendStart(addr,1);
    
    if(status == I2C_1_MSTR_NO_ERROR){                      //tjekkes om der er fejl
        
        //læser første og anden byte, og skriver tilbage med hhv. ACK og NAK
        temp = I2C_1_MasterReadByte(I2C_1_ACK_DATA);        
        temphalf = I2C_1_MasterReadByte(I2C_1_NAK_DATA);    
        
        I2C_1_MasterSendStop(); //stopper kommunikationen
        
        char buf_temp[256];
        for(unsigned int i = sizeof(buffer); i < sizeof(buffer); i++){
           buf_temp[i] = buffer[i];
        }
        
        int realTemp = binTwosComplementToSignedDecimal(buf_temp,8);
      
        uint8 half = (temphalf & 0b10000000) == 0b10000000; 
        if(half) {
            unsigned int temp_half = 5;
        snprintf(buffer, sizeof(buf_temp),"%d.%d\n", temp, temp_half);
          
        } else {
            unsigned int temp_null = 0;
        snprintf(buffer, sizeof(buf_temp),"%d.%d\n", temp,temp_null);
        }
        //UART_1_PutString(buffer); 
    }
    else{
        I2C_1_MasterSendStop();
        //UART_1_PutString("Failed to read\r\n");
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    I2C_1_Start();
    PWM_1_Start();
    UART_1_PutString("Program starts \n");
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    float Kp = 7.0f;
    float Ki = 2.5f/30.0f;
    float Kd = 0.0f;
    float integralMax = 3000;
    float integralMin = -3000;
    float temp = 0;
    float controlSignal = 0;
    
    char buffer[256] = {0};

    float dt = ((float)sampleWaitTimeInMilliseconds) / 1000; // dt is measured in seconds
    PIDControl_init(Kp, Ki, Kd, integralMax, integralMin, dt);
    PIDControl_changeSetPoint(setPoint);

//    UART_1_PutString("Temperature control application started\r\n");

    for(;;)
    {
        /* Place your application code here. */
        readTemp(72,buffer);
        temp = atof(buffer);
        float error = setPoint - temp;  //afstand til setpoint. Når den er konstant 0, er temp opnået.øø
        float proportionalPart = 0;
        float integralPart = 0;
        float derivativePart = 0;
        
        controlSignal = PIDControl_doStep(temp, &proportionalPart, &integralPart, &derivativePart);            
        snprintf(outputBuffer, sizeof(outputBuffer), "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f \r\n", 
                                                      setPoint, temp, error, controlSignal, Kp, Ki, Kd, 
                                                      proportionalPart, integralPart, derivativePart);
        
        if(controlSignal > 100){PWM_1_WriteCompare(100);}
        else {PWM_1_WriteCompare(controlSignal);}
        
        
        UART_1_PutString(outputBuffer);

        CyDelay(sampleWaitTimeInMilliseconds);
    }
}

/* [] END OF FILE */
