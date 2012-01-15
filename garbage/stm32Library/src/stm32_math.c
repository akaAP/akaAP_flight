 /*************************************
 * stm32_math.c
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/


 /*Include*********************************/
#include "../inc/stm32_math.h"
 /*Definitions******************************/

 /*Functions********************************/
float stm32_sin(float a){
#include "../inc/tables/stm32_math_lookup_sin.h"

	//richtiges Intervall finden
	u16 intv_hi  = 0;
	u16 intv_low = 0;
	u16 startintv = (u16)(a/maxintv);
	//int startintv = 0;
	while(sinapp_x[startintv]<a){startintv++;}
	intv_hi  = startintv - 1;
	intv_low = startintv + 1 -1;
	//interpolieren
	float appsin = 0;
	float slope = (sinapp_sin[intv_hi]-sinapp_sin[intv_low]) / (sinapp_x[intv_hi]-sinapp_x[intv_low]);
	float dif  = (sinapp_x[intv_hi] - a);
	appsin = sinapp_sin[intv_low] + slope * dif;

	return appsin;
}
