#include "Flash_data.h"
Flash_data::Flash_data() {
	write = new Write_and_read_data() ;
}

Flash_data::~Flash_data() {
	// TODO Auto-generated destructor stub
}

void Flash_data::setData(){
	write->flashWriteData(getData(), getDataSize()) ;
//	write->sendString("after set data  \r\n") ;
}

int Flash_data::getDataSize(){
	return sizeof(flashData); //
}

uint8_t* Flash_data::getData(){
	return flashDataBuffer.bytes;
}

void Flash_data::readData(){
	write->flashReadData(flashDataBuffer.data32);
	write->sendString("Flash data: \r\n") ;
	write->sendString((char*)flashDataBuffer.bytes) ;
	write->sendString("\r\n") ;
}

