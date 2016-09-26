/*
 * Chip4E1Logic.c
 *
 *  Created on: 2012-12-26
 *      Author: Administrator
 */

#include "Mid_SPI.h"
#include "Chip4E1Logic.h"

#define GetCPLDChannelBySlot(slot)  ((slot) << 2)

uint32 InitExtChip4E1(uint8 slot, Card_4E1_Config_T* cfgData) {

	//ÃðµôËùÓÐE1 LED
	ExtCPLDRegWriteByte(GetCPLDChannelBySlot(slot), E1_LED, 0xff);
	ExtCPLDRegWriteByte(GetCPLDChannelBySlot(slot), PWM_PARA, cfgData->pwm);

	return TRUE;

}

void led_e1wrk_on(uint8 slot, uint8 e1) {
	uint8 led = 0;
	ExtCPLDRegReadByte(4 * slot, E1_LED, &led);
	led &= ~(1 << (e1 + 4));
	ExtCPLDRegWriteByte(4 * slot, E1_LED, led);
}

void led_e1wrk_off(uint8 slot, uint8 e1) {
	uint8 led = 0;
	ExtCPLDRegReadByte(4 * slot, E1_LED, &led);
	led |= (1 << (e1 + 4));
	ExtCPLDRegWriteByte(4 * slot, E1_LED, led);

}

void led_e1ais_on(uint8 slot, uint8 e1) {
	uint8 led = 0;
	ExtCPLDRegReadByte(4 * slot, E1_LED, &led);
	led &= ~(1 << (e1));
	ExtCPLDRegWriteByte(4 * slot, E1_LED, led);
}

void led_e1ais_off(uint8 slot, uint8 e1) {
	uint8 led = 0;
	ExtCPLDRegReadByte(4 * slot, E1_LED, &led);
	led |= (1 << (e1));
	ExtCPLDRegWriteByte(4 * slot, E1_LED, led);
}

uint16 get4E1ChipVersion(uint8 slot) {
	uint8 ver = 0;
	ExtCPLDRegReadByte(4 * slot, Chip_4E1_VER, &ver);
	return ver;
}
