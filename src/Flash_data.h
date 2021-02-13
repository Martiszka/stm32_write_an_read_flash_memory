#ifndef FLASH_DATA_H_
#define FLASH_DATA_H_
#include "Write_and_read_data.h"

#define PAGE_SIZE 32
class Flash_data {
public:
	Flash_data();
   ~Flash_data();

	struct pidStruct{
		int P, I, D ;
	};
	struct flashDataStruct{
		int int1;
		int int2;
	//	double double1;
	//	double double2;
	//	float float1;
	}  __attribute__ ((__packed__));

	union flashDataBufferUnion{
		flashDataStruct *flashData;
		uint8_t *bytes;
		uint32_t *data32 ;
	};

	flashDataBufferUnion flashDataBuffer;
	flashDataStruct flashData;

	void printInfo();
	void printData();
	void setData() ;
	uint8_t* getData() ;
	int getDataSize();
	void readData() ;

private:
	 Write_and_read_data *write ;
	 UART_HandleTypeDef uart;
};

#endif /* FLASH_DATA_H_ */
