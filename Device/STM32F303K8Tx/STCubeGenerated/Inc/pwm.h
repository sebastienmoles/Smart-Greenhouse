#ifndef __pwm_H
#define __pwm_H

#include "stm32f3xx_hal.h"
#include "main.h"
 

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void start_pwm(void);

void pwm_chauffage(uint16_t duty_cycle);
void pwm_ventilateur(uint16_t duty_cycle);


#endif