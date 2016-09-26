/*
 * EthBoard.cpp
 *
 *  Created on: 2014-4-8
 *      Author: Administrator
 */

#include "EthBoard.h"
#include "RTL8306ESwitch.h"
#include "ChipGlulogic.h"
#include "UID.h"
#include <string.h>
#include "SwitchModule.h"
#include "SysError.h"

static uint8 chipsn[] = {0,0,1,1,0,0,1,1,0,0,1,1};
static uint8 portSn[] = {0,1,0,1,2,3,2,3,4,5,4,5};

EthBoard::EthBoard(int portNum, bool ifsw) {

	storeInfo.BlockFirst = MB_ETH_Config_Block_Start;
	storeInfo.BufAddr = (uint32)&storeData;
	storeInfo.ByteNums = sizeof(storeData);
	FlashDriver.setInfo(storeInfo);

	if( !FlashDriver.ReadData() ) {
		//restore default data

		RestoreDefauleConfig();
	}

	ChipSwitch = new RTL8306ESwitch();

	//µÈ´ýÇ°µ¼Âë
	getSwitch(1);
	for (int i = 0; i < 10000; ++i) {

	}
	getSwitch(0);
	for (int i = 0; i < 10000; ++i) {

	}

	for (int i = 0; i < 2; ++i) {
		CSwitchBaseImpl* driver = getSwitch(i);
		uint32 id = 0;
		driver->GetSwitchChipID(&id);
		if( id != 0x001C ) {
			throw SysError("!!!RTL8306E not exist!");
		}
		driver->InitializeSwitch(1);
	}

	if( ifsw ) {
		new SwitchModule(this, &(storeData.sw), &FlashDriver);
	}
	else {
		for (int i = 0; i < 2; ++i) {
			CSwitchBaseImpl* driver = getSwitch(i);
			driver->InitializeAggregationMode();
		}
	}

	ST_FE info = {100, 0};
	for( int i = 0; i < portNum; i++ ) {
		info.port = i;
		uint32 uid = UID::makeUID(&info);
		eport[i] = new PortEth(uid, chipsn[i], portSn[i], &storeData.port[i], &FlashDriver, this);
	}

}

EthBoard::~EthBoard() {
	// TODO Auto-generated destructor stub
}

CSwitchBaseImpl* EthBoard::getSwitch(int sn) {
	glulogic->I2C_SEL = sn;
	return ChipSwitch;
}


void EthBoard::RestoreDefauleConfig(void) {
	memset( &storeData, 0, sizeof(storeData));
	for( int i = 0; i < 8; i++ ) {
		storeData.port[i].autoAN = 1;
		storeData.port[i].enable = 1;
		storeData.port[i].linkType = 1;
		storeData.port[i].speed = 1;
		storeData.port[i].duplex = 1;
	}
	FlashDriver.SaveData();

}
