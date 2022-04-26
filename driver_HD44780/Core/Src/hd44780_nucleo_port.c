/*
 * hd44780_nucleo_port.c
 *
 *  Created on: 14 abr. 2022
 *      Author: Ricardo
 */

#include "hd44780_nucleo_port.h"

/* Handler del I2C */
static I2C_HandleTypeDef hi2c1;


/************************************************************************************************************
 * @brief Esta funcion transmite los datos a través del I2C de la placa nucleo.
 * 
 * @param hi2c Handler del I2C de la placa nucleo.
 * @param address Dirección del esclavo.
 * @param data Datos a enviar.
 * 
************************************************************************************************************/
void i2c_transmit_nucleo_port(uint16_t address, uint8_t data) {

        HAL_I2C_Master_Transmit(&hi2c1, address, &data, (uint16_t)1, (uint32_t)10);
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
void delay_ms_nucleo_port(uint32_t ms) {
        HAL_Delay(ms);
}

/************************************************************************************************************
 * @brief Esta funcion inicializa el delay en microsegundos.
 * 
 * @return True si fue inicializado. False si hubo un error.
 * 
 * Fuente: https://deepbluembedded.com/stm32-delay-microsecond-millisecond-utility-dwt-delay-timer-delay/
************************************************************************************************************/
static bool delay_us_nucleo_port_init(void) {
    /* Disable TRC */
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
    /* Enable TRC */
    CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;
 
    /* Disable clock cycle counter */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
    /* Enable  clock cycle counter */
    DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;
 
    /* Reset the clock cycle counter value */
    DWT->CYCCNT = 0;
 
    /* 3 NO OPERATION instructions */
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
 
    /* Check if clock cycle counter has started */
    if(DWT->CYCCNT)
    {
       return 0; /*clock cycle counter started*/
    }
    else
    {
      return 1; /*clock cycle counter not started*/
    }
}

/************************************************************************************************************
 * @brief Esta funcion realiza un delay en microsegundos.
 * 
 * @return None.
 * 
 * Fuente: https://deepbluembedded.com/stm32-delay-microsecond-millisecond-utility-dwt-delay-timer-delay/
************************************************************************************************************/
void delay_us_nucleo_port(volatile uint32_t au32_microseconds) {
        
        uint32_t au32_initial_ticks = DWT->CYCCNT;
        uint32_t au32_ticks = (HAL_RCC_GetHCLKFreq() / 1000000);
        au32_microseconds *= au32_ticks;
        while ((DWT->CYCCNT - au32_initial_ticks) < au32_microseconds-au32_ticks);
}

/************************************************************************************************************
  * @brief  Fucion Handler de errores de ST.
  * @retval None
************************************************************************************************************/
static void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


/************************************************************************************************************
  * @brief Funcion de inicializacion del I2C1 generada por la IDE de STM.
  * @param None
  * @return None
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
  
  /* Se inicializa el delay de us */
  if (delay_us_nucleo_port_init() == false)
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
void i2c_init_nucleo_port(void) {
        MX_I2C1_Init();
}

