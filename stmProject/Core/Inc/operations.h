/*
 * operations.h
 *
 *  Created on: Apr 17, 2022
 *      Author: marcel
 */

#ifndef INC_OPERATIONS_H_
#define INC_OPERATIONS_H_
#include "main.h"


#define FLASH_SIZE_HERE 0x00100000

//Structure with measurements
struct measurement {
	uint16_t time;
	uint16_t meas[9];
};


HAL_StatusTypeDef storeData(struct measurement mes);
uint16_t sendData();


#endif /* INC_OPERATIONS_H_ */
