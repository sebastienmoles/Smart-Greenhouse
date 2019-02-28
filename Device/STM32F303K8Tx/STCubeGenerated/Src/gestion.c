#include "gestion.h"
#include "i2c.h"
#include "adc.h"
#include "pwm.h"
#include "uart.h"
#include <stdlib.h>

#define PWM_MAX	4000

void gestion_serre(void)
{
	
	static uint32_t compteur = 0;
	static uint8_t start_stop = 1;
	
/* Gestion brumisateur ---------------------------------------------------------*/
	if(Consignes_Param.consigne_humidite_air < Humi_temp_t.humidite && compteur < 60000 && start_stop == 1)	// 60000 = 10min
	{
		brumisateur_ON();
		compteur++;
	}else
	{
		start_stop = 0;
		brumisateur_OFF();
		if(compteur != 0)
		{
			compteur--;
		}else
		{
			start_stop = 1;
		}
	}
	
/* Gestion Pompe ---------------------------------------------------------*/
	if(Consignes_Param.consigne_humidite_sol < humidite_sol.poucentage_humi)
	{
		pompe_ON();
	}else
	{
		pompe_OFF();
	}

/* Gestion chauffage ---------------------------------------------------------*/	
	Regulateur_Proportionnel.erreur = Consignes_Param.consigne_temperature - Humi_temp_t.temperature;
	Regulateur_Proportionnel.commande = (uint16_t) Regulateur_Proportionnel.erreur * Regulateur_Proportionnel.Kp;
	
	if(Regulateur_Proportionnel.commande > 4000)
	{
		Regulateur_Proportionnel.commande = 4000;
	}else if (Regulateur_Proportionnel.commande < 0)
	{
		Regulateur_Proportionnel.commande = 0;
	}
	
	pwm_chauffage(Regulateur_Proportionnel.commande);
	
/* Gestion ventilateur ---------------------------------------------------------*/	
	if(Regulateur_Proportionnel.commande > 800) // 20% de PWM_MAX
	{
		pwm_ventilateur(Regulateur_Proportionnel.commande);
	}else if (Humi_temp_t.temperature > Consignes_Param.consigne_temperature)
	{
		pwm_ventilateur(PWM_MAX);
	}else if (Humi_temp_t.humidite > Consignes_Param.consigne_humidite_air)
	{
		pwm_ventilateur(PWM_MAX);
	}
}


void brumisateur_ON(void)
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
}

void brumisateur_OFF(void)
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);
}

void pompe_ON(void)
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);
}

void pompe_OFF(void)
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_RESET);
}

void eclairage_ON(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
}

void eclairage_OFF(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

void LED_ROUGE_ON(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
}

void LED_ROUGE_OFF(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
}

void LED_VERTE_ON(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
}

void LED_VERTE_OFF(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

void Ecriture_Consigne(uint8_t status, uint8_t consigne[2])
{
	uint8_t ok_message[] = "OK\r\n/";
	
	switch (status)
	{
		case 1:
			Consignes_Param.consigne_temperature = atof((char*)consigne);
			uart_transmit(ok_message);	
			break;
		case 2:
			Consignes_Param.consigne_humidite_air = atof((char*)consigne);
			uart_transmit(ok_message);
			break;
		case 3:
			Consignes_Param.consigne_humidite_sol = atof((char*)consigne);
			uart_transmit(ok_message);
			break;
		default:
			break;
	}
		
		
}