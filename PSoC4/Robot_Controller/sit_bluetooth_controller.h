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


/***************************************
*        API Constants
***************************************/
#define NO_ALERT           (0u)
#define MILD_ALERT         (1u)
#define HIGH_ALERT         (2u)

#define NO_ALERT_COMPARE   (0u)
#define MILD_ALERT_COMPARE (250u)
#define HIGH_ALERT_COMPARE (500u)

/***************************************
*        Function Prototypes
***************************************/
uint8 read_ble_state();
void StackEventHandler(uint32 event, void* eventParam);
void IasEventHandler(uint32 event, void* eventParam);
void RequestResolver(uint8 status);
void get_robot_state (uint8 a []);

void CustomEventHandler(uint32 event, void * eventParam);
void state_BLE_test (unsigned short);
/* [] END OF FILE */

#define TRUE							(1)
#define FALSE							(0)
#define ZERO	                        (0)
#define MAX_INSTR 4