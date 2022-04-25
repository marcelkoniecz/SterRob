#include "parser.h"

void printCurrTime()
{
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  time_t timestamp;
  struct tm currTime;

  HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

  currTime.tm_year = currentDate.Year + 100;
  currTime.tm_mday = currentDate.Date;
  currTime.tm_mon  = currentDate.Month - 1;

  currTime.tm_hour = currentTime.Hours;
  currTime.tm_min  = currentTime.Minutes;
  currTime.tm_sec  = currentTime.Seconds;

  timestamp = mktime(&currTime);

  printf("%s as timestamp %lu\r\n",ctime(&timestamp), (uint32_t)timestamp);
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
		return 1;
	}

	return 0;
}


