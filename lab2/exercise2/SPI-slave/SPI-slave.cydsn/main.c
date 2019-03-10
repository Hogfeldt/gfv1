#include "project.h"
#include "stdio.h"

CY_ISR(bob);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SPIS_1_Start();
    isr_1_StartEx(bob);
    LED_Write(0);
    for(;;){}
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
    } else if(data == 's') {
        SPIS_1_ClearRxBuffer();
        uint8_t switch_state = SW_Read();
        if(switch_state == 1) {
            SPIS_1_WriteTxData('1');
        } else if (switch_state == 0) {
            SPIS_1_WriteTxData('0');
        }
    }
    
}
