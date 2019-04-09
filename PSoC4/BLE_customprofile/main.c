#include "project.h"
#define TRUE							(1)
#define FALSE							(0)
#define ZERO	                        (0)
#define RGB_ON 0
#define RGB_OFF 1
#define MAX_INSTR 4
void CustomEventHandler(uint32 event, void * eventParam);
void state_BLE_controller (unsigned short);
uint8 deviceConnected = 0;
uint32 i = 0;
unsigned short state [4];
int main(void)
{   
    for(i = 0; i < MAX_INSTR; i++){
        state[0] = 0;
    }
    RGB_R_Write(RGB_OFF);
    RGB_G_Write(RGB_ON);
    RGB_B_Write(RGB_ON);
    CyDelay(300);
    RGB_R_Write(RGB_ON);
    RGB_G_Write(RGB_ON);
    RGB_B_Write(RGB_OFF); 
    CyDelay(300);
    CyGlobalIntEnable; /* Enable global interrupts. */
    CyBle_Start(CustomEventHandler);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {   
        /* Place your application code here. */
         CyBle_ProcessEvents();
    }
}
void CustomEventHandler(uint32 event, void * eventParam)
{
    /* Local variable to strore the write request parameters */
	CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if(CYBLE_STATE_DISCONNECTED == CyBle_GetState()){
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            }
            //ROJO
            RGB_R_Write(RGB_ON);
            RGB_G_Write(RGB_OFF);
            RGB_B_Write(RGB_OFF);            
            break;
        case CYBLE_EVT_GATT_CONNECT_IND:
            deviceConnected = TRUE;
            //Verde
            RGB_R_Write(RGB_OFF);
            RGB_G_Write(RGB_ON);
            RGB_B_Write(RGB_OFF);             
            break;
        case CYBLE_EVT_GATT_DISCONNECT_IND:
            deviceConnected = FALSE;
            //Azul
            RGB_R_Write(RGB_OFF);
            RGB_G_Write(RGB_OFF);
            RGB_B_Write(RGB_ON);             
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
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
           
            
            RGB_R_Write(RGB_ON);
            RGB_G_Write(RGB_OFF);
            RGB_B_Write(RGB_ON);             
            /* if (attributeHandle == RGB LED Characteristic Handle) */
            if(wrReqParam->handleValPair.attrHandle == cyBle_customs[CYBLE_ROBOT_SERVICE_SERVICE_INDEX].\
								                        customServiceInfo[CYBLE_ROBOT_SERVICE_SERVICE_INDEX].\
                                                        customServiceCharHandle)
            {
                /* Extract the value of the attribute from the handle-value 
                 * pair database. */
                state [0] = wrReqParam->handleValPair.value.val[0];
                //CyBle_GattsWriteAttributeValue(
                /* Update the PrISM components and the attribute for RGB LED read 
                 * characteristics */
                state_BLE_controller(state[0]);
            }
			/* Send the response to the write request received. */
			CyBle_GattsWriteRsp(cyBle_connHandle);
			break;

        default:

       	 	break;            
    }    
}
void state_BLE_controller(unsigned short state){
    switch(state){
        case 0:
            //BLANCO
            RGB_R_Write(RGB_ON);
            RGB_G_Write(RGB_ON);
            RGB_B_Write(RGB_ON);
            CyDelay(100);
            RGB_R_Write(RGB_ON);
            RGB_G_Write(RGB_ON);
            RGB_B_Write(RGB_ON);
            break;
        case 1:
	    //AZUL CLARO
            RGB_R_Write(RGB_OFF);
            RGB_G_Write(RGB_ON);
            RGB_B_Write(RGB_ON);
            break;
        default:
            //AMARILLO
            RGB_R_Write(RGB_ON);
            RGB_G_Write(RGB_ON);
            RGB_B_Write(RGB_OFF); 
            break;
            
    }
}
