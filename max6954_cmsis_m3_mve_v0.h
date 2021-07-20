/*
 * max6954_cmsis_m3_mve_v0.h
 *
 * Created on: Jul 12, 2021
 * Author: MVE
 * The SPI and DELAY be must be pre-initialized!!!!!!!!!!!!!!
 * 1) !!!!!!!!!!!!!!!!! CS Doesn't work on A port (A port use foe spi)
 *
 */

#ifndef MAX6954_CMSIS_m3_MVE_V0_H
#define MAX6954_CMSIS_m3_MVE_V0_H

#include "main.h"
#include "string.h"


// !!! Choose SPI channel, CS Port and CS Pin!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Port B, pin 0
#define CS_MAX6954_PORT GPIOC				// Use Port C
#define CS_RCC			RCC_APB2ENR_IOPCEN	// IOPAEN - Port A, IOPBEN - Port B etc...
#define CS_MAX6945_Pin	13					// Use PC13
// ------------------------------------------------------------------------------------------------------------------

//Defines for CS PORT -------------------------------------------------------------------------------------------
#if (CS_MAX6945_Pin > 7)
	#define CS_CR 			CRH
	#define CS_CR_CNF_POS	(CS_MAX6945_Pin-8)*4+2
	#define CS_CR_MODE_POS	(CS_MAX6945_Pin-8)*4
#else
	#define CS_CR			CRL
	#define CS_CR_CNF_POS	CS_MAX6945_Pin*4+2
	#define CS_CR_MODE_POS	CS_MAX6945_Pin*4
#endif

#define CS_SET		CS_MAX6954_PORT->BSRR |= (0x1UL << CS_MAX6945_Pin);
#define CS_RESET	CS_MAX6954_PORT->BSRR |= (0x1UL << (CS_MAX6945_Pin+16));

// Defines for MAX6954 --------------------------------------------------------------------------------------
#define digitShift 		0x30 			// числа идут по порядку начиная с этого адреса
#define digitAddress	0x20 			// адрес первой из 8 цифр

// Special Defines for IEE RAS project ---------------------------------------------------------------------
#define voltageDigit	digitAddress	// первые 4 цифры напряжение
#define currentDigit	digitAddress+4	// вторые 4 цифры то

// function prototype list --------------------------------------------------------------------------------
void CS_Init(void);
void max6954_Test(uint32_t time);
void max6954_Init();
void max6954_SendV(uint16_t);
void max6954_SendI(float);
void max6954_SendText(char*, uint8_t);
void max6954_SetGlobalIntensity(uint8_t); // от 1 до 16

//void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)


#endif /* MAX6954_HAL_MVE_H_ */
