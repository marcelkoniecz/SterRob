/**
 ******************************************************************************
 * File Name          : RTC.c
 * Description        : This file provides code for the configuration
 *                      of the RTC instances.
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
#include "rtc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void) {
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };

	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Initialize RTC and set the Time and Date
	 */
	sTime.Hours = 0;
	sTime.Minutes = 0;
	sTime.Seconds = 0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_JANUARY;
	sDate.Date = 1;
	sDate.Year = 0;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		Error_Handler();
	}

}

void HAL_RTC_MspInit(RTC_HandleTypeDef *rtcHandle) {

	if (rtcHandle->Instance == RTC) {
		/* USER CODE BEGIN RTC_MspInit 0 */

		/* USER CODE END RTC_MspInit 0 */
		/* RTC clock enable */
		__HAL_RCC_RTC_ENABLE();
		/* USER CODE BEGIN RTC_MspInit 1 */

		/* USER CODE END RTC_MspInit 1 */
	}
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef *rtcHandle) {

	if (rtcHandle->Instance == RTC) {
		/* USER CODE BEGIN RTC_MspDeInit 0 */

		/* USER CODE END RTC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_RTC_DISABLE();
		/* USER CODE BEGIN RTC_MspDeInit 1 */

		/* USER CODE END RTC_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
uint8_t setDate(int day, int month, int year, int weekDay) {
	RTC_DateTypeDef Date;
	Date.Date = day;
	Date.Month = month;
	Date.WeekDay = weekDay;
	Date.Year = year;

	if (HAL_RTC_SetDate(&hrtc, &Date, RTC_FORMAT_BIN) == HAL_OK)
		return HAL_OK;
	else
		return HAL_ERROR;

}
uint8_t setTime(int sec, int min, int hour) {
	RTC_TimeTypeDef Time;
	Time.Seconds = sec;
	Time.Minutes = min;
	Time.Hours = hour;

	if (HAL_RTC_SetTime(&hrtc, &Time, RTC_FORMAT_BIN) != HAL_OK)
		return HAL_OK;
	else
		return HAL_ERROR;

}

uint32_t RTCtoSec() {
	RTC_TimeTypeDef Time;
	RTC_DateTypeDef Date;
	HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);
	uint32_t timeSec = 0;
	timeSec += Time.Seconds; //Adding seconds
	timeSec += (Time.Minutes * 60); //Convert minutes to seconds
	timeSec += (Time.Hours * 3600); //Convert hours to seconds
	timeSec += (Date.Date * 24 * 3600); //Convert date to seconds
	timeSec += monthToSec(Date.Month, Date.Year);
	timeSec += (Date.Date * 24 * 3600); //Convert month to seconds
	timeSec += (Date.Year * 365.25 * 24 * 3600); //convert year to seconds
	return timeSec;

}
uint32_t monthToSec(uint8_t month, uint8_t year) {
	uint32_t sec = 0;
	if (year % 4 == 0 && year != 0 && month >= 2)
		sec += 1;
	switch (month) {
	case 1:
		sec += ((31 * 1 + 30 * 0) * 24 * 3600);
		break;
	case 2:
		sec += ((31 * 1 + 30 * 0 + 28) * 24 * 3600);
		break;
	case 3:
		sec += ((31 * 2 + 28) * 24 * 3600);
		break;
	case 4:
		sec += ((31 * 2 + 30 + 28) * 24 * 3600);
		break;
	case 5:
		sec += ((31 * 3 + 30 + 28) * 24 * 3600);
		break;
	case 6:
		sec += ((31 * 3 + 30 * 2 + 28) * 24 * 3600);
		break;
	case 7:
		sec += ((31 * 4 + 30 * 2 + 28) * 24 * 3600);
		break;
	case 8:
		sec += ((31 * 5 + 30 * 2 + 28) * 24 * 3600);
		break;
	case 9:
		sec += ((31 * 5 + 30 * 3 + 28) * 24 * 3600);
		break;
	case 10:
		sec += ((31 * 6 + 30 * 3 + 28) * 24 * 3600);
		break;
	case 11:
		sec += ((31 * 6 + 30 * 4 + 28) * 24 * 3600);
		break;
	case 12:
		sec += ((31 * 7 + 30 * 4 + 28) * 24 * 3600);
		break;
	}
	return sec;

}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
