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
#include "sit_leds_controller.h"
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
/* [] END OF FILE */
