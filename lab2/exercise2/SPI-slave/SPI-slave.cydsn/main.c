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
#include "stdio.h"

CY_ISR(bob);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SPIS_1_Start();
    isr_1_StartEx(bob);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    LED_Write(0);
    for(;;)
    {
        /*
        SPIS_1_ClearTxBuffer();
        uint8_t switch_state = SW_Read();
        if(switch_state == 1) {
            SPIS_1_WriteTxData('1');
            //LED_Write(1);
        } else if (switch_state == 0) {
            SPIS_1_WriteTxData('0');
            //LED_Write(0);
        }*/
    }
}

CY_ISR(bob) {
    uint8_t data = SPIS_1_ReadRxData();
    if(data == 't') {
        SPIS_1_ClearRxBuffer();
        LED_Write(1);
        SPIS_1_WriteTxData('t');
    } else if(data == 'n') {
        SPIS_1_ClearRxBuffer();
        LED_Write(0);
        SPIS_1_WriteTxData('n');
    }    
    
}

/* [] END OF FILE */
