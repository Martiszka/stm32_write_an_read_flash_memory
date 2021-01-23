#include "stm32f1xx.h"
#include "stm32f1xx_nucleo.h"
#include "Flash_data.h"
Flash_data *flash_data1 , *flash_data2;

int main(void)
{
	flash_data1 = new Flash_data() ;
	flash_data2 = new Flash_data() ;
	char tab[] ="Test3";
	flash_data1->setData((char*)tab) ;

	uint8_t tab2[] = "Test4" ;
	flash_data2->setData((char*)tab2) ;
}
