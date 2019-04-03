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
#include "project.h"
#include "sit_leds_controller.h"
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
void get_robot_state (uint8 * a);

/* [] END OF FILE */
