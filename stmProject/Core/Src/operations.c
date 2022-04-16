/*
 * operations.c
 *
 *  Created on: Apr 15, 2022
 *      Author: marcel
 */
#include "main.h"
#include <stdio.h>
#include <string.h>
#define FLASH_SIZE_HERE 0x00FFFFFF

//Variable with current address
uint32_t curAddr = 0;

//Structure with measurements
struct measurement {
	uint16_t time;
	uint16_t meas[9];
};

//Write date and data to memory
HAL_StatusTypeDef storeData(struct measurement mes) {

	if ((curAddr + 20) >= FLASH_SIZE_HERE)
		return HAL_ERROR;

	if (CSP_QSPI_Write(&(mes.time), curAddr, 2) != HAL_OK)
		return HAL_ERROR;

	curAddr++;

	for (int i = 0; i < 9; i++) {
		if (CSP_QSPI_Write(&(mes.meas[i]), curAddr, 2) != HAL_OK)
			return HAL_ERROR;
		curAddr++;
	}
	return HAL_OK;
}

uint16_t sendData() {
	uint16_t dataNum = 0;
	uint32_t tmpCurAddr = curAddr;
	uint16_t readData[20];
	//string uartData;
	if (curAddr < 20)
		return dataNum;
	for (int i = 0; i < (tmpCurAddr / 20); i++) {
		if (CSP_QSPI_Read(&readData, curAddr, 20) != HAL_OK)
			return -1;
		dataNum++;
		curAddr = curAddr - 10;
		//strncpy(uartData,readData,20);
		printf("%s", readData);
	}
	if(CSP_QSPI_Erase_Chip()!= HAL_OK)
		return -2;
	return dataNum;
}

