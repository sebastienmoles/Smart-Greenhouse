#ifndef __adc_H
#define __adc_H

#include "stm32f3xx_hal.h"
#include "main.h"

#define SENSOR_IN_WATER	1533
#define SENSOR_IN_AIR	3040

extern ADC_HandleTypeDef hadc1;

typedef struct humidite_sol
{
	
	uint16_t value_adc;
	uint8_t string_hum_sol[20];
	float a;
	float b;
	
}humidite_sol;

extern humidite_sol humidite_sol_t;

void get_value_hum_sol();

void calibration_hum_sol();

#endif