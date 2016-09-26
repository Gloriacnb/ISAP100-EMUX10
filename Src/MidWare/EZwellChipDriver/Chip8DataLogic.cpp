/*
 * Chip8DataLogic.cpp
 *
 *  Created on: 2013-6-17
 *      Author: Administrator
 */

#include "Chip8DataLogic.h"
#include "Mid_SPI.h"

static uint8 mapPortSpi[] = {1, 1, 1, 1, 2, 2, 2, 2 };
static uint8 bitMapPort_422[] = {3, 2, 1, 0, 3, 2, 1, 0};
static uint8 bitMapPort_232[] = {7, 6, 5, 4, 7, 6, 5, 4};

static uint8 getSpiCh(uint8 slot, uint8 port) {
	return (slot<<2)+mapPortSpi[port];
};

uint8 getDPtype(uint8 slot, uint8 port) {
	uint8 type = 0;
	uint8 spich = getSpiCh(slot, port);
	ExtCPLDRegReadByte(spich, Chip_8DT_ChType, &type);
	return type;
}


uint8 get8DataVersion(uint8 slot) {
	uint8 spi_ch = slot << 2;
	uint8 ver = 0;
	ExtCPLDRegReadByte(spi_ch, Chip_8DT_VER, &ver);
	return ver;
}


void setPortEnable(uint8 slot, uint8 port, uint8 en) {
	uint8 spich = getSpiCh(slot, port);
	uint8 type = getDPtype(slot, port);
	if( type == type_RS422 || type == type_RS485 ) {
		ExtCPLDRegWriteBit(spich, Chip_8DT_ChEnable, bitMapPort_422[port], en);
	}
	else {
		ExtCPLDRegWriteBit(spich, Chip_8DT_ChEnable, bitMapPort_232[port], en);
	}
}


void setPortLoopOut(uint8 slot, uint8 port, uint8 loop) {
	uint8 spich = getSpiCh(slot, port);
	uint8 type = getDPtype(slot, port);
	if( type == type_RS422 || type == type_RS485 ) {
		ExtCPLDRegWriteBit(spich, Chip_8DT_LoopOut, bitMapPort_422[port], loop);
	}
	else {
		ExtCPLDRegWriteBit(spich, Chip_8DT_LoopOut, bitMapPort_232[port], loop);
	}
}
void setPortLoopIn(uint8 slot, uint8 port, uint8 loop) {
	uint8 spich = getSpiCh(slot, port);
	uint8 type = getDPtype(slot, port);
	if( type == type_RS422 || type == type_RS485 ) {
		ExtCPLDRegWriteBit(spich, Chip_8DT_LoopIn, bitMapPort_422[port], loop);
	}
	else {
		ExtCPLDRegWriteBit(spich, Chip_8DT_LoopIn, bitMapPort_232[port], loop);
	}
}
