#ifndef __uart_H
#define __uart_H

#include "stm32f3xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart1;
void init_uart_IT(void);
void uart_transmit(uint8_t *pData);

#endif