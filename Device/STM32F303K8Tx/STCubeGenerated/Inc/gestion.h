#ifndef __gestion_H
#define __gestion_H

#include "stm32f3xx_hal.h"
#include "main.h"
 
typedef struct Consignes_Param
{
	float consigne_temperature;
	float consigne_humidite_air;
	float consigne_humidite_sol;

}Consignes_Param;

extern Consignes_Param Consignes_Param_t;

void gestion_serre(void);

void brumisateur_ON(void);
void brumisateur_OFF(void);

void pompe_ON(void);
void pompe_OFF(void);

void eclairage_ON(void);
void eclairage_OFF(void);

void LED_ROUGE_ON(void);
void LED_ROUGE_OFF(void);

void LED_VERTE_ON(void);
void LED_VERTE_OFF(void);

#endif
