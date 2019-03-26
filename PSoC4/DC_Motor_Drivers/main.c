/* ==============================================
 *
 * Copyright Eladio Barrio Querol IFIC - UV 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Eladio Barrio Querol.
 *
 * ==============================================
*/
#include "project.h"

void inicializar_motor(void);
void cambio_directo_marcha_atras();
void cambio_directo_marcha_adelante();
void frenar_direccion();
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Clock_1_Start();
    PWM_1_Start();
    inicializar_motor();
    CyDelay(2000);
    cambio_directo_marcha_atras();
    CyDelay(2000);
    cambio_directo_marcha_adelante();
    CyDelay(2000);
    frenar_direccion();
    for(;;)
    {
        /* Place your application code here. */
    }
}
void inicializar_motor(void){
    // Activa puertos de habilitamiento
    ENA_Write(1u);
    ENB_Write(1u);
    // Activa puertos driver marcha adelante
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(1u);
    S1B_Write(1u);  
}
void cambio_directo_marcha_atras(){
    // Frena el motor y espera para bajar revoluciones
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u);
    CyDelay(100);
    // Activa puertos driver marcha atras
    S0A_Write(1u);
    S0B_Write(1u);
    S1A_Write(0u);
    S1B_Write(0u); 
}
void cambio_directo_marcha_adelante(){
    // Frena el motor y espera para bajar revoluciones
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(1u);
    S1B_Write(1u); 
    CyDelay(100);
    // Activa puertos driver marcha adelante
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(1u);
    S1B_Write(1u);   
}
void frenar_direccion(){
    ENA_Write(0u);
    ENB_Write(0u);
}
/* [] END OF FILE */
