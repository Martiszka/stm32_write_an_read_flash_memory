#include <string.h>
#include "stm32f1xx.h"

//#include <stdio.h>
//#include <inttypes.h>

#include "flash.h"

uint32_t data[] = {0x33333333 , 0x55555555} ;

uint32_t Rx_Data[2];

int main(void)
{
	SystemCoreClock = 72000000;
	HAL_Init();



	Flash_Write_Data(0x0801FC00 , data);

	Flash_Read_Data(0x0801FC00, Rx_Data);

}
