#include "uart.h"
#include "stm32f3xx_it.h"
#include "i2c.h"
#include "adc.h"
#include "pwm.h"
#include "gestion.h"
#include <stdio.h>
#include <string.h>

extern uint8_t aRxBuffer[1];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t erreur_commande[16] = "Erreur Commande/";
	
	switch (aRxBuffer[0])
	{
		case 0x74 :
			uart_transmit(Humi_temp_t.string_temp);
			break;
		case 0x68 :
			uart_transmit(Humi_temp_t.string_hum);
		break;
		case 0x73 :
			get_value_hum_sol();
			uart_transmit(humidite_sol_t.string_hum_sol);
			break;
		case 0x6F :
			eclairage_ON();
			break;
		case 0x66 :
			eclairage_OFF();
			break;
		default:
			uart_transmit(erreur_commande);
			break;
	}
	
	HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1);
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