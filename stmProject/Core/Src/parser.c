#include "parser.h"
#include <stdlib.h>
#include <ctype.h>

HAL_StatusTypeDef ParseCommand(uint8_t *data, uint16_t first, uint16_t last)
{
	uint16_t pos;
	uint8_t found = 0;
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
			return ParseCommand(data, 0, i);
		}
	}

	return HAL_ERROR;
}
