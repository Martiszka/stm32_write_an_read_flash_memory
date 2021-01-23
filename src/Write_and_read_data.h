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
	uint32_t flashWriteData(uint8_t *DATA_8, uint32_t size) ;
	void flashReadData(uint8_t *DATA_8) ;
	void writeNewData(char *new_data_8, char *data_8) ;
	void clearMemory() ;
private:
	UART_HandleTypeDef uart;
	uint32_t StartPageAddress = 0x0801FC00 ;
	char read_data[100] ;
};

#endif /* WRITE_AND_READ_DATA_H_ */
