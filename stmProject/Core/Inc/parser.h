

#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "rtc.h"
#include "operations.h"

extern uint8_t working_mode;
extern uint8_t meas_interval;

void printCurrTime();
uint8_t parseCommand(uint8_t *buf);

#endif /* INC_PARSER_H_ */
