/*
 * operations.h
 *
 *  Created on: Apr 17, 2022
 *      Author: marcel
 */

#ifndef INC_OPERATIONS_H_
#define INC_OPERATIONS_H_
#include "main.h"
#include "rtc.h"
#include "quadspi.h"

#define FLASH_SIZE_HERE 0x00100000

#define MEAS_NUM 9

//Structure with measurements
typedef struct measurement {
	uint32_t time;
	uint16_t meas[MEAS_NUM];
} Measurement;

HAL_StatusTypeDef storeData(struct measurement mes);
HAL_StatusTypeDef sendData();

#endif /* INC_OPERATIONS_H_ */
