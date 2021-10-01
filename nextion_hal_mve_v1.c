/*
 * MVE_Nextion.c
 *
 *  Created on: Apr 12, 2021
 * 	latest version 20210930
 *      Author: MVE
 */

#include "MVE_Nextion.h"

extern UART_HandleTypeDef huart2;
void NEXTION_Send (char *ID, char *extantion, char *string){
	// Если нужно передать строку то ставим \*
	char buf[50] = {0};
	uint8_t Cmd_End[3] = {0xFF,0xFF,0xFF};  // command end sequence
	if (ID[0]=='t'){
		sprintf (buf, "%s.%s=\"%s\"", ID, extantion, string);
	}
	else{
		sprintf (buf, "%s.%s=%s", ID, extantion, string);
	}
	uint8_t len = strlen(buf);
	HAL_UART_Transmit(&huart2, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(&huart2, Cmd_End, 3, 100);
}

