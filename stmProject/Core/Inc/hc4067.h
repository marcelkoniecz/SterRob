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
#include "operations.h"

void readMultipleSensors(ADC_HandleTypeDef  *hadc, uint16_t *data, uint8_t num );

void readMeasurements(ADC_HandleTypeDef *hadc, Measurement *m);

#endif /* INC_HC4067_H_ */
