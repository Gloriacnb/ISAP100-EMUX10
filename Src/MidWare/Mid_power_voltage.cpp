/*
 * Mid_power_voltage.cpp
 *
 *  Created on: 2013-11-2
 *      Author: Administrator
 */

#include "Mid_power_voltage.h"
#include "lpc32xx_gpio_driver.h"
#include "DeviceLocal.h"
#include "Mid_ADC.h"

#define Power1JudgePin P3_IN_STATE_U1_RX
#define Power2JudgePin P3_IN_STATE_U3_RX

void powerSlotInit(void) {
	ADC_INIT();
}

bool PowerCardExist(uint8 sn) {
	STVersion v;
	DeviceLocal::instance().GetDeviceAttributeObject().GetVersion(ver_pcb, v);
	bool rtn = false;
	if (v.uiVerNum != CDeviceAttribute::ver_num_V10) {
		uint16 vol = 0;
		if (sn == 4) {
			readADC();
			vol = getADCData(0);
		} else {
			vol = getADCData(1);
		}
		rtn = vol > 0x200;
	} else {
		uint32 position = 0;
		if (sn == 4) {
			position = Power1JudgePin;
		} else {
			position = Power2JudgePin;
		}
		uint32 bak = GPIO->p3_inp_state;
		uint32 comp = bak & position;
		rtn = (comp == position);
	}
	return rtn;
}
;
