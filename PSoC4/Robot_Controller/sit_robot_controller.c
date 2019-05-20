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

#include "sit_robot_controller.h"

/***************************************
*       Extern variable (sit_main)
***************************************/

extern uint32 count_10us;

/****************************************************************************************
* robot_avanzar: Controla el robot para avanzar 10cm
****************************************************************************************/

void robot_avanzar(){
    max_write_up();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    cambio_directo_marcha_adelante();
    CyDelay(500);
    frenar_direccion();
}
/****************************************************************************************
* robot_retroceder: Controla el robot para retroceder 10cm
****************************************************************************************/

void robot_retroceder(){
    max_write_down();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    cambio_directo_marcha_atras();
    CyDelay(500);
    frenar_direccion();
}

/****************************************************************************************
* robot_girar_izquierda: Controla el robot para girar 90º a la izquierda
****************************************************************************************/

void robot_girar_izquierda(){
    max_write_left();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    giro_izquierda();
    CyDelay(300);
    frenar_direccion();
}

/****************************************************************************************
* robot_girar_derecha: Controla el robot para girar 90º a la derecha
****************************************************************************************/

void robot_girar_derecha(){
    max_write_rigth();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    giro_derecha();
    CyDelay(300);
    frenar_direccion();
}

/************************************************************************************************
* robot_ldr_control: Avanza el robot dependiendo de la medida sensada por el LDR
*************************************************************************************************/

void robot_ldr_control(){
    if(LDR_trigger_Read() == 0){
        while(LDR_trigger_Read() == 0);
    }
    cambio_directo_marcha_adelante();
    while(LDR_trigger_Read() == 1);
    frenar_direccion();
}

/************************************************************************************************
* robot_sense_distance: Sensa y devuelve la distancia hasta el primer obstaculo frontal del robot
        return: Distancia sensada
*************************************************************************************************/

uint64 robot_sense_distance(){
    uint64 cmSense = 0;
    uint64 us = 0;
    uint64 ini_counter_value = 0;
    uint64 fin_counter_value = 0;
    uint64 cen_counter_value = 0;
    //Se asegura la señal de disparo
    Trigger_Pin_Write(LOW);
    CyDelayUs(4);
    //Se envia pulso al pin de trigger durante 10us
    Trigger_Pin_Write(HIGH);
    CyDelayUs(10);
    Trigger_Pin_Write(LOW);
    //Esperamos la señal de echo
    cen_counter_value = count_10us;
    while(Echo_Pin_Read() == LOW || ini_counter_value - cen_counter_value >= 1000000){
        ini_counter_value = count_10us;
    }
    cen_counter_value = count_10us;
    while(Echo_Pin_Read() == HIGH || fin_counter_value - cen_counter_value >= 1000000){
        fin_counter_value = count_10us;
    }
    us = (fin_counter_value - ini_counter_value)/10;
    cmSense = us * 10 / 292 / 2;
    return cmSense;
}

/************************************************************************************************
* robot_avanza_sens_dist: Avanza el robot dependiendo de la medida sensada por el sensor de distancia
*                    Calcula la media de 25 muestras del sensor para obtener un resultado fiable
*************************************************************************************************/

void robot_avanza_sens_dist(){
    uint64 cm_sense = 100;
    uint64 acum = 0;
    uint8 muestras_sensado = 25;
    uint8 i = 0;
    max_write_house();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    cambio_directo_marcha_adelante();
    while (cm_sense >= 5){
        acum = 0;
        for(i = 0; i < muestras_sensado;i++){
        acum = acum + robot_sense_distance();
        }
        cm_sense = acum / muestras_sensado;
    }
    frenar_direccion();
}

/*************************************************************************************************************
* robot_detector_lineas: Avanza el robot dependiendo de la medida sensada por el sensor de reflejo infrarrojo
*************************************************************************************************************/

void robot_detector_lineas(){
    uint8 sentido = 0;
    uint8 viajes = 0;
    while(viajes < 3){
        rgb_azuloscuro();
        if(sentido == 0){
            sentido = 1;
            cambio_directo_marcha_adelante();
        }
        else{
            sentido = 0;
            cambio_directo_marcha_atras();
        }
        while(Seguidor_Digital_Read() == 0);
        frenar_direccion();
        rgb_blanco();
        CyDelay(250);
        viajes++;
    }
}
/*************************************************************************************************************
* robot_seguidor: Ejecuta el firmware de un robot seguidor de lineas.
*************************************************************************************************************/

void robot_seguidor(){
    uint16 min_pwm = 2000;
    uint16 pwm1 = min_pwm;
    uint16 pwm2 = min_pwm;
    uint16 dif_marcha = 2000;
    uint16 max_pwm = min_pwm + dif_marcha;
    uint8 light = 0;
    PWM_1_WriteCompare(min_pwm);
    PWM_2_WriteCompare(min_pwm);
    cambio_directo_marcha_adelante();
    while(1){
        light = Seguidor_Digital_Read();
        switch(light){
            case(0u):
                rgb_verde();
                if(pwm1 + dif_marcha <= max_pwm){
                    pwm1 += dif_marcha;
                    PWM_1_WriteCompare(pwm1);

                }
                if(pwm2 - dif_marcha >= min_pwm){
                    pwm2 -= dif_marcha;
                    PWM_2_WriteCompare(pwm2);
                }
            break;
            default:
                rgb_rojo();
                if(pwm2 + dif_marcha <= max_pwm){
                    pwm2 += dif_marcha;
                    PWM_2_WriteCompare(pwm2);

                }
                if(pwm1 - dif_marcha >= min_pwm){
                    pwm1 -= dif_marcha;
                    PWM_1_WriteCompare(pwm1);
                }
            break;
        }
    }
}

/*************************************************************************************************************
* robot_aceleracion_progresiva: Aclera el robot hasta la velocidad máxima.
    input segundos_aceleracion: Tiempo en segundos para realizar el barrido de velocidad.
*************************************************************************************************************/

void robot_aceleracion_progresiva(uint8 segundos_aceleracion){
    uint16 ini_value = 3000;
    uint16 comp_max_value = 8000;
    uint16 sec;
    if(segundos_aceleracion < 10 && segundos_aceleracion > 0)
        sec = segundos_aceleracion;
    else
        sec = 3;
    // us_delay = 10^6 * segundos / (max - ini)
    uint32 us_delay = 200 * (uint32) sec;
    cambio_directo_marcha_adelante();
    while(ini_value <= comp_max_value){
        PWM_1_WriteCompare(ini_value);
        PWM_2_WriteCompare(ini_value);
        ini_value++;
        CyDelayUs(us_delay);
    }
    //frenar_direccion();
}

/*************************************************************************************************************
* robot_rep_dist: Enciende un el RGB verde si la distancia es menor que 5cm y rojo de lo contrario.
*************************************************************************************************************/

void robot_rep_dist(){
    uint64 cm = 0;
    cm = robot_sense_distance();
    rgb_off();
    CyDelay(500);
    if(cm > 10)
        rgb_verde();
    else
        rgb_rojo();
    CyDelay(500);
    rgb_off();
}

/* [] END OF FILE */