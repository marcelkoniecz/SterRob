/*
 * operations.c
 *
 *  Created on: Apr 15, 2022
 *      Author: marcel
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

//Variable with current address
uint32_t curAddr = 0;

//Write date and data to memory
HAL_StatusTypeDef storeData(struct measurement mes) {

	if ((curAddr + 22) >= FLASH_SIZE_HERE)
		return HAL_ERROR;
	uint32_t tmp2;
	tmp2 = mes.time;
	if (CSP_QSPI_Write((uint8_t *)&tmp2, curAddr, 4) != HAL_OK)
		return HAL_ERROR;

	curAddr = curAddr + 4;
	uint16_t tmp = 0;
	for (int i = 0; i < 9; i++) {
		tmp = mes.meas[i];
		if (CSP_QSPI_Write((uint8_t *)&tmp, curAddr, 2) != HAL_OK)
			return HAL_ERROR;
		curAddr = curAddr + 2;
	}
	return HAL_OK;
}

HAL_StatusTypeDef sendData() {
	uint16_t dataNum = 0;
	uint32_t tmpCurAddr = curAddr;
	uint16_t readData[11];
	uint32_t timestamp;

	if (curAddr < 18)
		return HAL_ERROR;

	for (int i = 0; i < (tmpCurAddr / 22); i++) \
	{
		if (CSP_QSPI_Read((uint8_t *)&readData, dataNum * 22, 22) != HAL_OK)
		{
			Error_Handler();
			return HAL_ERROR;
		}

		dataNum++;
		curAddr -= 22;
		timestamp = (readData[1] << 16) | readData[0];
		printf("%lu;", timestamp);

		for (int j = 2; j < 11; j++)
		{
			printf("%d;", readData[j]);
		}
		printf("\n");
	}

	if(CSP_QSPI_EraseSector(0, tmpCurAddr) != HAL_OK)
	{
		Error_Handler();
		return HAL_ERROR;
	}

	return HAL_OK;
}
