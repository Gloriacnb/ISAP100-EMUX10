/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			ISAP100LED.cpp
** File path:			/ISAP100_Mainsoft/Src/EZSoft/ISAP100board/ISAP100LED.cpp
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
#include "ISAP100LED.h"
#include "lpc32xx_gpio_driver.h"
//#include "Mid_Timer.h"
#include <rtl.h>


typedef void (*pfun_led)(void);


pfun_led led_on[10] = { 	led_run_on,
						led_sta_on,
						led_maj_on,
						led_min_on,
						led_upe1wrk_a_on,
						led_upe1alm_a_on,
						led_upe1wrk_b_on,
						led_upe1alm_b_on,
						led_sfpalm_a_on,
						led_sfpalm_b_on};

pfun_led led_off[10] = { led_run_off,
						led_sta_off,
						led_maj_off,
						led_min_off,
						led_upe1wrk_a_off,
						led_upe1alm_a_off,
						led_upe1wrk_b_off,
						led_upe1alm_b_off,
						led_sfpalm_a_off,
						led_sfpalm_b_off};

#define LED_NUM		( sizeof(led_on) / sizeof(led_on[0]) )

void TurnOffAllLed(void) {
	pfun_led* p = led_off;
	for( int i = 0; i < LED_NUM; i++ ) {
		(*p)();
		++p;
	}
}

void TurnOnAllLed(void) {
	pfun_led* p = led_on;
	for( int i = 0; i < LED_NUM; i++ ) {
		(*p)();
		++p;
	}
}

//void FlashAllLedOnebyone(void) {
//	pfun_led* pon = led_on;
//	pfun_led* poff = led_off;
//
//	for( int i = 0; i < LED_NUM; i++ ) {
//		(*pon[i])();
//	}
//}


void InitLEDModule(void) {
	TurnOnAllLed();
	os_dly_wait(200);
	TurnOffAllLed();
}



void LEDRunToggle(uint32 on) {
	  uint32 set, clr;

	  if (on == FALSE) {
	    set = 0;
	    clr = P3_GPO2_MAT10;
	  }
	  else {
	    set = P3_GPO2_MAT10;
	    clr = 0;
	  }

	  /* Set RUN on GPO_O2 */
	  gpio_set_gpo_state(set, clr);
}

void LEDToggle(uint32 on, uint32 pin) {

	  uint32 set, clr;

	  if (on == FALSE) {
	    set = 0;
	    clr = (1<<pin);
	  }
	  else {
	    set = (1<<pin);
	    clr = 0;
	  }

	  /* Set RUN on GPO_21 */
	  gpio_set_gpo_state(set, clr);
}

#define DEF_PIN_RUN		2
#define DEF_PIN_STA		8
#define DEF_PIN_MAJ		9
#define DEF_PIN_MIN		23
#define DEF_PIN_SFP_ALM1	21
#define DEF_PIN_SFP_ALM2	12
#define DEF_PIN_SFP_LOS1	3
#define DEF_PIN_SFP_LOS2	5
#define DEF_PIN_UPE1_WRK1	7
#define DEF_PIN_UPE1_ALM1	6
#define DEF_PIN_UPE1_WRK2	13
#define DEF_PIN_UPE1_ALM2	15





void led_run_on(void) {
	LEDToggle(LED_ON, DEF_PIN_RUN);
}

void led_run_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_RUN);
}

void led_sfpalm_a_on(void) {
	LEDToggle(LED_ON, DEF_PIN_SFP_ALM1);
}
void led_sfpalm_a_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_SFP_ALM1);
}

void led_sfpalm_b_on(void) {
	LEDToggle(LED_ON, DEF_PIN_SFP_ALM2);
}
void led_sfpalm_b_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_SFP_ALM2);
}

void turn_led_sfplos_a(bool opt) {
	LEDToggle(opt, DEF_PIN_SFP_LOS1);
}

void turn_led_sfplos_b(bool opt) {
	LEDToggle(opt, DEF_PIN_SFP_LOS2);
}

void led_sta_on(void) {
	LEDToggle(LED_ON, DEF_PIN_STA);
}
void led_sta_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_STA);
}

void led_maj_on(void) {
	LEDToggle(LED_ON, DEF_PIN_MAJ);
}
void led_maj_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_MAJ);
}

void led_min_on(void) {
	LEDToggle(LED_ON, DEF_PIN_MIN);
}
void led_min_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_MIN);
}

void led_upe1wrk_a_on(void) {
	LEDToggle(LED_ON, DEF_PIN_UPE1_WRK1);
}
void led_upe1wrk_a_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_UPE1_WRK1);
}

void led_upe1alm_a_on(void) {
	LEDToggle(LED_ON, DEF_PIN_UPE1_ALM1);
}
void led_upe1alm_a_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_UPE1_ALM1);
}

void led_upe1wrk_b_on(void) {
	LEDToggle(LED_ON, DEF_PIN_UPE1_WRK2);
}
void led_upe1wrk_b_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_UPE1_WRK2);
}

void led_upe1alm_b_on(void) {
	LEDToggle(LED_ON, DEF_PIN_UPE1_ALM2);
}
void led_upe1alm_b_off(void) {
	LEDToggle(LED_OFF, DEF_PIN_UPE1_ALM2);
}
