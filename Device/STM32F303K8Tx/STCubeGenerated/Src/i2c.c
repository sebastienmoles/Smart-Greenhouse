#include "i2c.h"
#include "stm32f3xx_it.h"
#include "stdio.h"

static uint8_t data[4] = {0};
static float temp;
static float hum;

void recup_hum_temp_capteur (Data_Capteur_Humi_Temp *monPointeur)
{
	
	HAL_I2C_Master_Transmit(&hi2c1,78,(uint8_t*)data,0,100);
	HAL_Delay(50);
	HAL_I2C_Master_Receive(&hi2c1,78,(uint8_t*)data,4,100);
	hum = (((data[0] & 0x3F) << 8) + (data[1]));
	temp = ((data[2] << 6) + ((data[3] & 0xFC) >> 2));
	
	monPointeur->temperature = (((temp / 16382) * 165) - 40);
	monPointeur->humidite = ((hum / 16382) * 100);
	
	sprintf((char*)monPointeur->string_temp, "%.1f Degre Celsius/", monPointeur->temperature);
	sprintf((char*)monPointeur->string_hum , "%.0f Pourcent/", monPointeur->humidite);
	
}