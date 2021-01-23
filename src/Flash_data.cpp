#include "Flash_data.h"

Flash_data::Flash_data() {
	write = new Write_and_read_data() ;
}

Flash_data::~Flash_data() {
	// TODO Auto-generated destructor stub
}

void Flash_data::setData(){
	write->sendString("\r\n") ;
	write->flashWriteData(getData(), getDataSize()) ;
}


int Flash_data::getDataSize(){
	return sizeof(flashData); //
}

uint8_t* Flash_data::getData(){
	return flashDataBuffer.bytes;
}


