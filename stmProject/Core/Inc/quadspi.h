/**
  ******************************************************************************
  * File Name          : QUADSPI.h
  * Description        : This file provides code for the configuration
  *                      of the QUADSPI instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __quadspi_H
#define __quadspi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */
//RESET Operations
#define RESET_ENABLE                    0x66  //
#define RESET_MEMORY                    0x99


//IDENTIFICATION Operations
#define READ_ID                              	//NO DUAL, NO QUAD
#define MULTIPLE_I_OR_O_READ_ID         0xAF
#define RD_SRL_FLSH_DISC_PARAM          0xA5


//READ Operations
#define READ                            0x03 	//NO DUAL, NO QUAD
#define FAST_READ                       0x0B
#define DUAL_OUTPUT_FAST_READ           0x3B
#define DUAL_INPUT_OR_OUTPUT_FAST_READ  0x0B


//WRITE Operations
#define WRITE_ENABLE                    0x06
#define WRITE_DISABLE                   0x04


//REGISTER Operations
#define READ_STATUS_REG                 0x05
#define WRITE_STATUS_REG                0x01
#define READ_LOCK_REG                   0xE8
#define WRITE_LOCK_REG                  0xE5
#define READ_FLAG_STAT_REG              0x70
#define CLEAR_FLAG_STAT_REG             0x50
#define READ_NONVOLATILE_CONF_REG       0xB5
#define WRITE_NONVOLATILE_CONF_REG      0xB1
#define READ_VOLATILE_CONF_REG          0x85
#define WRITE_VOLATILE_CONF_REG         0x81
#define READ_ENHANCED_VOL_CONF_REG      0x65
#define WRITE_ENHANCED_VOL_CONF_REG     0x61


//PROGRAM Operations
#define PAGE_PROGRAM                    0x02
#define DUAL_INPUT_FAST_PROGRAM         0xA2
#define EXT_DUAL_INPUT_FAST_PROGRAM
#define QUAD_INPUT_FAST_PROGRAM         0x32 	//NO DUAL
#define EXT_QUAD_INPUT_FAST_PROGRAM				//NO DUAL


//ERASE Operations
#define SUBSECTOR_ERASE                 0x20
#define SECTOR_ERASE                    0xD8
#define BULK_ERASE                      0xC7
#define PROGRAM_OR_ERASE_RESUME         0X7A
#define PROGRAM_OR_ERASE_SUSPEND        0x75


//ONE-TIME PROGRAMMABLE (OTP) Operations
#define READ_OTP_ARRAY                  0x4B
#define PROGRAM_OTP_ARRAY               0x42
/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */

//uint8_t WriteEnable(QSPI_HandleTypeDef* qspi);
//uint8_t qspiMemWrite(QSPI_HandleTypeDef* qspi, uint32_t address, uint32_t size,uint8_t* Data);
//uint8_t qspiMemRead(QSPI_HandleTypeDef* qspi, uint32_t address, uint32_t size,uint8_t* Data);


uint8_t CSP_QUADSPI_Init(void);
uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress, uint32_t EraseEndAddress);
uint8_t CSP_QSPI_Write(uint8_t* buffer, uint32_t address, uint32_t buffer_size);
uint8_t CSP_QSPI_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t CSP_QSPI_Erase_Block(uint32_t BlockAddress);
uint8_t CSP_QSPI_EnableMemoryMappedMode(void);
uint8_t CSP_QSPI_Erase_Chip (void);



/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ quadspi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
