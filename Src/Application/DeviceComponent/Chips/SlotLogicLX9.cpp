/*
 * SlotLogicLX9.cpp
 *
 *  Created on: 2013-3-16
 *      Author: Administrator
 */

#include "SlotLogicLX9.h"

#include <fstream>
#include <cassert>
#include <sstream>
#include "ChipSlotLogic.h"
#include "TerminalUart.h"
#include "ChipOptLogic.h"
#include "SysError.h"

using namespace std;

static uint8 fileBuf[0x053300];

SlotLogic_LX9::SlotLogic_LX9() {
	// TODO Auto-generated constructor stub
	saveinfo.BlockFirst = 200;
	saveinfo.ByteNums = 0x053300;
	saveinfo.SecsUsed = 167;
	saveinfo.BufAddr = (uint32)fileBuf;
	savefile.setInfo(saveinfo);
	savefile.ReadData(0,0);
	memcpy(fileName, "lx9.bit", 8);
}



SlotLogic_LX9::~SlotLogic_LX9() {
	// TODO Auto-generated destructor stub
//	delete [] (uint8*)saveinfo.BufAddr;
//	saveinfo.BufAddr = 0;
}


SlotLogic_LX9::SlotLogic_LX9(uint8* name, uint8 nlen) {
	// TODO Auto-generated constructor stub
	saveinfo.BlockFirst = 200;
	saveinfo.ByteNums = 0x053300;
	saveinfo.SecsUsed = 167;
	saveinfo.BufAddr = (uint32)fileBuf;
	savefile.setInfo(saveinfo);
	savefile.ReadData(0,0);
	if( nlen < 20 ) {
		memcpy(fileName, name, nlen);
		fileName[nlen] = 0;
	}
	else {
		throw;
	}
}

void SlotLogic_LX9::OpenSlotLogic(void) {
	RST_MODE_E mode = Rst_Mode();
	if( mode == up_main ) {
		return;
	}
	uint32 state = slotlogic_open(&saveinfo);
	if( state != 0 ) {
		throw SysError("!!!SlotLogic chip init failed!");
	}
}


bool SlotLogic_LX9::UpDataLx9(uint8* name, uint8 nlen) {
	if( nlen > 12 ) {
		return false;
	}
	memcpy(fileName, name, nlen);
	fileName[nlen] = 0;
	return UpDataLx9();
}


bool SlotLogic_LX9::UpDataLx9(void) {
	FILE* inf = fopen((const char*)fileName, "rb");

	if( inf != NULL ) {
		fread((char*)saveinfo.BufAddr, 1, saveinfo.ByteNums, inf);
		savefile.SaveData(0);
		fclose(inf);
		return true;
	}
	return false;

}


//extern "C" int updatafpga(uint8* s, uint8 len);

int updatafpga(uint8* s, uint8 len) {
	SlotLogic_LX9 lx9(s, len);
	if( lx9.UpDataLx9() ) {
		return 1;
	}
	return -1;

}
