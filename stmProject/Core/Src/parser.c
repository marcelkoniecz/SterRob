#include "parser.h"

const uint8_t commands[COMMAND_NUM][COMMAND_MAX_SIZE] =
{
		{"GET_TIME"},
		{"SET_TIME"},
		{"GET_ALL_MEAS"},
		{"WORK_MOD_ON"},
		{"WORK_MOD_OFF"},
		{"CHANGE_INT"}
};

uint32_t getCurrTimestamp()
{
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  struct tm currTime;

  HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

  currTime.tm_year = currentDate.Year + 100;
  currTime.tm_mday = currentDate.Date;
  currTime.tm_mon  = currentDate.Month - 1;

  currTime.tm_hour = currentTime.Hours;
  currTime.tm_min  = currentTime.Minutes;
  currTime.tm_sec  = currentTime.Seconds;

  return (uint32_t)mktime(&currTime);
}


uint8_t parseCommand(uint8_t *buf)
{
	uint8_t val;

	switch(buf[0])
	{
	case 'T': // print current time and timestamp
		printCurrTime();
		break;
	case 'D': // print all saved measurments and clear memory
		printf("New measurments:\r\n");
		sendData();
		break;
	case 'P': // stop making new measurements
		working_mode = 0;
		printf("Woorking mode: Stop\r\n");
		break;
	case 'S': // start making new measurements
		working_mode = 1;
		printf("Woorking mode: Start\r\n");
		break;
	case 'I': // change interval between measurements
		val = (buf[1] - '0') * 10 + (buf[2] - '0');
		if(val > 0 && val < 100)
			meas_interval = val;
		printf("Current interval: %d\r\n", meas_interval);
		break;
	default:
		printf("ERROR\r\n");
		return 1;
	}

	return 0;
}

HAL_StatusTypeDef runCommand(Command com)
{
	switch(com.id)
	{
	case GET_TIME: // print current time
	{
		send_cur_time = 1;
		break;
	}
	case SET_TIME: // set current time
	{

	}
	case GET_ALL_MEAS: // print all saved measurments and clear memory
	{
		send_all_data = 1;
		break;
	}
	case WORK_MOD_ON: // stop making new measurements
	{
		working_mode = 0;
		break;

	}
	case WORK_MOD_OFF: // start making new measurements
	{
		working_mode = 1;
		break;
	}
	case CHANGE_INT: // change interval between measurements
	{
		meas_interval = com.data;
		return HAL_ERROR;
		break;

	}
	default:
		return HAL_ERROR;
	}
	return HAL_OK;
}

HAL_StatusTypeDef ParseCommand(uint8_t *data, uint16_t first, uint16_t last)
{
	uint16_t pos;
	uint8_t found = 0;
	Command com;
	uint16_t i;
	for(i = 0; i < COMMAND_NUM; ++i)
	{
		pos = 0;
		while(first + pos <= last)
		{
			if(commands[i][pos] == '\0')
			{
				found = 1;
				break;
			}

			if(data[first + pos] != commands[i][pos])
				break;
			else
			{
				++pos;
			}
		}

		if(found)
		{
			found = 1;
			com.id = i;
			com.data = 0;
			for(uint16_t j = pos; j <= last; ++j)
			{
				if(isdigit(data[j]))
				{
					com.data *= 10;
					com.data += (data[j] - '0');
				}
				else
				{
					break;
				}
			}
			runCommand(com);
			break;
		}
	}

	return (found ? HAL_OK : HAL_ERROR);
}

HAL_StatusTypeDef ParseData(uint8_t *data, uint8_t size)
{
	if(size < 3)
		return HAL_ERROR;

	for(uint16_t i = 0; i < size; ++i)
	{
		if(data[i] == '\n')
		{
			return ParseCommand(data, 0, i - 1);
		}
	}

	return HAL_ERROR;
}
