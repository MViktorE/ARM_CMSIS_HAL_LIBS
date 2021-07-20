/*
 * max6954_hal_mve_v0.c
 *
 *  Created on: Jun 18, 2021
 *      Author: mve
 */
#include "max6954_hal_mve_v0.h"

void max6954_Test(uint16_t time){
	uint8_t address = 0x07;
	uint8_t data = 1;
	HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
	HAL_SPI_Transmit(&channelSPI, &data, 1, 100);
	HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
	HAL_Delay(time);
	data = 0;
	HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
	HAL_SPI_Transmit(&channelSPI, &data, 1, 100);
	HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
}

void max6954_Init(){
	uint8_t address = 0x04;
	uint8_t data = 1;
	HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
	HAL_SPI_Transmit(&channelSPI, &data, 1, 100);
	HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
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
			HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
			HAL_SPI_Transmit(&channelSPI, &data, 1, 100);
			HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
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
			HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
			HAL_SPI_Transmit(&channelSPI, &data, 1, 100);
			HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
		}
	}
}

void max6954_SendText(char *input, uint8_t position){
	if (position > 8) {
		uint8_t address = digitAddress;
		char* data = "ErrorPos";
		for (position = 0; position<8; position++){
				HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
				HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
				HAL_SPI_Transmit(&channelSPI, (uint8_t*)&data, 1, 100);
				HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
				address++;
			}
	}
	else {
		uint8_t address = digitAddress;
		char data;
		for (position = 0; position<8; position++){
			data = input[position];
			HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
			HAL_SPI_Transmit(&channelSPI, (uint8_t*)&data, 1, 100);
			HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
			address++;
		}
	}
}

void max6954_SetGlobalIntensity(uint8_t Intens){
	uint8_t address = 0x02;
	HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&channelSPI, &address, 1, 100);
	HAL_SPI_Transmit(&channelSPI, &Intens, 1, 100);
	HAL_GPIO_WritePin(CS_MAX6954_Port, CS_MAX6945_Pin, GPIO_PIN_SET);
}



