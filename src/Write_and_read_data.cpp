#define STM32_F1
//#define STM32_F4
//#define STM32_F7  // F756xx, F74xxx

#include "Write_and_read_data.h"

Write_and_read_data::Write_and_read_data() {
	SystemCoreClock = 8000000;
	HAL_Init();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pin = GPIO_PIN_2;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpio);

	gpio.Mode = GPIO_MODE_AF_INPUT;
	gpio.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio);

	uart.Instance = USART2;
	uart.Init.BaudRate = 9600;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&uart);

}
uint32_t Write_and_read_data::flashWriteData(uint8_t *DATA_8 , int size){

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError ;

#ifdef STM32_F1
		uint32_t IncAddress = 4 ;
		uint32_t *DATA ;
		uint32_t StartAddress = StartPageAddress = 0x0801F800 ;
		uint32_t ProgramType = FLASH_TYPEPROGRAM_WORD ;
		uint32_t ErrorType = PAGEError ;

		int NumberOfWords = size / 4;
		if(size % 4 > 0)
			NumberOfWords++;

		uint32_t DATA_32[NumberOfWords];

		union dataToFlashUnion{
			uint32_t *dataToFlash;
			uint8_t *bytes;
		};

		dataToFlashUnion dataToFlash;
		dataToFlash.dataToFlash = DATA_32;

		for(int i = 0; i < size; i++){
			dataToFlash.bytes[i] = DATA_8[i];
		}
		DATA = &DATA_32[0] ;

		HAL_FLASH_Unlock();

		uint32_t StartPage = getPage(StartAddress);
		uint32_t EndPageAdress = StartAddress + NumberOfWords*4 ;
		uint32_t EndPage = getPage(EndPageAdress);

		EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress = StartPage;
		EraseInitStruct.NbPages     = ((EndPage - StartPage)/FLASH_PAGE_SIZE) +1;

#endif

#ifdef STM32_F4
		StartPageAddress = StartAddress = 0x08010000 ;
		uint32_t FlashSector = FLASH_SECTOR_4 ;  //64 Kbytes
#endif

#ifdef STM32_F7
		StartPageAddress = StartAddress = 0x08018000 ;
		uint32_t FlashSector = FLASH_SECTOR_3 ;
#endif

#if defined (STM32_F4) || defined (STM32_F7)
		NumberOfWords = size ;
		uint32_t IncAddress = 1 ;
		uint8_t *DATA = &DATA_8[0]  ;
		uint32_t ProgramType = FLASH_TYPEPROGRAM_BYTE ;
		uint32_t ErrorType = SECTORError ;

		HAL_FLASH_Unlock();

		EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
		EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
		EraseInitStruct.Sector        = FlashSector ;
		EraseInitStruct.NbSectors     = 1 ;

#endif

	int sofar = 0 ;
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &ErrorType) != HAL_OK){
		return HAL_FLASH_GetError ();
	}
	while( sofar < NumberOfWords ){
		if (HAL_FLASH_Program(ProgramType, StartAddress, DATA[sofar]) == HAL_OK){
			StartAddress += IncAddress;
			sofar++;
		}
		else{
			return HAL_FLASH_GetError ();
		}
	}
		HAL_FLASH_Lock();
		return 0;
}

void Write_and_read_data::flashReadData(uint32_t *DATA_32){

	uint32_t index = 0 ;
	while (1){
		*DATA_32 = *( uint32_t*)(StartPageAddress+index);
		if (*DATA_32 == 0xffffffff){
			*DATA_32 = '\0';
			break;
		}
		index += 4;
		DATA_32++ ;
	}
}

void Write_and_read_data::sendChar(char c){
	HAL_UART_Transmit(&uart, (uint8_t*)&c, 1, 1000);
}
void Write_and_read_data::sendString(char* s){
	HAL_UART_Transmit(&uart, (uint8_t*)s, strlen(s), 1000);
}
uint32_t Write_and_read_data::getPage(uint32_t Address){

	for (int indx=0; indx<128; indx++){
		if((Address < (0x08000000 + (1024 *(indx+1))) ) && (Address >= (0x08000000 + 1024*indx))){
			return (0x08000000 + 1024*indx);
		}
	}
	return -1;
}
Write_and_read_data::~Write_and_read_data() {
	// TODO Auto-generated destructor stub
}
