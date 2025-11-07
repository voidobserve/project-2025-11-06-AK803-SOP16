/****************************************************************************
@FILENAME:	e2prom_access.c
@FUNCTION:	handle e2prom access functon
@AUTHOR:	flege.zhang
@DATE:		2020.01.08
@COPYRIGHT(C) ZXW 2020
*****************************************************************************/


#include "e2prom_access.h"
#include "delay.h"


void e2prom_init(void)
{
	iic_init();
}

uint8_t e2prom_write_bytes(uint16_t sub_addr, uint8_t* data, uint8_t data_len, uint8_t try_times)
{
	uint8_t status;

	while(try_times--)
	{
		status = iic_write_bytes(sub_addr, data, data_len);

		delay_ms(5);

		if(status == 0x0)//SUCCESS
		{
			break;
		}
	}

	return status;
}

uint8_t e2prom_read_bytes(uint16_t sub_addr, uint8_t* data, uint8_t data_len, uint8_t try_times)
{
	uint8_t status;

	while(try_times--)
	{
		status = iic_read_bytes(sub_addr, data, data_len);

		delay_ms(5);
		
		if(status == 0x0)//SUCCESS
		{
			break;
		}
	}

	return status;
}

