/**
  ******************************************************************************
  * File Name          : QUADSPI.c
  * Description        : This file provides code for the configuration
  *                      of the QUADSPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 20;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */
    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PB0     ------> QUADSPI_BK1_IO1
    PB1     ------> QUADSPI_BK1_IO0
    PE10     ------> QUADSPI_CLK
    PE11     ------> QUADSPI_NCS
    */
    GPIO_InitStruct.Pin = QSO_Pin|QSI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = CLK_Pin|CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PB0     ------> QUADSPI_BK1_IO1
    PB1     ------> QUADSPI_BK1_IO0
    PE10     ------> QUADSPI_CLK
    PE11     ------> QUADSPI_NCS
    */
    HAL_GPIO_DeInit(GPIOB, QSO_Pin|QSI_Pin);

    HAL_GPIO_DeInit(GPIOE, CLK_Pin|CS_Pin);

  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

uint8_t memWrite(QSPI_HandleTypeDef* qspi, uint16_t startAdress,uint8_t *buf,uint16_t bufsize){

	if(qspi->Instance!=QUADSPI)
		return !HAL_OK;
	QSPI_CommandTypeDef cmd;
	cmd.AddressMode	= QSPI_ADDRESS_1_LINE;
	cmd.AddressSize = QSPI_ADDRESS_16_BITS;
	cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	cmd.InstructionMode= QSPI_INSTRUCTION_1_LINE;

	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

uint32_t memRead(QSPI_HandleTypeDef* qspi, uint32_t readAdr,uint32_t readSize){

	if(qspi->Instance!=QUADSPI)
		return !HAL_OK;
	uint8_t value=0;
	uint32_t rData=0;
	QSPI_CommandTypeDef cmd;
	cmd.Instruction= READ;
	cmd.Address=readAdr;
	cmd.AlternateByteMode=QSPI_ALTERNATE_BYTES_NONE;
	cmd.AddressSize= QSPI_ADDRESS_32_BITS;
	cmd.DummyCycles=0;
	cmd.InstructionMode= QSPI_INSTRUCTION_1_LINE;
	cmd.AddressMode= QSPI_ADDRESS_1_LINE;
	cmd.DataMode=QSPI_DATA_1_LINE;
	cmd.NbData=readSize;
	cmd.DdrMode=QSPI_DDR_MODE_DISABLE;
	cmd.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;

	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	HAL_QSPI_Command(&qspi, &cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Receive(&qspi, value, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

	//while(HAL_QSPI_Receive(&qspi, value, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
	//	rData=value;
	//	rData<<sizeof(value);
	//	value=0;
	//}

return value;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
