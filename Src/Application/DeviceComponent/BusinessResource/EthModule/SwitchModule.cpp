/*
 * SwitchModule.cpp
 *
 *  Created on: 2014-4-17
 *      Author: Administrator
 */

#include "SwitchModule.h"
#include "EthBoard.h"
#include "CSwitchBaseImpl.h"

SwitchModule* SwitchModule::obj;

SwitchModule::SwitchModule(EthBoard* b, Switch_Base_cfg_T* cfg, CMSSave* save) {
	obj = this;
	ConfigData = cfg;
	Board = b;
	storer = save;
	setSwitchMode(ConfigData->mode, false);
	setSwitchMTU(ConfigData->mtu, false);
}

SwitchModule::~SwitchModule() {
	// TODO Auto-generated destructor stub
}

bool SwitchModule::setSwitchMode(uint8 mode, bool save) {
	for (int i = 0; i < 2; ++i) {
		CSwitchBaseImpl* chip = Board->getSwitch(i);
		switch( mode ) {
		case 0:
			chip->InitializeFullSwitchMode();
			break;
		case 1:
			chip->InitializeAggregationMode();
			break;
		case 2:
			chip->InitializeTagAwareMode();
			break;
		default:
			return false;
		}

	}
	if( save ) {
		ConfigData->mode = mode;
		return storer->SaveData();
	}
	return true;
}

bool SwitchModule::setSwitchMTU(uint8 m, bool save) {
	CSwitchBaseImpl* chip = Board->getSwitch(0);
	chip->SetSwitchMaxPacketLength(m);
	if( save ) {
		ConfigData->mtu = m;
		return storer->SaveData();
	}
	return true;
}
