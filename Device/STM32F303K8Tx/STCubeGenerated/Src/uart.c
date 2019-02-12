#include "uart.h"
#include "stm32f3xx_it.h"
#include "i2c.h"
#include "adc.h"
#include <stdio.h>
#include <string.h>

extern uint8_t aRxBuffer[7];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	switch (aRxBuffer[0])
	{
		case 0x30 :
			uart_transmit(Humi_temp_t.string_temp);
			break;
		case 0x31 :
			uart_transmit(Humi_temp_t.string_hum);
		break;
		case 0x32 :
			get_value_hum_sol();
			uart_transmit(humidite_sol_t.string_hum_sol);
			break;
	}
	
	HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 7);
}

void uart_transmit(uint8_t *pData)
{
	uint8_t size = 0;
	uint8_t caractereActuel = 0;
	
	do
	{
		caractereActuel = pData[size];
		size++;
	}while(caractereActuel != '/');
	
	size--;

	HAL_UART_Transmit_IT(&huart1, pData, size);
	
}

void init_uart_IT(void)
{
	HAL_NVIC_SetPriority(USART1_IRQn,0,0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
}