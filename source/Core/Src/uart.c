/*
 * uart.c
 *
 *  Created on: Dec 10, 2023
 *      Author: HOANG DUNG
 */
#include "uart.h"

void uart_communication_fsm(ADC_HandleTypeDef hadc1, UART_HandleTypeDef huart2) {
	switch(status_uart) {
		case WAIT_RST:
			// If completed command = "RST" -> status = SEND_ADC, update ADC_Value, set command_flag = 0 and setTimer
			if (command_flag == 1) {
				command_flag = 0;
				if (command[0] == 'R' && command[1] == 'S' && command[2] == 'T') {
					// Get ADC value
					HAL_ADC_Start(&hadc1);
					ADC_value = HAL_ADC_GetValue(&hadc1);
					HAL_ADC_Stop(&hadc1);
					HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\n"), 1000);
					status_uart = SEND_ADC;
					setTimer(1, 3000);
				}
			}
			break;

		case SEND_ADC:
			// Display ADC Value on console, status = WAIT_OK
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC=%lu#\r\n", ADC_value), 1000);
			status_uart = WAIT_OK;
			break;

		case WAIT_OK:
			// If completed command = "OK" -> status = WAIT_RST and clearTimer
			if (command_flag == 1) {
				command_flag = 0;
				if (command[0] == 'O' && command[1] == 'K') {
					HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\n"), 1000);
					status_uart = WAIT_RST;
					clearTimer(1);
				}
			}
			// Else if each after 3s doesn't receive "OK" -> status = SEND_ADC and setTimer
			if(timer_flag[1] == 1) {
				status_uart = SEND_ADC;
				setTimer(1, 3000);
			}
			break;
		default:
			break;
	}
}
