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
#include "sit_robot_controller.h"

extern uint32 count_10us;

void robot_avanzar(){
    max_write_up();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    cambio_directo_marcha_adelante();
    CyDelay(500);
    frenar_direccion();
}
void robot_retroceder(){
    max_write_down();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    cambio_directo_marcha_atras();
    CyDelay(500);
    frenar_direccion();
}
void robot_girar_izquierda(){
    max_write_left();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    giro_izquierda();
    CyDelay(300);
    frenar_direccion();
}
void robot_girar_derecha(){
    max_write_rigth();
    PWM_1_WriteCompare(4000);
    PWM_2_WriteCompare(4000);
    giro_derecha();
    CyDelay(300);
    frenar_direccion();
}
void robot_ldr_control(){
    if(LDR_trigger_Read() == 0){
        while(LDR_trigger_Read() == 0);
    }
    cambio_directo_marcha_adelante();
    while(LDR_trigger_Read() == 1);
    frenar_direccion();
}
void robot_us_hardware_delay(uint32 us){
    uint32 counts = us;
    count_10us = 0;
    while (counts < (us/10)){
        counts = count_10us;
    }
}
void robot_sense_distance(){

}
void robot_avanza_sens_dist(){

}
void robot_cuenta_atras(){

}
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

void robot_seguidor(){
    uint16 min_pwm = 2200;
    uint16 pwm1 = min_pwm;
    uint16 pwm2 = min_pwm;
    uint16 dif_marcha = 2500;
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
void robot_test_hardware_delay(){
    rgb_rojo();
    CyDelay(1000);
}
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
/* [] END OF FILE */