#include "pwm.h"

void start_pwm(void)
{
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start(&htim3);
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void pwm_chauffage(uint16_t duty_cycle)
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,duty_cycle);
}

void pwm_ventilateur(uint16_t duty_cycle)
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,duty_cycle);
}