#include "project.h"
#include "stdio.h"

CY_ISR(bob);    //SPI slave interrupt

int main(void)
{
    CyGlobalIntEnable;  //Enable global interrupts
    SPIS_1_Start();     //SPI slave initieres
    isr_1_StartEx(bob); //SPI slave interrupt
    LED_Write(0);       //LED slukkes
    for(;;){}           //uendelig for-løkke
}

/*  Nedenstående interruptrutine aktiveres, når SPI slaven modtager noget fra masteren.  */
CY_ISR(bob) {
    uint8_t data = SPIS_1_ReadRxData();     //læst data fra SPI master lægges over i variabel.
    
    /*  Hvis der modtages "t" eller "n", sendes det samme retur til master.
        Hvis der modtages "s", tjekkes switch-status og statusen sendes tilbage.
        Løbende cleares Recieve bufferen for SPI slaven, så den er klar til at modtage nyt data.
    */
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
