#ifndef __gestion_H
#define __gestion_H

#include "stm32f3xx_hal.h"
#include "main.h"
 
typedef struct
{
	float consigne_temperature;
	float consigne_humidite_air;
	float consigne_humidite_sol;

}T_Consignes_Param;

typedef struct
{
	float erreur;
	uint16_t Kp;
	uint16_t commande;
	
}T_Regulateur_Proportionnel;

extern T_Consignes_Param Consignes_Param;

extern T_Regulateur_Proportionnel Regulateur_Proportionnel;

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

void Ecriture_Consigne(uint8_t status, uint8_t consigne[2]);

#endif
