/*
 * hd44780_nucleo_port.c
 *
 *  Created on: 14 abr. 2022
 *      Author: Ricardo
 */

#include "hd44780_nucleo_port.h"


/**
 * @brief Esta funcion transmite los datos a través del I2C de la placa nucleo.
 * 
 * @param hi2c Handler del I2C de la placa nucleo.
 * @param address Dirección del esclavo.
 * @param data Datos a enviar.
 * 
 * @return None.
 */
void i2c_transmit_nucleo_port(I2C_HandleTypeDef *hi2c, uint16_t address, uint8_t data) {

        HAL_I2C_Master_Transmit(hi2c, address, &data, (uint16_t)1, (uint32_t)10);
}

/**
 * @brief Esta funcion implementar un delay en milisegundos.
 * 
 * @param ms Los milisegundos para realizar el delay.
 * 
 * @return None.
 * 
 * @see HAL_Delay.
 */
void delay_nucleo_port(uint32_t ms) {
        HAL_Delay(ms);
}