/*
 * Chip8VFLogic.c
 *
 *  Created on: 2012-12-26
 *      Author: Administrator
 */

#include "Chip8VFLogic.h"
#include "Mid_SPI.h"
#include "Pcm821054.h"

extern uint8 GetVoiceChannelType(int chipID, int channelID);

uint32 InitExt8VFChip(uint8 slot, Card_8VF_Config_T* cfg) {
	int i;
	uint8 spi_ch = slot << 2;
	uint8 hotValue = 0;
	for( i = 0; i < 8; i++ ) {
		hotValue |= (cfg->port[i].work_mode >> i);
	}
	ExtCPLDRegWriteByte( spi_ch, Hot_Line_Ctrl, hotValue );
	for( i = 0; i < 8; i++ ) {
		if( i < 4 ) {
			if( stVC[i+1].Type == 1 ) {
				ExtCPLDRegWriteByte(spi_ch, DEF_TSch_Type_Base+i, 0);
			}
			else {
				ExtCPLDRegWriteByte(spi_ch, DEF_TSch_Type_Base+i, stVC[i+1].Type-2);
			}
		}
		else {
			if( stVC[i+13].Type == 1 ) {
				ExtCPLDRegWriteByte(spi_ch, DEF_TSch_Type_Base+i, 0);
			}
			else {
				ExtCPLDRegWriteByte(spi_ch, DEF_TSch_Type_Base+i, stVC[i+13].Type-2);
			}
		}

	}
	return TRUE;

}


uint8 getVFType(uint8 slot, uint8 port) {
	uint8 chipID = ((slot) << 2) + (port >> 2) + 1;
	uint8 channelID = (port & 3) + 1;
	return GetVoiceChannelType(chipID, channelID);
}


uint8 get8VFVersion(uint8 slot) {
	uint8 spi_ch = slot << 2;
	uint8 ver = 0;
	ExtCPLDRegReadByte(spi_ch, Chip_8VF_VER, &ver);
	return ver;
}


uint8 setHotLine(uint8 slot, uint8 port, uint8 en) {
	uint8 spi_ch = slot << 2;
	uint8 val = 0;
	ExtCPLDRegReadByte(spi_ch, Hot_Line_Ctrl, &val);
	if( en != 0 ) {
		val |= (1 << port);
	}
	else {
		val &= ~(1 << port);
	}

	ExtCPLDRegWriteByte(spi_ch, Hot_Line_Ctrl, val);
	return 0x5A;
}

uint8 getHookState(uint8 slot, uint8 port) {
	uint8 spi_ch = slot << 2;
	uint8 val = 0;
	ExtCPLDRegReadByte(spi_ch, Hook_State, &val);
	return (val >> port) & 1;
}

uint8 setRC(uint8 slot, uint8 port, uint8 rc) {
	uint8 spi_ch = slot << 2;
	uint8 val = 0;
	ExtCPLDRegReadByte(spi_ch, RC_Ctrl, &val);
	if( rc != 0 ) {
		val |= (1 << port);
	}
	else {
		val &= ~(1 << port);
	}

	ExtCPLDRegWriteByte(spi_ch, RC_Ctrl, val);
	return 0x5A;
}

uint8 setMTMode(uint8 slot, uint8 port, uint8 mode) {
	uint8 spi_ch = slot << 2;
	uint8 val = 0;
	ExtCPLDRegReadByte(spi_ch, MT_MODE, &val);
	val &= ~(1<<port);
	val |= (mode << port);
	ExtCPLDRegWriteByte(spi_ch, MT_MODE, val);
	return 0x5A;

}

uint8 setPolarDisable(uint8 slot, uint8 port, uint8 dis) {
	uint8 spi_ch = slot << 2;
	uint8 val = 0;
	ExtCPLDRegReadByte(spi_ch, Polar_DIS, &val);
	val &= ~(1<<port);
	val |= (dis << port);
	ExtCPLDRegWriteByte(spi_ch, Polar_DIS, val);
	return 0x5A;
}
