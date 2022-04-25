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
	uint32_t tmp2;
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
	uint16_t readData[11];
	uint32_t timestamp;

	if (curAddr < 18)
		return dataNum;

	for (int i = 0; i < (tmpCurAddr / 22); i++) \
	{
		if (CSP_QSPI_Read(&readData, dataNum * 22, 22) != HAL_OK)
			Error_Handler();
		dataNum++;
		curAddr -= 22;
		timestamp = (readData[1] << 16) | readData[0];
		printf("%d. %lu ", i, timestamp);

		for (int j = 2; j < 11; j++)
		{
			printf("%d ", readData[j]);
		}
		printf("\n\r");
	}

	if(CSP_QSPI_EraseSector(0, tmpCurAddr) != HAL_OK)
		Error_Handler();

	return dataNum;
}

void printCurrTime()
{
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  time_t timestamp;
  struct tm currTime;

  HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

  currTime.tm_year = currentDate.Year + 100;
  currTime.tm_mday = currentDate.Date;
  currTime.tm_mon  = currentDate.Month - 1;

  currTime.tm_hour = currentTime.Hours;
  currTime.tm_min  = currentTime.Minutes;
  currTime.tm_sec  = currentTime.Seconds;

  timestamp = mktime(&currTime);

  printf("%s as timestamp %lu\r\n",ctime(&timestamp), (uint32_t)timestamp);
}

uint8_t parseCommand(uint8_t *buf)
{
	switch(buf[0])
	{
	case 'T': // print current time and timestamp
		printCurrTime();
		break;
	case 'D': // print all saved measurments and clear memory
		sendData();
		break;
	case 'P': // stop making new measurements
		working_mode = 0;
		break;
	default:
		return 1;
	}

	return 0;
}
