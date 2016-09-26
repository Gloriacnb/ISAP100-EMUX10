/*
 * Task_led.cpp
 *
 *  Created on: 2013-3-19
 *      Author: Administrator
 */
#include "Task_define.h"
#include <rtl.h>
#include "ISAP100LED.h"
#include "Mid_RC7880A1App.h"
#include "Chip4E1Logic.h"
#include "Mid_SPI.h"
#include "DeviceLocal.h"
#include "UID.h"
#include "SDHGroup.h"
#include "CSTM.h"
#include "CNME1Port.h"
#include "CMainBoard.h"

OS_TID t_led;

__task void T_LED_SYS(void) {

	while( 1 ) {
		os_dly_wait(100);

		/* opt alm */
		if( do_vc4_alarm(0) == TRUE ) {
			led_sfpalm_a_on();
		}
 		else {
 			led_sfpalm_a_off();
 		}
 		if( do_vc4_alarm(1) == TRUE ) {
 			led_sfpalm_b_on();
 		}
 		else {
 			led_sfpalm_b_off();
 		}

 		/* opt los */
		STVersion v;
		DeviceLocal::instance().GetDeviceAttributeObject().GetVersion(ver_pcb, v);
 		if( v.uiVerNum != CDeviceAttribute::ver_num_V10 ) {
 			ST_SDH_STM info = {100, 0};
 			uint32 uid = UID::makeUID(&info);
 			uint8 en = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(uid)->getEnable();
			if( opt_is_los(0) && en != 0 ) {
				turn_led_sfplos_a(LED_ON);
			}
			else {
				turn_led_sfplos_a(LED_OFF);
			}

			info.stm = 1;
			uid = UID::makeUID(&info);
			en = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(uid)->getEnable();

			if( opt_is_los(1) && en != 0 ) {
				turn_led_sfplos_b(LED_ON);
			}
			else {
				turn_led_sfplos_b(LED_OFF);
			}
		}

 		/* led maj and min */
 		int E1_MAJ = 0;
 		int E1_MIN = 0;

		for( int slot = 0; slot < 4; slot++ ) {
			uint8 type;
			ExtCPLDRegReadByte(slot*4, 0, &type);
			if( type != 0x50 ) {
				continue;
			}
			for( int e1 = 0; e1 < 4; e1++ ) {
				if( do_E1_alm_wrk(slot, e1) == TRUE ) {
					led_e1wrk_on(slot, e1);
				}
				else {
					++E1_MAJ;
					led_e1wrk_off(slot, e1);
				}
				if( do_E1_alm_ais(slot, e1) == TRUE ) {
					led_e1ais_on(slot, e1);
					++E1_MIN;
				}
				else {
					led_e1ais_off(slot, e1);
				}
			}
		}

		/*NmPortE1*/
		CNME1Port* port = DeviceLocal::instance().getMainBoard()->getNmPort(0);
		if( port ) {
			if( port->ifE1Alarm(FE1_LOS) ) {
				led_upe1wrk_a_off();
			}
			else {
				led_upe1wrk_a_on();
			}

			if( port->ifE1Alarm(FE1_AIS) || port->ifE1Alarm(FE1_LOF) || port->ifE1Alarm(FE1_LOS) ) {
				led_upe1alm_a_on();
				++E1_MAJ;
			}
			else {
				led_upe1alm_a_off();
			}
		}
		port = DeviceLocal::instance().getMainBoard()->getNmPort(1);
		if( port ) {
			if( port->ifE1Alarm(FE1_LOS) ) {
				led_upe1wrk_b_off();
			}
			else {
				led_upe1wrk_b_on();
			}

			if( port->ifE1Alarm(FE1_AIS) || port->ifE1Alarm(FE1_LOF)  || port->ifE1Alarm(FE1_LOS) ) {
				++E1_MAJ;
				led_upe1alm_b_on();
			}
			else {
				led_upe1alm_b_off();
			}
		}


		if( (do_vc4_alarm(0) == TRUE) || (opt_is_los(0) == 1) ||
			(do_vc4_alarm(1) == TRUE) || (opt_is_los(1) == 1) ||
			(E1_MAJ != 0) ) {

				led_maj_on();

		}
		else {
				led_maj_off();
		}
		if( E1_MIN != 0 ) {
			led_min_on();
		}
		else {
			led_min_off();
		}

	}

}




