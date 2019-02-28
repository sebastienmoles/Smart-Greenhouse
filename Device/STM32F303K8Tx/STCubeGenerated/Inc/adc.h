#ifndef __adc_H
#define __adc_H

#include "stm32f3xx_hal.h"
#include "main.h"

#define SENSOR_IN_WATER	1533
#define SENSOR_IN_AIR	3040

extern ADC_HandleTypeDef hadc1;

typedef struct
{
	
	uint16_t value_adc;
	uint8_t string_hum_sol[20];
	float a;
	float b;
	float poucentage_humi;
	
}T_humidite_sol;

extern T_humidite_sol humidite_sol;

void get_value_hum_sol();

void calibration_hum_sol();

#endif