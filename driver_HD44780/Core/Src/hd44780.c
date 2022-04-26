/*
 * hd44780.c
 *
 *  Created on: 14 abr. 2022
 *      Author: Ricardo
 */

#include "hd44780.h"

/*************************** Máscara de pines ********************************/
/* Los pines RS, RW, EN y BL están ubicados en el Low Nibble del Byte de data 
 * El High Nibble está compuesto por los pines D7-D4 respectivamente
 ******************************************************************************/
#define RS              0x01    /* 0000 0001 . 0 = Commands. 1 = Characters.*/
#define RW              0x02    /* 0000 0010 . 0 = Write. 1 = Read. ESTE PIN SIEMPRE SE DEJA EN 0 PORQUE NO SE LEE DESDE EL DISPLAY. */
#define ENABLE          0x04    /* 0000 0100 */
#define BL              0x08    /* 0000 1000 . 0 = Off. 1 = On */


/******************************** Comandos ***********************************/
/* La conexión entre el I2C y el LCD solo abarca 4 pines de datos
 * por lo que los comandos (8 bits de largo) deben ser enviados primero la parte alta (High Nibble).
 * y luego la parte baja (Low Nibble). Los primeros 4bits son los datos del comandos
 * y el resto son los pines de control.
 ******************************************************************************/
#define CMD_CLEAR_DISPLAY_HN    0x00    /* 0000 0000 */
#define CMD_CLEAR_DISPLAY_LN    0X10    /* 0001 0000 */

#define CMD_RETURN_HOME_HN      0x00    /* 0000 0000 */
#define CMD_RETURN_HOME_LN      0X30    /* 0011 0000 */

/* Entry Mode Set */
/* Todos estos comandos comparten el mismo High Nibble. */
#define CMD_ENTRY_MODE_SET_HN                           0X00    /* 0000 0000 */
#define CMD_ENTRY_MODE_SET_OFF_LN                       0x40    /* 0100 0000 */
#define CMD_ENTRY_MODE_CURSOR_RIGHT_LN                  0X20    /* 0010 0000*/
#define CMD_ENTRY_MODE_DISPLAY_SHIFT_LN                 0X10    /* 0001 0000*/

/* Display Control */
/* Todos estos comandos comparten el mismo High Nibble. */
#define DISPLAY_HN              0x00    /* 0000 0000 */
#define DISPLAY_OFF_LN          0X80    /* 1000 0000 */
#define DISPLAY_ON_LN           0X40    /* 0100 0000 */
#define CURSOR_ON_LN            0x20    /* 0010 0000 */         
#define BLINKING_ON_LN          0x10    /* 0001 0000 */

/* Cursor/Display Shift */
/* Todos estos comandos comparten el mismo High Nibble. */
#define SHIFT_HN              0x10    /* 0001 0000 */
#define SHIFT_OFF_LN          0X00    /* 0000 0000 */
#define SHIFT_RIGHT_LN        0X40    /* 0100 0000 */
#define SHIFT_DISPLAY_LN      0x80    /* 1000 0000 */         

/* Function Set */
/* Todos estos comandos comparten el mismo High Nibble. */
#define FUNCTION_SET_HN                 0x20    /* 0010 0000. Configuracion de 4bits. */ 
#define FUNCTION_SET_2LINE_LN           0X80    /* 1000 0000. 1 = 2 Line Display. 0 = 1 Line Display */
#define FUNCTON_SET_5X10_CHAR_LN        0X40    /* 0100 0000. 1 = 5x10 char set. 0 = 5x8 char set */


/************************************************************************************************************
 *  Typedef para controlar el valor de la luz de fondo.
************************************************************************************************************/
typedef uint8_t backlight_t;

/************************************************************************************************************
 *  Typedef para seleccionar el registro.
************************************************************************************************************/
typedef uint8_t select_register_t;


/************************************************************************************************************
 *  Estructura donde se almacenan los nibbles del Function Set.
************************************************************************************************************/
typedef struct{

        uint8_t hn;
        uint8_t ln;

}function_set_t;

/************************************************************************************************************
 *  Estructura donde se almacenan los nibbles del Display Control.
************************************************************************************************************/
typedef struct{

        uint8_t hn;
        uint8_t ln;

}display_control_t;

/************************************************************************************************************
 *  Estructura donde se almacenan los nibbles del Cursor/Display Shift.
************************************************************************************************************/
typedef struct{

        uint8_t hn;
        uint8_t ln;

}cursor_display_shift_t;

/************************************************************************************************************
 * Estructura interna al driver que no es visible al usuario.
 * Se utiliza para cargar las funciones definidas especificamente como port para
 * el hardware especifico.
************************************************************************************************************/
typedef struct {

        hd44780_t hd44780_control;
        uint8_t data;
        backlight_t  backlight;
        function_set_t function_set;
        cursor_display_shift_t cursor_display_shift;
        display_control_t display_control;
        select_register_t select_register;

}driver_t;

static driver_t driver;

/**
 * @brief Función auxiliar que envía el comando por I2C.
 *      Los comandos se arman de la siguiente manera:
 *              CMD | BL | RS
 * 
 *      Los comandos están dividos en dos partes: High Nibble y Low Nibble.
 *      Esto es porque usando el I2C solo se pueden usar 4bits de datos del LCD.
 *      Por lo que primero hay que enviar la primera mitad del comando y luego la segunda mitad.
 *      
 *      Los bytes a enviar son de la siguiente manera: D7 D6 D5 D4 BL EN RW RS
 *      La primera parte corresponde a los datos y la segunda a los estados de los pines.
 * 
 *      Luego de enviar cada comando hay que "presionar" el pin de enable para que el comando sea tomado por el LCD.  
 * 
 * @param driver Instancia del driver que posee las funciones, comandos y estados a enviar.
 * 
 * @return None.
 */
static void _write_command(drivert_t driver) {
        
}


/**
 * @brief Función interna que hace la secuencia de pulsación del pin de Enable.
 * 
 * @param data Datos a enviar al LCD.
 * 
 * @return None.
 */
/*static void _press_enable(uint8_t data) {

}*/
