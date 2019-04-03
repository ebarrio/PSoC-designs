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

uint8 r_state = 0;
/*******************************************************************************
* Function Name: StackEventHandler
********************************************************************************
*
* Summary:
*  This is an event callback function to receive events from the BLE Component.
*
* Parameters:  
*  uint8 event:       Event from the CYBLE component
*  void* eventParams: A structure instance for corresponding event type. The 
*                     list of event structure is described in the component 
*                     datasheet.
*
* Return: 
*  None
*
*******************************************************************************/
void StackEventHandler(uint32 event, void *eventParam)
{
    uint8 alertLevel;
    
    switch(event)
    {
        /* Mandatory events to be handled by Find Me Target design */
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
        case CYBLE_EVT_TIMEOUT:
            /* Start the BLE fast advertisement. */
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            /* Reset the alert level to NOALERT */
            alertLevel = NO_ALERT;
            RequestResolver(alertLevel);
            break;
        default:
    	    break;
    }
}

/*******************************************************************************
* Function Name: IasEventHandler
********************************************************************************
*
* Summary:
*  This is an event callback function to receive events from the BLE Component,
*  which are specific to Immediate Alert Service.
*
* Parameters:  
*  uint8 event:       Write Command event from the CYBLE component.
*  void* eventParams: A structure instance of CYBLE_GATT_HANDLE_VALUE_PAIR_T
*                     type.
*
* Return: 
*  None
*
*******************************************************************************/
void IasEventHandler(uint32 event, void *eventParam)
{
    uint8 alertLevel;
    
    /* Alert Level Characteristic write event */
    if(event == CYBLE_EVT_IASS_WRITE_CHAR_CMD)
    {
        /* Extract Alert Level value from the GATT DB using the 
		 * CYBLE_IAS_ALERT_LEVEL as a parameter to CyBle_IassGetCharacteristicValue
		 * routine. Store the Alert Level Characteristic value in "alertLevel"
		 * variable */
        CyBle_IassGetCharacteristicValue(CYBLE_IAS_ALERT_LEVEL, sizeof(alertLevel), &alertLevel);
        /*Based on alert Level level recieved, Drive LED*/
        RequestResolver(alertLevel);
    }
}

/*******************************************************************************
* Function Name: HandleAlertLEDs
********************************************************************************
*
* Summary:
*  This function drives the LED based on the alert level
*
* Parameters:  
*  uint8 status:      Alert level 
*
* Return: 
*  None
*
*******************************************************************************/
void RequestResolver(uint8 status)
{
    /* Update Alert LED status based on IAS Alert level characteristic. */
        /* Place your application code here. */
        switch(status) {
            case 0:
            r_state = 0;
            break;
            case 1:
            r_state = 1;
            break;
            case 2:
            r_state = 2;
            break;
            default:
            break;
        }
    //Enter in sleep mode (CPU sleep, hardware (timmer interrupt) active)
}
void get_robot_state(uint8 * a){
    *a = r_state;
}
