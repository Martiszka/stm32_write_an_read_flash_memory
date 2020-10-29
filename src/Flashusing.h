/*
 * Flashusing.h
 *
 *  Created on: 22.10.2020
 *      Author: Marta
 */


#ifndef FLASHUSING_H_
#define FLASHUSING_H_
#include "stm32f1xx.h"
#include "stm32f1xx_nucleo.h"
#include <string.h>


class Flash_using {

public:
	void sendChar(char c);
	void sendString(char* s) ;
	Flash_using();
	uint32_t flashWriteData(uint8_t *DATA_8, uint32_t StartAddress) ;
	void flashReadData(uint8_t *DATA_8) ;
	static uint32_t getPage(uint32_t Address);
	void clearMemory() ;
	void newData(uint8_t *NEW_DATA8) ;
private:
	UART_HandleTypeDef uart;
	uint32_t StartPageAddress = 0x0801FC00 ;
	uint8_t new_data[100] , i=0;
	char write_data[100] , read_data[100] ;

};

extern "C"{
	void newData(uint8_t *NEW_DATA8) ;
	void sendChar(char c);
	void sendString(char* s) ;
	void clearMemory();
	uint32_t flashWriteData(uint8_t *DATA_8, uint32_t StartAddress) ;
	void flashReadData(uint8_t *DATA_8) ;
	//static
	uint32_t getPage(uint32_t Address);
	//UART_HandleTypeDef uart;
}

#endif /* FLASHUSING_H_ */


