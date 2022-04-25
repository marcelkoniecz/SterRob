/*
 * hc4067.c
 *
 *  Created on: Apr 18, 2022
 *      Author: kuchto
 */

#include "hc4067.h"
#include "main.h"

void readMultipleSensors(ADC_HandleTypeDef *hadc, uint16_t *data, uint8_t num )
{
	uint16_t  i ;

	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, RESET);


	for(i = 0; i < num; ++i)
	{
		HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, (i>>0) & 0x01);
		HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, (i>>1) & 0x01);
		HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, (i>>2) & 0x01);
		HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, (i>>3) & 0x01);
		HAL_Delay(1);

		HAL_ADC_Start(hadc);

		if (HAL_ADC_PollForConversion(hadc, 10) == HAL_OK)
		{
			data[i] = HAL_ADC_GetValue(hadc);
		}
	}
}

void readMeasurements(ADC_HandleTypeDef *hadc, Measurement *m)
{
	uint16_t i;

	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, RESET);

	for(i = 0; i < MEAS_NUM; ++i)
	{
		HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, (i>>0) & 0x01);
		HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, (i>>1) & 0x01);
		HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, (i>>2) & 0x01);
		HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, (i>>3) & 0x01);

		HAL_ADC_Start(hadc);

		if (HAL_ADC_PollForConversion(hadc, 10) == HAL_OK)
		{
			m->meas[i] = HAL_ADC_GetValue(hadc);
		}
	}

	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, SET);
}

void printData(uint16_t *data, uint8_t num)
{
 uint8_t  i;
 float p;

  for(i = 0; i < num; ++i)
    {
      p = (3.3 * data[i]) / 4095;
      printf("Sensor %d: %d (%3.3f)\r\n", i, data[i],p );
    }
}

void printTimestamp(RTC_HandleTypeDef *hrtc)
{
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  time_t timestamp;
  struct tm currTime;

  HAL_RTC_GetTime(hrtc, &currentTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(hrtc, &currentDate, RTC_FORMAT_BIN);

  currTime.tm_year = currentDate.Year + 100;
  currTime.tm_mday = currentDate.Date;
  currTime.tm_mon  = currentDate.Month - 1;

  currTime.tm_hour = currentTime.Hours;
  currTime.tm_min  = currentTime.Minutes;
  currTime.tm_sec  = currentTime.Seconds;

  timestamp = mktime(&currTime);

  printf("%s\r\n",ctime(&timestamp));
  printf("Time stamp: %lu s \r\n",(uint32_t)timestamp);
  printf("Size time_t: %d, size uint32_t: %d \r\n", sizeof(time_t), sizeof(uint32_t));
}

