#ifndef WRITE_AND_READ_DATA_H_
#define WRITE_AND_READ_DATA_H_

#include "stm32f1xx.h"
#include "stm32f1xx_nucleo.h"
#include <string.h>

class Write_and_read_data {
public:


	Write_and_read_data();

	virtual ~Write_and_read_data();

	void sendChar(char c);
	void sendString(char* s) ;
    uint32_t getPage(uint32_t Address);
	uint32_t flashWriteData(uint8_t *DATA_8) ;
	void flashReadData(uint8_t *DATA_8) ;
	void writeNewData(uint8_t *new_data_8, uint8_t *data_8) ;
	void clearMemory() ;
private:
	UART_HandleTypeDef uart;
	uint32_t StartPageAddress = 0x0801FC00 ;
	uint8_t new_data[100] , i=0;
	char write_data[100] , read_data[100] ;
};

#endif /* WRITE_AND_READ_DATA_H_ */
