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

uint8 robot_state = MOTOR_CONTROL;
u8 * p_robot_state = NULL;
uint8 InterruptCnt = 0;
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
    //Check BLE request
    CyBle_ProcessEvents();
    //Get state of BLE controller
    p_robot_state = &robot_state;
    get_robot_state(p_robot_state);
}

int main(void)
{   
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    /* Start the BLE component and register StackEventHandler function */
    CyBle_Start(StackEventHandler);
    
    /* Register IAS event handler function */
    CyBle_IasRegisterAttrCallback(IasEventHandler);
    
    /* Enable the Interrupt component connected to Timer interrupt */
    TimerISR_StartEx(InterruptHandler);

	/* Start the components */
    Timer_1_Start();
    
    for(;;)
    {
        switch(robot_state) {
            case MOTOR_CONTROL:
            
            break;
            case LINE_FOLLOW:
            roboparty();
            break;
            case LED_DISPLAY:
            roboparty();
            break;
            case 4:
            roboparty();
            break;
            default:
            CyDelay(10);
            break;
        }
    CySysPmSleep();
    }
}

/* [] END OF FILE */
