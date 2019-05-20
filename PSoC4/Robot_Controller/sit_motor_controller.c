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

#include "sit_motor_controller.h"

/****************************************************************************************
* cambio_directo_marcha_atras: Configura puente para marcha atras
****************************************************************************************/

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

/****************************************************************************************
* cambio_directo_marcha_adelante: Configura puente para marcha adelante
****************************************************************************************/

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

/****************************************************************************************
* frenar_direccion: Configura puente para frenar la direccion
****************************************************************************************/

void frenar_direccion(){
    S0A_Write(0u);
    S0B_Write(0u);
    S1A_Write(0u);
    S1B_Write(0u);
}

/****************************************************************************************
* giro_derecha: Configura puente para girar a la derecha
****************************************************************************************/

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

/****************************************************************************************
* giro_izquierda: Configura puente para girar a la izquierda
****************************************************************************************/

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
/* [] END OF FILE */
