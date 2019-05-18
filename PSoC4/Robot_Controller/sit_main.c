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
#include "sit_bluetooth_controller.h"

uint8 robo_state_resolved = 1;
uint8 robot_state[STATES_NUM];
//u8 * p_robot_state = NULL;
uint32 count_10us = 0;
uint8 i = 0;
/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
* Launched 
********************************************************************************/
CY_ISR(InterruptHandler)
{
	/* Read Status register in order to clear the sticky Terminal Count (TC) bit 
	 * in the status register. Note that the function is not called, but rather 
	 * the status is read directly.
	 */
   	Timer_1_STATUS;
    count_10us++;
    //Check BLE request
    CyBle_ProcessEvents();
}

int main(void)
{       
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Start the BLE component and register StackEventHandler function */
    CyBle_Start(CustomEventHandler); 
    /* Enable the Interrupt component connected to Timer interrupt */
    TimerISR_StartEx(InterruptHandler);
	/* Start the components */
    Timer_1_Start();
    PWM_1_Start();
    PWM_2_Start();
    motor_inicializar();
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
                    case CUENTA_ATRAS:
                        robot_cuenta_atras();
                        break;
                    case SEGUIDOR:
                        robot_seguidor();
                        break;
                    case DETECTOR_LINEA:
                        robot_detector_lineas();
                        break;
                    case HARDWARE_DELAY:
                        rgb_blanco();
                        CyDelay(1000);
                        robot_test_hardware_delay();
                        break;
                    case ACELERACION_PROGRESIVA:
                        robot_aceleracion_progresiva(3);
                    default:
                        rgb_azuloscuro();
                        break;
                }
            }
            //max_write_house();
            robo_state_resolved = 1;
        }
        CySysPmSleep();
    }
}

/* [] END OF FILE */
