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

extern uint8 robo_state_resolved;
//static CYBLE_API_RESULT_T apiResult;
//static uint8 securityKey[16] = {0};
uint8 deviceConnected = 0;
uint32 j = 0;
unsigned short state [STATES_NUM];
/* All zeros passed as  argument passed to CyBle_GapRemoveDeviceFromWhiteList for 
removing all the bonding data stored */
CYBLE_GAP_BD_ADDR_T clearAllDevices = {{0,0,0,0,0,0},0};

void CustomEventHandler(uint32 event, void * eventParam)
{
    /* Local variable to strore the write request parameters */
	CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    //CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
    switch(event)
    {   

        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            rgb_amarillo();
            //CyBle_GapAuthReq(cyBle_connHandle.bdHandle, &cyBle_authInfo); //PAIRING REQUEST
            //CyBle_GapSetOobData(cyBle_connHandle.bdHandle, CYBLE_GAP_OOB_ENABLE, securityKey, NULL, NULL);
        break;
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
        //case CYBLE_EVT_GAP_AUTH_REQ:
            
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if(CYBLE_STATE_DISCONNECTED == CyBle_GetState()){
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            }
            //ROJO
            /*RGB_RedLed_Write(RGB_ON);
            RGB_G_Write(RGB_OFF);
            RGB_B_Write(RGB_OFF);  */          
            break;
        case CYBLE_EVT_GATT_CONNECT_IND:
            rgb_blanco();
            deviceConnected = TRUE;
            
            break;
        case CYBLE_EVT_GATT_DISCONNECT_IND:
            rgb_rojo();
            deviceConnected = FALSE;       
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
            rgb_azulclaro();
             /* This event is received when Central device sends a Write command 
             * on an Attribute. 
             * We first get the attribute handle from the event parameter and 
             * then try to match that handle with an attribute in the database.
             */
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            /* This condition checks whether the RGB LED characteristic was
             * written to by matching the attribute handle.
             * If the attribute handle matches, then the value written to the 
             * attribute is extracted and used to drive RGB LED.
             */
             /* Extract the attribute handle for the RGB LED characteristic 
             * from the custom service data structure.
             */
            //Morado
            /*
            RGB_R_Write(RGB_ON);
            RGB_G_Write(RGB_OFF);
            RGB_B_Write(RGB_ON); 
            */
            /* if (attributeHandle == RGB LED Characteristic Handle) */
            if(wrReqParam->handleValPair.attrHandle == cyBle_customs[CYBLE_ROBOT_SERVICE_SERVICE_INDEX].\
								                        customServiceInfo[CYBLE_ROBOT_SERVICE_SERVICE_INDEX].\
                                                        customServiceCharHandle)
            {
                
                /* Extract the value of the attribute from the handle-value 
                 * pair database. */
                for (j = 0 ; j < STATES_NUM ; j++){
                    state [j] = wrReqParam->handleValPair.value.val[j];
                }
                // AVISAMOS QUE HEMOS CAMBIADO EL STATE Y ESTA POR RESOLVER
                robo_state_resolved = 0;
                //CyBle_GattsWriteAttributeValue(
                /* Update the PrISM components and the attribute for RGB LED read 
                 * characteristics */
                //state_BLE_test(state[0]);  
            }
			/* Send the response to the write request received. */
			CyBle_GattsWriteRsp(cyBle_connHandle);
			break;
        default:

       	 	break;            
    }    
}
void get_robot_state(uint8 a []){
    for (j = 0 ; j < STATES_NUM ; j++){
        a[j] = state [j];
    }
}
void state_BLE_test(unsigned short state){
    switch(state){
        case 0:
            rgb_blanco();
            CyDelay(200);
            rgb_off();
            break;
        case 1:
            rgb_azulclaro();
            break;
        default:
            rgb_amarillo();
            break;           
    }
}