/* ========================================
 *
 * Copyright Eladio Barrio Querol
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Eladio Barrio.
 *
 * ========================================
*/
#include "project.h"
#include "MAX7219.h"
void test_borra_matriz_LED(void);
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    LCD_Start();
    LCD_Position(0u, 0u);
    LCD_PrintString("-MAX7219 TEST 1-");
    LCD_Position(1u, 0u);
    LCD_PrintString("Command = ");
    LCD_Position(1u, 10u);
    LCD_PrintInt16(0);
  
    max_init();
    max_test();
    max_delete();

    
    for(;;)
    {   
        max_write_house();
        CyDelay(1000);
        max_write_down();
        CyDelay(1000);
        max_write_rigth();
        CyDelay(1000);
        max_write_left();
        CyDelay(1000);
        max_write_up();
        CyDelay(1000);
    }
}
void test_borra_matriz_LED(void){
    unsigned char i;
    unsigned short com;
    for ( i = 1; i < 9; i ++){
        com = 0x0000 |((unsigned short)i<<8);
        LCD_Position(1u, 10u);
        LCD_PrintInt16(com);
        SPIM_1_WriteTxData(com);// & 0xFF00;
        CyDelay(1000);
    }
}

/* [] END OF FILE */

