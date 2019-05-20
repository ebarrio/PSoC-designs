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

#include "sit_bluetooth_controller.h"

/***************************************
*            Global variables
***************************************/

uint8 robo_state_resolved = 1;
uint8 robot_state[STATES_NUM];
uint32 count_10us = 0;
uint8 i = 0;

/*******************************************************************************
* Rutina de interrupción
********************************************************************************/

CY_ISR(InterruptHandler)
{
	// Clear TC
   	Timer_1_STATUS;
    count_10us++;
    //Check BLE request
    CyBle_ProcessEvents();
}

/*******************************************************************************
* Programa principal
********************************************************************************/

int main(void)
{   
    /* Inicialización componentes*/
    CyGlobalIntEnable;
    CyBle_Start(CustomEventHandler); 
    TimerISR_StartEx(InterruptHandler);
    Timer_1_Start();
    PWM_1_Start();
    PWM_2_Start();
    max_init();
    max_delete();
    max_write_happy();

    for(;;){
        if(robo_state_resolved == 0){
            //Get state of BLE controller
            get_robot_state(robot_state);
            
            for(i = 0; i < STATES_NUM  ; i++){
                switch(robot_state[i]) {
                    case SLEEP_ROBOT:;
                        break;
                    case AVANZAR:
                        rgb_amarillo();
                        robot_avanzar();
                        break;
                    case RETROCEDER:
                        rgb_verde();
                        robot_retroceder();
                        break;
                    case GIRAR_IZQUIERDA:
                        rgb_azulclaro();
                        robot_girar_izquierda();
                        break;
                    case GIRAR_DERECHA:
                        rgb_azuloscuro();
                        robot_girar_derecha();
                        break;
                    case LDR_DRIVE:
                        robot_ldr_control();
                        break;
                    case BUZZER_IMPERIAL_MARCH:
                        max_write_jedi_logo();
                        buzzer_ImperialMarch();
                        max_write_happy();
                        break;
                    case SENSAR_DISTANCIA:
                        robot_avanza_sens_dist();
                        break;
                    case REPRESENTACION_DISTANCIA:
                        robot_rep_dist();
                        break;
                    case SEGUIDOR:
                        robot_seguidor();
                        break;
                    case DETECTOR_LINEA:
                        robot_detector_lineas();
                        break;
                    case RGB_TEST:
                        roboparty();
                        break;
                    case ACELERACION_PROGRESIVA:
                        robot_aceleracion_progresiva(3);
                    default:
                        rgb_azuloscuro();
                        break;
                }
            }
            robo_state_resolved = 1;
        }
        CySysPmSleep();
    }
}
/* [] END OF FILE */
