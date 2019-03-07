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

int main(void)
{
    SPIS_1_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    Pin_1_Write(1);
    for(;;)
    {
        uint8_t modtaget;
        while(!SPIS_1_ReadRxStatus()) {
            modtaget = SPIS_1_ReadRxData();
            SPIS_1_ClearRxBuffer();
        }
        
        /* Place your application code here. */
    }
}

CY_ISR(isr_1) {
    if(Pin_1_Read() == 1){
        Pin_1_Write(0);
    } else {
        Pin_1_Write(1);
    }
    
}

/* [] END OF FILE */
