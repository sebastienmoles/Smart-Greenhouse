#include "uart.h"
#include "stm32f3xx_it.h"
#include "i2c.h"
#include "adc.h"
#include "pwm.h"
#include "gestion.h"
#include <stdio.h>
#include <string.h>

#define recuperation_temperature	0x74	// Code ASCII de la lettre "t"
#define recuperation_humidite_air 0x68	// Code ASCII de la lettre "h"
#define recuperation_humidite_sol	0x73	// Code ASCII de la lettre "s"
#define eclairage_horitcole_ON		0x6F	// Code ASCII de la lettre "o"
#define eclairage_horticole_OFF		0x66	// Code ASCII de la lettre "f"
#define consigne_temperature			0x31	// Code ASCII du chiffre 	 "0"
#define consigne_humidite_air			0x32	// Code ASCII du chiffre	 "1"
#define consigne_humidite_sol			0x33	// COde ASCII du chiffre 	 "2"


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	static uint8_t erreur_commande[] = "Erreur Commande\r\n/";
	static uint8_t info_consigne_temp[] = "Veuillez entrer une consigne de temperature : /";
	static uint8_t info_consigne_humi_air[] = "Veuillez entrer une consigne d'humidite de l'air : /";
	static uint8_t info_consigne_humi_sol[] = "Veuillez entrer une consigne d'humidite du sol : /";
	static uint8_t status = 0;

	if(status == 0)
	{
		switch (aRxBuffer[0])
		{
			case recuperation_temperature :
				uart_transmit(Humi_temp_t.string_temp);
				break;
			case recuperation_humidite_air :
				uart_transmit(Humi_temp_t.string_hum);
				break;
			case recuperation_humidite_sol :
				get_value_hum_sol();
				uart_transmit(humidite_sol.string_hum_sol);
				break;
			case eclairage_horitcole_ON :
				eclairage_ON();
				break;
			case eclairage_horticole_OFF :
				eclairage_OFF();
				break;
			case consigne_temperature :
				uart_transmit(info_consigne_temp);
				status = 1;
				HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 2);
				break;
			case consigne_humidite_air :
				uart_transmit(info_consigne_humi_air);
				status = 2;
				HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 2);
				break;
			case consigne_humidite_sol :
				uart_transmit(info_consigne_humi_sol);
				status = 3;
				HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 2);
				break;
			default:
				uart_transmit(erreur_commande);
				break;
		}
	
	}else if (status == 1)
	{
		Ecriture_Consigne(status, aRxBuffer);
		status = 0;
	}else if (status == 2)
	{
		Ecriture_Consigne(status, aRxBuffer);
		status = 0;
	}else if (status == 3)
	{
		Ecriture_Consigne(status, aRxBuffer);
		status = 0;
	}
	
	if(status == 0)
		{
			HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1);
		}
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