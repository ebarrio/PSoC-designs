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

#define RGB_OFF 1u
#define RGB_ON 0u

/***************************************
*       RGB Function Prototypes
***************************************/
void rgb_off();
void rgb_blanco();
void rgb_verde();
void rgb_rojo();
void rgb_azuloscuro();
void rgb_azulclaro();
void rgb_amarillo();
void roboparty();

/***************************************
*     LED matrix Function Prototypes
***************************************/

void max_init();
void max_test();
void max_delete(void);
void max_write_img(unsigned char img[]);
void max_write_house(void);
void max_write_down(void);
void max_write_rigth(void);
void max_write_left(void);
void max_write_up(void);
void max_write_happy(void);
void max_write_jedi_logo();

/* [] END OF FILE */
