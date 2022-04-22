/*
 * operations.c
 *
 *  Created on: Apr 15, 2022
 *      Author: marcel
 */
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "operations.h"

//Variable with current address
uint32_t curAddr = 0;

//Write date and data to memory
HAL_StatusTypeDef storeData(struct measurement mes) {

	if ((curAddr + 22) >= FLASH_SIZE_HERE)
		return HAL_ERROR;
	uint32_t tmp2 = 0;
	tmp2 = mes.time;
	if (CSP_QSPI_Write(&tmp2, curAddr, 4) != HAL_OK)
		return HAL_ERROR;

	curAddr = curAddr + 4;
	uint16_t tmp = 0;
	for (int i = 0; i < 9; i++) {
		tmp = mes.meas[i];
		if (CSP_QSPI_Write(&tmp, curAddr, 2) != HAL_OK)
			return HAL_ERROR;
		curAddr = curAddr + 2;
	}
	return HAL_OK;
}

uint16_t sendData() {
	uint16_t dataNum = 0;
	uint32_t tmpCurAddr = curAddr;
	static uint16_t readData[11];
	//string uartData;
	if (curAddr < 18)
		return dataNum;
	for (int i = 0; i < (tmpCurAddr / 22); i++) {
		if (CSP_QSPI_Read(&readData, dataNum * 22, 22) != HAL_OK)
			return -1;
		dataNum++;
		curAddr = curAddr - 22;
		printf("%d. ", i);
		for (int i = 0; i < 11; i++)
			printf("%d ", readData[i]);
		printf("\n\r");
	}
	if (CSP_QSPI_Erase_Chip() != HAL_OK)
		return -2;
	return dataNum;
}

