#include "hc4067.h"


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

		for(int i = 0; i < 10000; ++i){}

		HAL_ADC_Start(hadc);

		if (HAL_ADC_PollForConversion(hadc, 10) == HAL_OK)
		{
			m->meas[i] = HAL_ADC_GetValue(hadc);
		}
	}

	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, SET);
}
