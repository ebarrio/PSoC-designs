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
*             Includes
***************************************/

#include "project.h"

/***************************************
*           Define (ROM)
***************************************/

#define COUNTS_DO 383
#define COUNTS_SOL 304
#define COUNTS_MI 255
#define COUNTS_SI 203
#define COUNTS_DOs 191
#define BEAT 50
#define BEAT_CORR_DO 1
#define BEAT_CORR_SOL 1.261
#define BEAT_CORR_MI 1.502
#define BEAT_CORR_SI 1.889
#define BEAT_CORR_DOs 2.004

/***************************************
*        Function Prototypes
***************************************/

void buzzer_MI();
void buzzer_SOL();
void buzzer_DO();
void buzzer_SI();
void buzzer_DOs();
void buzzer_stop();
void buzzer_play();
void buzzer_ImperialMarch();

/* [] END OF FILE */
