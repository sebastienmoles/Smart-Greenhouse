#include "adc.h"
#include "stm32f3xx_it.h"

void get_value_hum_sol()
{
	
	HAL_ADC_Start(&hadc1);
	
	if(HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK)
	{
		humidite_sol.value_adc = HAL_ADC_GetValue(&hadc1);
	}
	
	HAL_ADC_Stop(&hadc1);
	
	humidite_sol.poucentage_humi = ((humidite_sol.a * humidite_sol.value_adc) + humidite_sol.b);
	
	if(humidite_sol.poucentage_humi<0)
	{
		humidite_sol.poucentage_humi=0;
	}else if (humidite_sol.poucentage_humi>100)
	{
		humidite_sol.poucentage_humi = 100;
	}
	
	sprintf((char*)humidite_sol.string_hum_sol , "%.0f Pourcent\r\n/", humidite_sol.poucentage_humi);
	
}
void calib_hum_sol()
{
	humidite_sol.a = -0.06635700066; //(100 / (SENSOR_IN_WATER - SENSOR_IN_AIR));
	humidite_sol.b =  200.64; //-(SENSOR_IN_AIR * humidite_sol_t.a);
}