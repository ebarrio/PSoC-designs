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
#include "sit_motor_controller.h"
void motor_request(uint8 robot_state){
    switch(robot_state){
        default:
        break;
    }
}
void motor_inicializar(void){
    // Activa puertos driver marcha adelante
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u); 
}
void cambio_directo_marcha_atras(){
     // Frena el motor y espera para bajar revoluciones
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u);
    CyDelay(100);
    // Activa puertos driver marcha atras
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(1u);
    S1B_Write(1u); 

}
void cambio_directo_marcha_adelante(){
     // Frena el motor y espera para bajar revoluciones
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u);
    CyDelay(100);
    // Activa puertos driver marcha adelanye
    S0A_Write(1u);
    S0B_Write(1u);
    S1A_Write(0u);
    S1B_Write(0u);
  
}
void frenar_direccion(){
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u);
}
void giro_derecha(){
    // Frena el motor y espera para bajar revoluciones
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u); 
    CyDelay(100);
    // Activa puertos driver marcha adelante
    S0A_Write(0u);
    S0B_Write(1u);
    S1A_Write(1u);
    S1B_Write(0u); 
}
void giro_izquierda(){
    // Frena el motor y espera para bajar revoluciones
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u); 
    CyDelay(100);
    // Activa puertos driver izquierda
    S0A_Write(1u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(1u); 
}
void robot_seguidor_derecha(){
    // Activa puertos driver izquierda
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u);
    S0A_Write(1u);
}
void robot_seguidor_izquierda(){
    S1A_Write(0u);
    S1B_Write(0u);
    S0A_Write(0u);
    S0B_Write(1u);
}
/* [] END OF FILE */
