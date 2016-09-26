/*
 * MidMC145572.cpp
 *
 *  Created on: 2013-7-30
 *      Author: Administrator
 */

#include "MidMC145572.h"
#include "Mid_SPI.h"
#include "ChipGluLogic.h"
#include <rtl.h>
#include "Chip2BDLogic.h"

MidMC145572::MidMC145572(uint8 slot, uint8 sn) {
	// TODO Auto-generated constructor stub
	slt = slot;
	cid = sn;
	spiCH = (slot << 2) | (sn+1);
	initChip(true);
}

MidMC145572::~MidMC145572() {
	// TODO Auto-generated destructor stub
}


void MidMC145572::softReset(void) {
	writeNibbleReg(NR0, 0x08);
	os_dly_wait(1);
	writeNibbleReg(NR0, 0x00);
}

void MidMC145572::initChip(bool cold) {

	if( cold ) {
		resetMC145572(slt, cid);
	}
	//IDL2 to short frame, 8bit, 2048
	writeByteReg(BR7,5); //bit2 speed 2048, bit0 8bit
	uint8 temp = readOverlayReg(OR7);
	temp &= ~(1<<3);
	writeOverlayReg(OR7, temp); // short frame
}

int MidMC145572::setMode(uint8 mode) {
	selectNTLT(slt, cid, mode);
	return 1;
}
int MidMC145572::setEnable(uint8 en) {
	uint8 temp = readNibbleReg(NR0);
	if( en == 0 ) {
		temp |= (1<<2);
	}
	else {
		temp &= ~(1<<2);
	}
	return writeNibbleReg(NR0, temp);
}
int MidMC145572::setLoopIn(uint8 loop) {
	if( loop == 0 ) {
		writeOverlayReg(OR8, 0);
		writeOverlayReg(OR9, 0);
	}
	else {
		writeOverlayReg(OR8, 0x22);
		writeOverlayReg(OR9, 0x20);
	}
	return 1;
}
int MidMC145572::setLoopOut(uint8 loop) {
	uint8 temp = readByteReg(BR6);
	temp &= ~(1 << 5);
	temp |= (loop << 5);
	writeByteReg(BR6, temp);
	return 1;
}



int MidMC145572::readNibbleReg(uint8 addr) {

	os_mut_wait(mut_spi, 0xffff);
	glulogic->SPI_SEL = spiCH | 0x03;	//patch
	glulogic->SPI_SEL = spiCH;
	uint16 val = SpiMCRead(addr, 4, 4);
	glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
	os_mut_release(mut_spi);
	return val;
}
int MidMC145572::readByteReg(uint8 addr) {
	addr += 0x70;
	os_mut_wait(mut_spi, 0xffff);
	glulogic->SPI_SEL = spiCH | 0x03;	//patch
	glulogic->SPI_SEL = spiCH;
	uint16 val = SpiMCRead(addr, 8, 8);
	glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
	os_mut_release(mut_spi);
	return val;

}
int MidMC145572::readOverlayReg(uint8 addr) {
	writeByteReg(10, 7); //ÇÐ»»µ½overlay register
	int rtn = readByteReg(addr);
	writeByteReg(10, 0);
	return rtn;
}

int MidMC145572::readR6Reg(void) {
	os_mut_wait(mut_spi, 0xffff);
	glulogic->SPI_SEL = spiCH | 0x03;	//patch
	glulogic->SPI_SEL = spiCH;
	uint16 val = SpiMCRead(0x76, 8, 16);
	glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
	os_mut_release(mut_spi);
	return val;
}


int MidMC145572::writeNibbleReg(uint8 addr, uint8 data) {
	os_mut_wait(mut_spi, 0xffff);
	glulogic->SPI_SEL = spiCH | 0x03;	//patch
	glulogic->SPI_SEL = spiCH;
	int rtn = SpiMCWrite(addr, data, 4, 4);
	glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
	os_mut_release(mut_spi);
	return rtn;
}
int MidMC145572::writeByteReg(uint8 addr, uint8 data) {
	addr += 0x70;
	os_mut_wait(mut_spi, 0xffff);
	glulogic->SPI_SEL = spiCH | 0x03;	//patch
	glulogic->SPI_SEL = spiCH;
	int rtn = SpiMCWrite(addr, data, 8, 8);
	glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
	os_mut_release(mut_spi);
	return rtn;

}
int MidMC145572::writeOverlayReg(uint8 addr, uint8 data) {
	writeByteReg(10, 7); //ÇÐ»»µ½overlay register
	int rtn = writeByteReg(addr, data);
	writeByteReg(10, 0);
	return rtn;

}

int MidMC145572::writeR6Reg(uint16 data) {
	os_mut_wait(mut_spi, 0xffff);
	glulogic->SPI_SEL = spiCH | 0x03;	//patch
	glulogic->SPI_SEL = spiCH;
	int rtn = SpiMCWrite(0x76, data, 8, 16);
	glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
	os_mut_release(mut_spi);
	return rtn;
}
