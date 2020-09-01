#include <string.h>
#include "stm32f1xx.h"


UART_HandleTypeDef uart;

uint32_t StartPageAddress = 0x0801FC00 ;
uint32_t StartAddress = 0x0801FC00 ;

void sendString(char* s){
	HAL_UART_Transmit(&uart, (uint8_t*)s, strlen(s), 1000);
}

static uint32_t getPage(uint32_t Address){
  for (int indx=0; indx<128; indx++){
      if((Address < (0x08000000 + (1024 *(indx+1))) ) && (Address >= (0x08000000 + 1024*indx))){
          return (0x08000000 + 1024*indx);
      }
  }
  return -1;
}

uint32_t flashWriteData(uint8_t *DATA_8){

	uint32_t DATA_32[(strlen((char*)DATA_8)/4)+(int)((strlen((char*)DATA_8)%4) != 0)] ;
	memset((uint8_t*)DATA_32, 0, strlen((char*)DATA_32));
	strcpy((char*)DATA_32, (char*)DATA_8);

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError;
	int sofar=0;

	int numberofwords = (strlen(DATA_32)/4) + ((strlen(DATA_32) % 4) != 0);

	HAL_FLASH_Unlock();

	uint32_t StartPage = getPage(StartPageAddress);
	uint32_t EndPageAdress = StartPageAddress + numberofwords*4;
	uint32_t EndPage = getPage(EndPageAdress);

	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = StartPage;
	EraseInitStruct.NbPages     = ((EndPage - StartPage)/FLASH_PAGE_SIZE) +1;

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK){
		return HAL_FLASH_GetError ();
	}
	while( sofar < numberofwords ){
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartPageAddress, DATA_32[sofar]) == HAL_OK){
			StartPageAddress += 4;  // use StartPageAddress += 2 for half word and 8 for double word
			sofar++;
		}
		else{
			return HAL_FLASH_GetError ();
		}
	}

	HAL_FLASH_Lock();

	return 0;
}

void flashReadData(uint8_t *DATA_8){
	uint32_t DATA_32, index = 0 ;
	while (1){
		DATA_32 = *( uint32_t*)(StartAddress+index);

		if (DATA_32 == 0xffffffff){
			DATA_32 = '\0';
			break;
		}

		DATA_8[index] = (uint8_t)DATA_32;
		DATA_8[index + 1] = (uint8_t)(DATA_32 >> 8);
		DATA_8[index + 2] = (uint8_t)(DATA_32 >> 16);
		DATA_8[index + 3] = (uint8_t)(DATA_32 >> 24);
		index += 4;
	}
}

int main(void){

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
	uart.Init.BaudRate = 115200;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&uart);

	char write_data[50];
	memset(write_data, 0, sizeof(write_data));
	strcpy(write_data, "Test1");
	flashWriteData((uint8_t*)write_data) ;

	char read_data[50];

	while (1){
		if (__HAL_UART_GET_FLAG(&uart, UART_FLAG_RXNE) == SET){
			uint8_t value;
			HAL_UART_Receive(&uart, &value, 1, 100);

			memset(read_data, 0, sizeof(read_data));
			flashReadData((uint8_t*)read_data);
			sendString(read_data) ;
			sendString("\r\n") ;
		}
	}
}
