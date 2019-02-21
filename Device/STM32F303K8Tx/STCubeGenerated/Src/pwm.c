#include "pwm.h"

void start_pwm(void)
{

	__HAL_RCC_TIM1_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
			
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	
}

void pwm_chauffage(uint16_t duty_cycle)
{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,duty_cycle);
}

void pwm_ventilateur(uint16_t duty_cycle)
{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,duty_cycle);
}
