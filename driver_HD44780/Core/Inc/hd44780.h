/*
 * hd44780.h
 *
 *  Created on: 14 abr. 2022
 *      Author: Ricardo
 */

#ifndef INC_HD44780_H_
#define INC_HD44780_H_

#include <stdint.h>
#include <stdbool.h>




/************************************************************************************************************
 * typedefs para simplificar la lectura de los punteros a función
 * a usarse dentro de la estructura del driver.
************************************************************************************************************/
typedef void (*i2c_init_t)(void);
typedef void (*i2c_transmit_t)(uint16_t, uint8_t);
typedef void (*delayms_t)(uint32_t);
typedef void (*delayus_t)(uint32_t);

/************************************************************************************************************
 * Estructura del driver
************************************************************************************************************/
struct _hd44780 {
        i2c_init_t i2c_init;
	i2c_transmit_t i2c_write;
	delayms_t delay_ms;
        delayus_t delay_us;
        uint8_t n_rows;
        uint16_t address;
};

typedef struct _hd44780 hd44780_t;


void hd44780_init_driver(hd44780_t config);
void hd44780_write_char(const char car);

#endif /* INC_HD44780_H_ */
