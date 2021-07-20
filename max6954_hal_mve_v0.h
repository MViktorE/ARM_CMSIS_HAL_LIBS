/*
 * max6954_hal_mve_v0.h
 *
 * Created on: Jun 18, 2021
 * Author: MVE
 * The SPI be must be pre-initialized!!!!!!!!!!!!!!
 *
 */

#ifndef MAX6954_HAL_MVE_H_
#define MAX6954_HAL_MVE_H_

#include "main.h"
#include "string.h"

// !!! Choose SPI channel, CS Port and CS Pin!!!
SPI_HandleTypeDef 		hspi1;
#define channelSPI 		hspi1
#define CS_MAX6954_Port CS_MAX6954_GPIO_Port
#define CS_MAX6945_Pin	CS_MAX6954_Pin

#define digitShift 		0x30 			// числа идут по порядку начиная с этого адреса
#define digitAddress	0x20 			// адрес первой из 8 цифр
#define voltageDigit	digitAddress	// первые 4 цифры напряжение
#define currentDigit	digitAddress+4	// вторые 4 цифры ток


void max6954_Test(uint16_t time);
void max6954_Init();
void max6954_SendV(uint16_t);
void max6954_SendI(float);
void max6954_SendText(char*, uint8_t);
void max6954_SetGlobalIntensity(uint8_t); // от 1 до 16

//void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)


#endif /* MAX6954_HAL_MVE_H_ */
