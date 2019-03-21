/********************************************************************************
* File Name: main.c
*
* Version : 1.10
*
* Description: 
*  This is a source code for example project of 16 bit Timer UDB Block.
*
* Test Result:
*  Watch capture output on P0_0, tc output on P0_1, and Period, Compare and 
*  Count value on LCD.
*
********************************************************************************
* Copyright 2012-2017, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>
#define HIGH 1u
#define LOW 0u
#define Timer_1_Counts_to_10us 240
uint8 InterruptCnt;
unsigned short senseDistanceCm();
unsigned short senseDistanceCm2();
/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
********************************************************************************/
CY_ISR(InterruptHandler)
{
	/* Read Status register in order to clear the sticky Terminal Count (TC) bit 
	 * in the status register. Note that the function is not called, but rather 
	 * the status is read directly.
	 */
   	Timer_1_STATUS;
    
	/* Increment the Counter to indicate the keep track of the number of 
     * interrupts received */
    InterruptCnt++;    
}
/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
* Main function performs following functions:
* 1: Enables the clock
* 2: Start the Timer
* 3: Initializes the LCD
* 4: Print Period, capture, counter value on LCD
* 
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()

{   
    unsigned short cmSense = 0;
    /* Enable the global interrupt */
    CyGlobalIntEnable;
    Timer_1_Start();
    CyDelay(20);
    Timer_1_Stop();
    CyDelay(20);
    /* Enable the Interrupt component connected to Timer interrupt */
    TimerISR_StartEx(InterruptHandler);

	/* Start the components */
    Trigger_Write(HIGH);
    CyDelay(20);
    Trigger_Write(LOW);
    CyDelay(20);
    
    /* Display TMR-16 on LCD */
    LCD_Start();
    LCD_Position(0u, 0u);
    LCD_PrintString("Sensor distancia"); 
    LCD_Position(1u, 0u);
    LCD_PrintString("Dist(mm)="); 
    for(;;)
    {   
        if(SW0_Read() == LOW){
                //Envio pulso trigger  durante 10us.
            //Timer_1_RestoreConfig();
            cmSense = senseDistanceCm();
            LCD_Position(1u, 8u);
            LCD_PrintDecUint16(cmSense);

        }
    }
}
unsigned short senseDistanceCm(){
    unsigned short cmSense;
    unsigned short startReadCounter;
    Trigger_Write(HIGH);
    CyDelayUs(10);
    Trigger_Write(LOW);
    //Esperamos el echo y medimos las cuentas del timmer en las que esta en estado alto.
    Timer_1_Start();
    startReadCounter = Timer_1_ReadCapture();
    while(Echo_Read() == LOW);
    while(Echo_Read() == HIGH);
    Timer_1_Stop();
    startReadCounter = Timer_1_ReadCapture() - startReadCounter;
    cmSense = (startReadCounter*1715)/(100*24);
    if(cmSense == 0){
        LED0_Write(HIGH);
    }
    else{
        LED0_Write(LOW);
    }
    return cmSense;

}
unsigned short senseDistanceCm2(){
    unsigned short cmSense = 0;
    double operationVariable = 0;
    unsigned short startReadCounter;
    //Envio pulso trigger  durante 10us.
    //Timer_1_RestoreConfig();
    startReadCounter = Timer_1_ReadCounter();
    Trigger_Write(HIGH);
    while((Timer_1_ReadCounter() -  startReadCounter) < Timer_1_Counts_to_10us);
    Trigger_Write(LOW);
    //Esperamos el echo y medimos las cuentas del timmer en las que esta en estado alto.
    while(Echo_Read() == LOW);
    startReadCounter = Timer_1_ReadCounter();
    while(Echo_Read() == HIGH);
    operationVariable = Timer_1_ReadCounter() - startReadCounter;
    operationVariable = (operationVariable * 1715)/(10000*24);
    return cmSense;
}

/* [] END OF FILE */