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

#include "sit_buzzer_controller.h"

/***************************************
*            Global variables
***************************************/

extern uint32 count_10us;
uint32 counts_init = 0;

/*******************************************************************************
* buzzer_MI: Reproduce tono de unico pulso con la frecuencia MI.
********************************************************************************/

void buzzer_MI(){
    counts_init = count_10us;
    //CHECK COUNTS BEFORE
    //Pulse high
    BUZZER_Write(1u);
    while((count_10us - counts_init) < (COUNTS_MI/2));
    //Pulse low
    counts_init = count_10us;
    BUZZER_Write(0u);
    while((count_10us - counts_init) < (COUNTS_MI/2));
}

/*******************************************************************************
* buzzer_SOL: Reproduce tono de unico pulso con la frecuencia SOL.
********************************************************************************/

void buzzer_SOL(){
    counts_init = count_10us;
    //CHECK COUNTS BEFORE
    //Pulse high
    BUZZER_Write(1u);
    while((count_10us - counts_init) < (COUNTS_SOL/2));
    //Pulse low
    counts_init = count_10us;
    BUZZER_Write(0u);
    while((count_10us - counts_init) < (COUNTS_SOL/2));
}

/*******************************************************************************
* buzzer_DO: Reproduce tono de unico pulso con la frecuencia DO.
********************************************************************************/

void buzzer_DO(){
    counts_init = count_10us;
    //CHECK COUNTS BEFORE
    //Pulse high
    BUZZER_Write(1u);
    while((count_10us - counts_init) < (COUNTS_DO/2));
    //Pulse low
    counts_init = count_10us;
    BUZZER_Write(0u);
    while((count_10us - counts_init) < (COUNTS_DO/2));
}

/*******************************************************************************
* buzzer_DOs: Reproduce tono de unico pulso con la frecuencia DO sostenido.
********************************************************************************/

void buzzer_DOs(){
    counts_init = count_10us;
    //CHECK COUNTS BEFORE
    //Pulse high
    BUZZER_Write(1u);
    while((count_10us - counts_init) < (COUNTS_DOs/2));
    //Pulse low
    counts_init = count_10us;
    BUZZER_Write(0u);
    while((count_10us - counts_init) < (COUNTS_DOs/2));
}

/*******************************************************************************
* buzzer_SI: Reproduce tono de unico pulso con la frecuencia SI.
********************************************************************************/

void buzzer_SI(){
    counts_init = count_10us;
    //CHECK COUNTS BEFORE
    //Pulse high
    BUZZER_Write(1u);
    while((count_10us - counts_init) < (COUNTS_SI/2));
    //Pulse low
    counts_init = count_10us;
    BUZZER_Write(0u);
    while((count_10us - counts_init) < (COUNTS_SI/2));
}

/*******************************************************************************
* buzzer_ImperialMarch: Reproduce melodia de la marcha imperial.
********************************************************************************/

void buzzer_ImperialMarch(){
    uint32 k = 0;
    uint32 j = 0;
    //AÑADIR FACTOR CORRECION AL BEAT
    for(k = 0 ; k < 2 ; k++){
        for(j = 0; j < 3*BEAT*BEAT_CORR_MI ; j++){
            buzzer_MI();
        }
        CyDelay(50);
    }
    for(k = 0; k < 2 ; k++){
        for(j = 0; j < 3*BEAT*BEAT_CORR_MI ; j++){    
            buzzer_MI();
        }
        CyDelay(50);
        for(j = 0; j < 2*BEAT*BEAT_CORR_DO ; j++){
            buzzer_DO();
        }
        CyDelay(50);
        for(j = 0; j < BEAT*BEAT_CORR_SOL; j++){
            buzzer_SOL();
        }
        CyDelay(50);
    }    
    for(j = 0; j < 6*BEAT*BEAT_CORR_MI;j++){
        buzzer_MI();
    }
    CyDelay(50);
     
    for(k = 0 ; k < 3 ; k++){
        for(j = 0; j < 3*BEAT*BEAT_CORR_SI ; j++){
            buzzer_SI();
        }
            CyDelay(50);
    }
    for(k = 0; k < 2; k++){
        if(k == 0){
            for(j = 0; j < 2*BEAT*BEAT_CORR_DOs; j++){
                buzzer_DOs();
            }
        }
        else{
            for(j = 0; j < 2*BEAT*BEAT_CORR_DO; j++){
                buzzer_DO();
            }
        }
        CyDelay(50);
        for(j = 0; j < BEAT*BEAT_CORR_SOL; j++){
            buzzer_SOL();
        }
        CyDelay(50);
        for(j = 0; j < BEAT*3*BEAT_CORR_MI; j++){
            buzzer_MI();
        }
        CyDelay(50);
    }    
}
/* [] END OF FILE */