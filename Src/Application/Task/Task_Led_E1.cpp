/*
 * Task_Led_E1.cpp
 *
 *  Created on: 2013-3-19
 *      Author: Administrator
 */

#include "Task_define.h"
#include <rtl.h>
#include "ISAP100LED.h"
//#include "Mid_RC7880A1App.h"
#include "ChipSlotLogic.h"

OS_TID t_led_upE1;


__task void T_LED_UP_E1(void) {

	while( 1 ) {
		os_dly_wait(100);


		if( do_upe1_alarm_ais(2) == true ) {
			led_upe1alm_a_on();
		}
		else {
			led_upe1alm_a_off();
		}

		if( do_upe1_alarm_wrk(2) == true ) {
			led_upe1wrk_a_on();
			led_maj_off();
		}
		else {
			led_upe1wrk_a_off();
			led_maj_on();
		}


		if( do_upe1_alarm_ais(3) == true ) {
			led_upe1alm_b_on();
		}
		else {
			led_upe1alm_b_off();
		}

		if( do_upe1_alarm_wrk(3) == true ) {
			led_maj_off();
			led_upe1wrk_b_on();
		}
		else {
			led_maj_on();
			led_upe1wrk_b_off();
		}


	}

}




