#ifndef FLASH_DATA_H_
#define FLASH_DATA_H_
#include "Write_and_read_data.h"

#define PAGE_SIZE 32
class Flash_data {
private:
	 UART_HandleTypeDef uart;
public:
	Write_and_read_data *write ;

	struct flashDataStruct{
			int int1;
			int int2;
			double double1;
		//	double double2;
			float float1;
		}  __attribute__ ((__packed__));

		union flashDataBufferUnion{
			flashDataStruct *flashData;
			uint8_t *bytes;
		};

	flashDataBufferUnion flashDataBuffer;
	flashDataStruct flashData;

	void printInfo();
	void printData();

	Flash_data();
   ~Flash_data();
	void setData() ;
	uint8_t* getData() ;
	int getDataSize();
};

#endif /* FLASH_DATA_H_ */
