/*
 * hc4067.h
 *
 *  Created on: Apr 18, 2022
 *      Author: kuchto
 */

#ifndef INC_HC4067_H_
#define INC_HC4067_H_

#include "stm32l4xx_hal.h"
#include <time.h>

//int _write(int file, uint8_t *ptr, uint16_t len);

void readMultipleSensors(ADC_HandleTypeDef  *hadc, uint16_t *data, uint8_t num );

void printData(uint16_t *data, uint8_t num);

void printTimestamp(RTC_HandleTypeDef *hrtc);

#endif /* INC_HC4067_H_ */
