/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			ISAP100LED.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/include/ISAP100LED.h
** Created by:          Administrator
** Created date:        2012-12-6
** Version:             V0.1
** Descriptions:        
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:				
** Descriptions:        
**
** Rechecked by:        
***********************************************************************************************************************/


#ifndef ISAP100LED_H_
#define ISAP100LED_H_
#include "EZ_types.h"


#define LED_ON	FALSE
#define LED_OFF TRUE

void InitLEDModule(void);

void led_run_on(void);
void led_run_off(void);

void led_sfpalm_a_on(void);
void led_sfpalm_a_off(void);

void led_sfpalm_b_on(void);
void led_sfpalm_b_off(void);

void led_sta_on(void);
void led_sta_off(void);

void led_maj_on(void);
void led_maj_off(void);

void led_min_on(void);
void led_min_off(void);

void led_upe1wrk_a_on(void);
void led_upe1wrk_a_off(void);

void led_upe1alm_a_on(void);
void led_upe1alm_a_off(void);

void led_upe1wrk_b_on(void);
void led_upe1wrk_b_off(void);

void led_upe1alm_b_on(void);
void led_upe1alm_b_off(void);

void turn_led_sfplos_a(bool opt);
void turn_led_sfplos_b(bool opt);


#endif /* ISAP100LED_H_ */
