#include "stm32f1xx.h"
#include "stm32f1xx_nucleo.h"
#include "Flash_data.h"
Flash_data *flash_data1 , *flash_data2;

int main(void)
{

	Flash_data *flash = new Flash_data();
		flash->flashData.int1 = 65539;
		//flash->flashData.int2 = 3;
		//flash->flashData.double1 = 45.34;
		//flash->flashData.float1 = 0.01f;

	//	flash->printInfo();
	//	flash->printData();
		flash->setData() ;
}
