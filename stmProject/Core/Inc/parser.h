#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "rtc.h"
#include "operations.h"

#define COMMAND_MAX_SIZE 20
#define COMMAND_NUM 6

extern uint8_t working_mode;
extern uint8_t meas_interval;

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

void printCurrTime();
uint8_t parseCommand(uint8_t *buf);

#endif /* INC_PARSER_H_ */
