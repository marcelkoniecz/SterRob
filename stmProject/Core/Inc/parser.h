#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "rtc.h"
#include "operations.h"

#define COMMAND_MAX_SIZE 20
#define COMMAND_NUM 6

static const uint8_t commands[COMMAND_NUM][COMMAND_MAX_SIZE] =
{
		{"GET_TIME"},
		{"SET_TIME"},
		{"GET_ALL_MEAS"},
		{"WORK_MOD_ON"},
		{"WORK_MOD_OFF"},
		{"CHANGE_INT"}
};

typedef enum command_list
{
	GET_TIME,
	SET_TIME,
	GET_ALL_MEAS,
	WORK_MOD_ON,
	WORK_MOD_OFF,
	CHANGE_INT
} CommandList;

typedef struct command_struct
{
	CommandList id;
	uint32_t data;
} Command;

extern Command com;

HAL_StatusTypeDef ParseData(uint8_t *data, uint8_t size);

#endif /* INC_PARSER_H_ */
