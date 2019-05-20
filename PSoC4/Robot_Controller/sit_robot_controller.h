/* ========================================
 *
 * Copyright Eladioy Andrea, 2019
 * All Rights Reserved
 * GPL SOFTWARE.
 *
 * PROPERTY OF y UV - Eladio Barrio and Andrea Granell.
 *
 * ========================================
*/

/***************************************
*             Includes
***************************************/

#include "sit_leds_controller.h"
#include "sit_motor_controller.h"
#include "sit_buzzer_controller.h"

/***************************************
*           Define (ROM)
***************************************/

#define STATES_NUM 8
#define HIGH 0u
#define LOW 1u
#define WIDTH_FOR_1CM 2
#define SLEEP_ROBOT 0x00
#define AVANZAR 0x01
#define RETROCEDER 0x02
#define GIRAR_IZQUIERDA 0x03
#define GIRAR_DERECHA 0x04
#define LDR_DRIVE 0x05
#define BUZZER_IMPERIAL_MARCH 0x06
#define SENSAR_DISTANCIA 0x07
#define REPRESENTACION_DISTANCIA 0x08
#define SEGUIDOR 0x09
#define DETECTOR_LINEA 0x0A
#define RGB_TEST 0x0B
#define ACELERACION_PROGRESIVA 0x0C

/***************************************
*        Function Prototypes
***************************************/

void robot_avanzar();
void robot_retroceder();
void robot_girar_izquierda();
void robot_girar_derecha();
void robot_ldr_control();
uint64 robot_sense_distance();
void robot_avanza_sens_dist();
void robot_detector_lineas();
void robot_seguidor();
void robot_aceleracion_progresiva(uint8 sec);
void robot_rep_dist();

/* [] END OF FILE */
