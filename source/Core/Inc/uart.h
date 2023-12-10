/*
 * uart.h
 *
 *  Created on: Dec 10, 2023
 *      Author: HOANG DUNG
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "software_timer.h"
#include "global.h"
#include "command.h"
#include "stdio.h"
#include "stdlib.h"

void uart_communication_fsm(ADC_HandleTypeDef hadc1, UART_HandleTypeDef huart2);


#endif /* INC_UART_H_ */
