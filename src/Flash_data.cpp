#include "Flash_data.h"

Flash_data::Flash_data() {
	write = new Write_and_read_data() ;
}

Flash_data::~Flash_data() {
	// TODO Auto-generated destructor stub
}

void Flash_data::setData(char *dane){
	write->sendString("\r\n") ;
	write->writeNewData(dane, data.data_char) ;
}

uint32_t* Flash_data::getData(){
	return data.DATA_32 ;
}
