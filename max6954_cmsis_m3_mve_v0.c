/*
 * max6954_cmsis_m3_mve_v0.c
 *
 *  Created on: Jul 15, 2021
 *      Author: MVE
 *
 *
 */

#include "max6954_cmsis_m3_mve_v0.h"

void CS_Init(void){
	RCC->APB2ENR 		   |= CS_RCC; 				// turn on clocking of CS_PORT (4 бит в регистре в 1)
	CS_MAX6954_PORT->CS_CR &= ~(0x3UL << (CS_CR_CNF_POS)); // Сбрасываем биты CNF для выбранного бита. Режим 00 - Push-Pull
	CS_MAX6954_PORT->CS_CR |=  (0x1UL << CS_CR_MODE_POS); // Выставляем бит MODE для выбранного пина. Режим MODE 01 = Max Speed 10MHz
	CS_SET; // выставляем 1 на пине
}

void max6954_Test(uint32_t time){
	uint8_t address = 0x07;
	uint8_t data = 1;
	CS_RESET;
	Delay(1);
	SPI1_Write(address);
	Delay(1);
	SPI1_Write(data);
	Delay(1);
	CS_SET;
	Delay(time);
	data = 0;
	CS_RESET;
	Delay(1);
	SPI1_Write(address);
	Delay(1);
	SPI1_Write(data);
	Delay(1);
	CS_SET;
	Delay(1);
}

void max6954_Init(){
	uint8_t address = 0x04;
	uint8_t data = 1;
	CS_RESET;
	Delay(1);
	SPI1_Write(address);
	Delay(1);
	SPI1_Write(data);
	Delay(1);
	CS_SET;
	Delay(1);
}

void max6954_SendText(char *input, uint8_t shift){
//	if (position > 8) {
//		uint8_t address = digitAddress;
//		char* data = "ErrorPos";
//		for (position = 0; position<8; position++){
//				HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
//				HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
//				HAL_SPI_Transmit(&channelSPI, (uint8_t*)&data, 1, 100);
//				HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
//				address++;
//			}
//	}
//	else {
		uint8_t address = digitAddress;
		char data;
		for (uint8_t position = 0; position<8; position++){
			data = input[position];
			CS_RESET;
			Delay(1);
			SPI1_Write(address+shift);
			Delay(1);
			SPI1_Write(data);
			Delay(1);
			CS_SET;
			address++;
			Delay(1);
		}
//	}
}


void max6954_SendV(uint16_t Voltage){
	if (Voltage > 9999){				// Проверка предела отображения;
		max6954_SendText("OVER", 0);
	}
	else {
		uint8_t address;
		uint8_t data;
		char n[4];
		n[0] = Voltage/1000;
		n[1] = Voltage%1000/100;
		n[2] = Voltage%100/10;
		n[3] = Voltage%10;
		for (uint8_t i = 0; i < 4; i++){
			address = voltageDigit+i;
			data = n[i]+digitShift;
			CS_RESET;
			Delay(1);
			SPI1_Write(address);
			Delay(1);
			SPI1_Write(data);
			Delay(1);
			CS_SET;
		}
	}
}

void max6954_SendI(float Current){
	if (Current > 99.99){
		max6954_SendText("OVER", 4);
	}
	else {
		uint8_t address;
		uint8_t data;
		char n[4];
		n[0] = (uint8_t)Current/10;
		n[1] = (uint8_t)Current%10;
		n[2] = (uint8_t)((uint16_t)(Current*10)%10);
		n[3] = (uint8_t)((uint16_t)(Current*100)%10);
		for (uint8_t i = 0; i < 4; i++){
			address = currentDigit+i;
			data = n[i]+digitShift;
			if (i==1){
				data |= 0b10000000;
			}
			CS_RESET;
			Delay(1);
			SPI1_Write(address);
			Delay(1);
			SPI1_Write(data);
			Delay(1);
			CS_SET;
		}
	}
}



void max6954_SetGlobalIntensity(uint8_t Intens){
	uint8_t address = 0x02;
	CS_RESET;
	Delay(1);
	SPI1_Write(address);
	Delay(1);
	SPI1_Write(Intens);
	Delay(1);
	CS_SET;
}

