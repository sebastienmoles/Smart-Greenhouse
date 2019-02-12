#ifndef __i2c_H
#define __i2c_H

#include "stm32f3xx_hal.h"
#include "main.h"
 

extern I2C_HandleTypeDef hi2c1;

typedef struct Data_Capteur_Humi_Temp
{
	
	float temperature;
	float humidite;
	uint8_t string_temp[20];
	uint8_t string_hum[20];
	
}Data_Capteur_Humi_Temp;

extern Data_Capteur_Humi_Temp Humi_temp_t; 

void recup_hum_temp_capteur (Data_Capteur_Humi_Temp *monPointeur);

#endif