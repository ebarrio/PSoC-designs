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
#include "MAX7219.h"

void max_init(){
    SPIM_1_Start();
    CyDelay(1);
    // Operation: Normal
    SPIM_1_WriteTxData(0x0C01);
    CyDelay(1);
    //Decode: Off
    SPIM_1_WriteTxData(0x0900);
    CyDelay(1);
    // Enable all digits 
    SPIM_1_WriteTxData(0x0B07);
    CyDelay(1);
    // minima intesnidad
    SPIM_1_WriteTxData(0x0A02);
    CyDelay(1);
}
void max_test(void){
// test on
    SPIM_1_WriteTxData(0x0F01);
    CyDelay(1000);
    // testo off
    SPIM_1_WriteTxData(0x0F00);
    CyDelay(1);
}
void max_delete(void){
    unsigned char i;
    for ( i = 1; i < 9; i ++){
        SPIM_1_WriteTxData(0x0000 |((unsigned short)i<<8));// & 0xFF00;
        CyDelay(1);
    }
}
void max_write_img(unsigned char img[]){
    unsigned char i;
    for ( i = 0; i < 8; i ++){
        SPIM_1_WriteTxData(0x0000 | ((((unsigned short)i+1)<<8)|img[i]));
        CyDelay(1);
    }
}
void max_write_house(void){
    unsigned char img_1 [8] = {0x10,0x3f,0x40,0xb7,0xb7,0x40,0x3f,0x10};
    max_write_img(img_1);
    CyDelay(1);
}
/* [] END OF FILE */
