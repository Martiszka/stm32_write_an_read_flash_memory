#include "Flash_data.h"

Flash_data::Flash_data() {
	write = new Write_and_read_data() ;
}

Flash_data::~Flash_data() {
	// TODO Auto-generated destructor stub
}

void Flash_data::setData(uint8_t *dane){
	write->writeNewData(dane) ;
}
