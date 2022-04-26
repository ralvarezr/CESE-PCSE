/*
 * hd44780_nucleo_port.h
 *
 *  Created on: 14 abr. 2022
 *      Author: Ricardo
 */

#ifndef INC_HD44780_NUCLEO_PORT_H_
#define INC_HD44780_NUCLEO_PORT_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>


void i2c_init(void);

void i2c_transmit_nucleo_port(uint16_t address, uint8_t data);

void delay_ms_nucleo_port(uint32_t ms);

void delay_us_nucleo_port(uint32_t us);

#endif /* INC_HD44780_NUCLEO_PORT_H_ */
