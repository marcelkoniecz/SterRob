/*
 * operations.c
 *
 *  Created on: Apr 15, 2022
 *      Author: marcel
 */
#include "main.h"

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

	if ((curAddr + 10) >= FLASH_SIZE_HERE)
		return HAL_ERROR;

	if (CSP_QSPI_Write(&(mes.time), curAddr, 2) != HAL_OK)
		return HAL_ERROR;

	curAddr++;

	for (int i = 0; i < 9; i++) {
		if (CSP_QSPI_Write(&(mes.meas[i]), 0, 2) != HAL_OK)
			return HAL_ERROR;
		curAddr++;
	}
return HAL_OK;
}

HAL_DMA_StateTypeDef returnData(uint16_t howMany){


}





