/*
 * CDataPort.cpp
 *
 *  Created on: 2013-6-14
 *      Author: Administrator
 */

#include "CDataPort.h"
#include "CPPTools.h"
#include "UID.h"
#include "CTSChannel.h"
#include "Chip8DataLogic.h"
#include <string.h>
#include "CMSSave.h"

std::map<uint32, CDataPort*> CDataPort::Group;

CDataPort::CDataPort(uint32 userIndex, uint8 psn, Data_Port_Config_T* cfg, CMSSave* driver) : RealPortBase(userIndex) {
	uid = userIndex;
	LinkChannel = CTSChannel::getTSChannelByUid(uid);
	if( LinkChannel ) {
		LinkChannel->setActive(1);
	}
	configData = cfg;

	cfgDriver = driver;

	portSn = psn;

	name = "slot-" + CPPTools::number2string(uid>>24) + "-DataPort-" + CPPTools::number2string(portSn+1);

	Group.insert(std::pair<uint32, CDataPort*>(uid, this));

//	portType = getPortType;
}

CDataPort::~CDataPort() {
	LinkChannel->setActive(0);
	Group.erase(uid);
}

uint8 CDataPort::getEnable(void) {
	return configData->enable;
}

int CDataPort::setEnable(uint8 en) {
	setPortEnable((uid >> 24)-1, portSn, en);
	configData->enable = en;
	cfgDriver->SaveData();
	return 0x5A;
}

char* CDataPort::getDesc(uint32* len) {
	*len = configData->desclen;
	return configData->desc;
}
int CDataPort::setDesc(const char* s, uint32 len) {
	configData->desclen = len;
	memcpy(configData->desc, s, len);
	cfgDriver->SaveData();
	return 1;
}


uint8 CDataPort::getPortType(void) {
	uint8 slot = (uid >> 24)-1;
	return getDPtype(slot, portSn);
}

int CDataPort::setLoop(const int type) {
	uint8 slot = (uid >> 24)-1;
	switch( type ) {
	case dev_and_line_loop:
		setPortLoopOut(slot, portSn, 1);
		setPortLoopIn(slot, portSn, 1);
		break;
	case line_loop:
		setPortLoopOut(slot, portSn, 1);
		setPortLoopIn(slot, portSn, 0);
		break;
	case dev_loop:
		setPortLoopOut(slot, portSn, 0);
		setPortLoopIn(slot, portSn, 1);
		break;
	case no_loop:
		setPortLoopOut(slot, portSn, 0);
		setPortLoopIn(slot, portSn, 0);
		break;
	default:
		return -1;
	}
	return 0x5A;
}
