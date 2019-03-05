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
void max_write_down(void){
    unsigned char img_2 [8] = {0x08,0x04,0x02,0xFF,0xFF,0x02,0x04,0x08};
    max_write_img(img_2);
    CyDelay(1);
}
void max_write_rigth(void){
    unsigned char img_3 [8] = {0x18,0x3c,0x5a,0x99,0x18,0x18,0x18,0x18};
    max_write_img(img_3);
    CyDelay(1);
}
void max_write_left(void){
    unsigned char img_4 [8] = {0x18,0x18,0x18,0x18,0x99,0x5a,0x3c,0x18};
    max_write_img(img_4);
    CyDelay(1);
}
void max_write_up(void){
    unsigned char img_5 [8] = {0x10,0x20,0x40,0xff,0xff,0x40,0x20,0x10};
    max_write_img(img_5);
    CyDelay(1);
}
/* [] END OF FILE */
