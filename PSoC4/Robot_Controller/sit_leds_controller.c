/* ========================================
 *
 * Copyright Eladioy Andrea, 2019
 * All Rights Reserved
 * GPL SOFTWARE.
 *
 * PROPERTY OF UV - Eladio Barrio and Andrea Granell.
 *
 * ========================================
*/

/***************************************
*             Include
***************************************/

#include "sit_leds_controller.h"

/*******************************************************************************
* roboparty: Barrido RGB.
********************************************************************************/

void roboparty(){
    RGB_BlueLed_Write(RGB_ON);
    RGB_RedLed_Write(RGB_ON);
    RGB_GreenLed_Write(RGB_ON);
    CyDelay(200);
    RGB_BlueLed_Write(RGB_ON);
    RGB_RedLed_Write(RGB_ON);
    RGB_GreenLed_Write(RGB_OFF);
    CyDelay(200);
    RGB_BlueLed_Write(RGB_ON);
    RGB_RedLed_Write(RGB_OFF);
    RGB_GreenLed_Write(RGB_ON);
    CyDelay(200);
    RGB_BlueLed_Write(RGB_ON);
    RGB_RedLed_Write(RGB_OFF);
    RGB_GreenLed_Write(RGB_OFF);
    CyDelay(200);
    RGB_BlueLed_Write(RGB_OFF);
    RGB_RedLed_Write(RGB_ON);
    RGB_GreenLed_Write(RGB_ON);
    CyDelay(200);
    RGB_BlueLed_Write(RGB_OFF);
    RGB_RedLed_Write(RGB_ON);
    RGB_GreenLed_Write(RGB_OFF);
    CyDelay(200);
    RGB_BlueLed_Write(RGB_OFF);
    RGB_RedLed_Write(RGB_OFF);
    RGB_GreenLed_Write(RGB_ON);
    CyDelay(200);
    RGB_BlueLed_Write(RGB_OFF);
    RGB_RedLed_Write(RGB_OFF);
    RGB_GreenLed_Write(RGB_OFF);
}

/*******************************************************************************
* rgb_off: apaga RGB.
********************************************************************************/

void rgb_off(){
    RGB_RedLed_Write(RGB_OFF);
    RGB_GreenLed_Write(RGB_OFF);
    RGB_BlueLed_Write(RGB_OFF);
}

/*******************************************************************************
* rgb_color: enciende RGB del color correspondiente.
********************************************************************************/

void rgb_blanco(){
    RGB_RedLed_Write(RGB_ON);
    RGB_GreenLed_Write(RGB_ON);
    RGB_BlueLed_Write(RGB_ON);
}
void rgb_verde(){
    RGB_RedLed_Write(RGB_OFF);
    RGB_GreenLed_Write(RGB_ON);
    RGB_BlueLed_Write(RGB_OFF);
}
void rgb_rojo(){
    RGB_RedLed_Write(RGB_ON);
    RGB_GreenLed_Write(RGB_OFF);
    RGB_BlueLed_Write(RGB_OFF);
}
void rgb_azuloscuro(){
    RGB_RedLed_Write(RGB_OFF);
    RGB_GreenLed_Write(RGB_OFF);
    RGB_BlueLed_Write(RGB_ON); 
}
void rgb_azulclaro(){
    RGB_RedLed_Write(RGB_OFF);
    RGB_GreenLed_Write(RGB_ON);
    RGB_BlueLed_Write(RGB_ON);
}
void rgb_amarillo(){
    RGB_RedLed_Write(RGB_ON);
    RGB_GreenLed_Write(RGB_ON);
    RGB_BlueLed_Write(RGB_OFF);
}

/*******************************************************************************
* max_init: Configura registros MAX mediante SPI.
********************************************************************************/

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

/*******************************************************************************
* max_test: Utilizada para testear la matriz led.
********************************************************************************/

void max_test(void){
// test on
    SPIM_1_WriteTxData(0x0F01);
    CyDelay(1000);
    // testo off
    SPIM_1_WriteTxData(0x0F00);
    CyDelay(1);
}

/*******************************************************************************
* max_delete: Apaga LED matriz.
********************************************************************************/

void max_delete(void){
    unsigned char i;
    for ( i = 1; i < 9; i ++){
        SPIM_1_WriteTxData(0x0000 |((unsigned short)i<<8));// & 0xFF00;
        CyDelay(1);
    }
}

/****************************************************************************************
* max_delete: escribe vector con 8 posiciones de 1byte en los registros de representcion
****************************************************************************************/

void max_write_img(unsigned char img[]){
    unsigned char i;
    for ( i = 0; i < 8; i ++){
        SPIM_1_WriteTxData(0x0000 | ((((unsigned short)i+1)<<8)|img[i]));
        CyDelay(1);
    }
}

/****************************************************************************************
* max_write_x: Representa figura X en la matriz LED
****************************************************************************************/

void max_write_house(void){
    unsigned char img_1 [8] = {0x10,0x3f,0x40,0xb7,0xb7,0x40,0x3f,0x10};
    max_write_img(img_1);
    CyDelay(1);
}
void max_write_down(void){
    unsigned char img_2 [8] = {0x10,0x20,0x40,0xff,0xff,0x40,0x20,0x10};
    max_write_img(img_2);
    CyDelay(1);
}
void max_write_rigth(void){
    unsigned char img_4 [8] = {0x18,0x3c,0x5a,0x99,0x18,0x18,0x18,0x18};
    max_write_img(img_4);
    CyDelay(1);
}
void max_write_left(void){
    unsigned char img_3 [8] = {0x18,0x18,0x18,0x18,0x99,0x5a,0x3c,0x18};
    max_write_img(img_3);
    CyDelay(1);
}
void max_write_up(void){
    unsigned char img_5 [8] = {0x08,0x04,0x02,0xFF,0xFF,0x02,0x04,0x08};
    max_write_img(img_5);
    CyDelay(1);
}
void max_write_happy(void){
    unsigned char img_6 [8] = {0x20, 0x46, 0x46, 0x80, 0x80, 0x46, 0x46, 0x20};
    max_write_img(img_6);
    CyDelay(1);
}
void max_write_jedi_logo(){
    unsigned char img_6 [8] = {0x7e, 0xf1, 0xe4, 0xff, 0xff, 0xe4, 0xf1, 0x7e};
    max_write_img(img_6);
    CyDelay(1);
}