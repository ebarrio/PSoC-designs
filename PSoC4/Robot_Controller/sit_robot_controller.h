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
#define STATES_NUM 8

#include "sit_leds_controller.h"
#include "sit_motor_controller.h"
#include "sit_buzzer_controller.h"

struct Robot{
    uint32 * counts;
    uint8 states[STATES_NUM];
    uint8 state_resolved;
    uint8 pwm_duty_porc;
};

#define WIDTH_FOR_1CM 2

#define SLEEP_ROBOT 0x00
#define AVANZAR 0x01
#define RETROCEDER 0x02
#define GIRAR_IZQUIERDA 0x03
#define GIRAR_DERECHA 0x04
#define LDR_DRIVE 0x05
#define BUZZER_IMPERIAL_MARCH 0x06
#define SENSAR_DISTANCIA 0x07
#define CUENTA_ATRAS 0x08
#define SEGUIDOR 0x09
#define DETECTOR_LINEA 0x0A
#define HARDWARE_DELAY 0x0B
#define ACELERACION_PROGRESIVA 0x0C

void robot_us_hardware_delay(uint32);
void robot_test_hardware_delay();
void robot_avanzar();
void robot_retroceder();
void robot_girar_izquierda();
void robot_girar_derecha();
void robot_ldr_control();
void robot_sense_distance();
void robot_avanza_sens_dist();
void robot_cuenta_atras();
void robot_detector_lineas();
void robot_seguidor();
void robot_aceleracion_progresiva(uint8 sec);
/* [] END OF FILE */
