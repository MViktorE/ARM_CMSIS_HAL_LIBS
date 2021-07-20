#include "spi_cmsis_m3_mve_v0.h"

void SPI1_Init(void){
	//Включаем тактирование SPI1 и GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN;

	//Для начала сбрасываем все конфигурационные биты в нули
	GPIOA->CRL &= ~(GPIO_CRL_CNF5_Msk | GPIO_CRL_MODE5_Msk
	| GPIO_CRL_CNF6_Msk | GPIO_CRL_MODE6_Msk
	| GPIO_CRL_CNF7_Msk | GPIO_CRL_MODE7_Msk);

	//Настроаиваем
	//SCK: MODE5 = 0x03 (11b); CNF5 = 0x02 (10b)
	GPIOA->CRL |= (0x02<<GPIO_CRL_CNF5_Pos) | (0x03<<GPIO_CRL_MODE5_Pos);

	//MISO: MODE6 = 0x00 (00b); CNF6 = 0x01 (01b)
	GPIOA->CRL |= (0x01<<GPIO_CRL_CNF6_Pos) | (0x00<<GPIO_CRL_MODE6_Pos);

	//MOSI: MODE7 = 0x03 (11b); CNF7 = 0x02 (10b)
	GPIOA->CRL |= (0x02<<GPIO_CRL_CNF7_Pos) | (0x03<<GPIO_CRL_MODE7_Pos);

	SPI1->CR1 &= ~SPI_CR1_DFF; //Размер кадра 8 бит
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST; //MSB first
	SPI1->CR1 |= SPI_CR1_SSM; //Программное управление SS
	SPI1->CR1 |= SPI_CR1_SSI; //SS в высоком состоянии
	SPI1->CR1 |= 0x04<<SPI_CR1_BR_Pos; //Скорость передачи: F_PCLK/32
	SPI1->CR1 |= SPI_CR1_MSTR; //Режим Master (ведущий)
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	SPI1->CR1 &= ~SPI_CR1_CPHA; //Режим работы SPI: 0

	SPI1->CR1 |= SPI_CR1_SPE; //Включаем SPI
}

void SPI1_Write(uint16_t data){
	//Ждем, пока не освободится буфер передатчика
	while(!(SPI1->SR & SPI_SR_TXE));
	//заполняем буфер передатчика
	SPI1->DR = data;
}
