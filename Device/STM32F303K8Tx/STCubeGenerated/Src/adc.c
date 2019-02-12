#include "adc.h"
#include "stm32f3xx_it.h"

void get_value_hum_sol()
{
	
	float pourcentage_humi = 0;
	
	HAL_ADC_Start(&hadc1);
	
	if(HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK)
	{
		humidite_sol_t.value_adc = HAL_ADC_GetValue(&hadc1);
	}
	
	HAL_ADC_Stop(&hadc1);
	
	pourcentage_humi = ((humidite_sol_t.a * humidite_sol_t.value_adc) + humidite_sol_t.b);
	
	if(pourcentage_humi<0)
	{
		pourcentage_humi=0;
	}else if (pourcentage_humi>100)
	{
		pourcentage_humi = 100;
	}
	
	sprintf((char*)humidite_sol_t.string_hum_sol , "%.0f Pourcent/", pourcentage_humi);
	
}
void calib_hum_sol()
{
	humidite_sol_t.a = -0.06635700066; //(100 / (SENSOR_IN_WATER - SENSOR_IN_AIR));
	humidite_sol_t.b =  200.64; //-(SENSOR_IN_AIR * humidite_sol_t.a);
}