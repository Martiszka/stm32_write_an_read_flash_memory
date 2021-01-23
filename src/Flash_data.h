#ifndef FLASH_DATA_H_
#define FLASH_DATA_H_
#include "Write_and_read_data.h"

class Flash_data {
private:
	 UART_HandleTypeDef uart;
public:
	Write_and_read_data *write ;
	union data_32{
		uint32_t DATA_32[100] ;
		uint8_t data_bytes[400];
		char	data_char[400];
	};
	data_32 data ;
	Flash_data();
   ~Flash_data();
	void setData(char *dane) ;
	uint32_t* getData() ;
};

#endif /* FLASH_DATA_H_ */
