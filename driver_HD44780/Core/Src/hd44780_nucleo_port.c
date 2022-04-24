/*
 * hd44780_nucleo_port.c
 *
 *  Created on: 14 abr. 2022
 *      Author: Ricardo
 */

#include "hd44780_nucleo_port.h"

/* Handler del I2C */
static  I2C_HandleTypeDef hi2c1;


/************************************************************************************************************
 * @brief Esta funcion transmite los datos a través del I2C de la placa nucleo.
 * 
 * @param hi2c Handler del I2C de la placa nucleo.
 * @param address Dirección del esclavo.
 * @param data Datos a enviar.
 * 
 * @return True si se pudo transmitir. False si hubo algún problema.
************************************************************************************************************/
bool i2c_transmit_nucleo_port(uint16_t address, uint8_t data) {

        if(HAL_I2C_Master_Transmit(&hi2c1, address, &data, (uint16_t)1, (uint32_t)10) != HAL_OK)
        {
                return false;
        }

        return true;
}

/************************************************************************************************************
 * @brief Esta funcion implementar un delay en milisegundos.
 * 
 * @param ms Los milisegundos para realizar el delay.
 * 
 * @return None.
 * 
 * @see HAL_Delay.
************************************************************************************************************/
void delay_nucleo_port(uint32_t ms) {
        HAL_Delay(ms);
}


/************************************************************************************************************
  * @brief Funcion de inicializacion del I2C1 generada por la IDE de STM.
  * @param None
  * @retval None
************************************************************************************************************/
static void MX_I2C1_Init(void) {

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }

}

/************************************************************************************************************
 * @brief Esta funcion inicializa el I2C1 de la placa nucleo.
 * 
 * @return None.
 * 
 * @see MX_I2C1_INIT
************************************************************************************************************/
void i2c_init(void) {
        MX_I2C1_Init();
}