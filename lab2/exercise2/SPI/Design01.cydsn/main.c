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

uint8_t fraPer;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SPIM_1_Start();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint8_t per = 255;
    
    for(;;)
    {
        /* Place your application code here. */
        SPIM_1_WriteByte(per);
        while(!SPIM_1_ReadRxStatus()){
            fraPer = SPIM_1_ReadRxData();
            SPIM_1_ClearRxBuffer();
        }
        CyDelay(1000);
        
    }
}

CY_ISR(isr_1)
{
    
}

/* [] END OF FILE */
