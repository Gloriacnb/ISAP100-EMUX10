/*
 * Chip2BDLogic.cpp
 *
 *  Created on: 2013-8-1
 *      Author: Administrator
 */

#include "Chip2BDLogic.h"
#include "Mid_SPI.h"
#include <rtl.h>

uint16 get2BDChipVersion(uint8 slot) {
	uint8 ver = 0;
	ExtCPLDRegReadByte(4*slot, Chip_2BD_VER, &ver);
	return ver;
}

/*
 * chip  0 reset chip1
 *       1 reset chip2
 *       2 reset all
 */
void resetMC145572(uint8 slot, uint8 chip) {
	uint8 temp = 3;
	ExtCPLDRegReadByte(4*slot, MC145572_reset, &temp);
	temp &= ~(1 << chip);

	ExtCPLDRegWriteByte(4*slot, MC145572_reset, temp);
	os_dly_wait(1);
	ExtCPLDRegWriteByte(4*slot, MC145572_reset, 3);
}


void selectNTLT(uint8 slot, uint8 chip, uint8 mode) {
	if( chip == 0 ) {
		ExtCPLDRegWriteByte(4*slot, NTLT_SEL_0, mode);
	}
	else {
		ExtCPLDRegWriteByte(4*slot, NTLT_SEL_1, mode);
	}
	setModeLED(slot, chip, mode);
}

/*
 * s(0) on
 * s(1) off
 */
void setLinkLED(uint8 slot, uint8 chip, uint8 s) {
	if( chip == 0 ) {
		uint8 temp;
		ExtCPLDRegReadByte(4*slot, LED_2BD_0, &temp);
		temp &= ~(1 << 0);
		temp |= (s << 0);
		ExtCPLDRegWriteByte(4*slot, LED_2BD_0, temp);
	}
	else {
		uint8 temp;
		ExtCPLDRegReadByte(4*slot, LED_2BD_1, &temp);
		temp &= ~(1 << 0);
		temp |= (s << 0);
		ExtCPLDRegWriteByte(4*slot, LED_2BD_1, temp);
	}
}
void setModeLED(uint8 slot, uint8 chip, uint8 mode) {
	if( chip == 0 ) {
		uint8 temp;
		ExtCPLDRegReadByte(4*slot, LED_2BD_0, &temp);
		temp &= ~(1 << 1);
		temp |= (mode << 1);
		ExtCPLDRegWriteByte(4*slot, LED_2BD_0, temp);
	}
	else {
		uint8 temp;
		ExtCPLDRegReadByte(4*slot, LED_2BD_1, &temp);
		temp &= ~(1 << 1);
		temp |= (mode << 1);
		ExtCPLDRegWriteByte(4*slot, LED_2BD_1, temp);
	}
}
