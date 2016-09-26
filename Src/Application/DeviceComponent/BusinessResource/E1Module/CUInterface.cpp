/*
 * CUInterface.cpp
 *
 *  Created on: 2013-7-29
 *      Author: Administrator
 */

#include "CUInterface.h"
#include <sstream>
#include "CE1Channel.h"
#include "CMSSave.h"
#include <string.h>
#include "MidMC145572.h"
#include "Chip2BDLogic.h"
#include <stdio.h>
#include "Task_define.h"

std::map<uint32, CUInterface*> CUInterface::UIF_group;
std::map<uint32, CUInterface*>::iterator CUInterface::it;

//OS_TID task_UActive = 0;

CUInterface::CUInterface(int sn, uint32 uid, UInterface_config_data* config, CMSSave* save,  MidMC145572* dri) : RealPortBase(uid) {
	// TODO Auto-generated constructor stub
	portSn = sn;
	std::ostringstream os;
	os << "Slot-" << (uid>>24) << "-U-" << sn + 1;
	name = os.str();
	configData = config;
	storer = save;
	driver = dri;

	UIF_group.insert( std::pair<uint32, CUInterface*>(uid, this) );

	linkChannel = CE1Channel::getE1(uid);
	linkChannel->setActive(true);

//	Actived = false;
	stoped = false;
	setMode(config->mode, false);

	task_UActive = os_tsk_create_ex(T_UActive, P_UI_Active, this);

}

CUInterface::~CUInterface() {
	// TODO Auto-generated destructor stub
	linkChannel->setActive(false);
	UIF_group.erase(getUID());
	os_tsk_delete(task_UActive);
	delete driver;
}

int CUInterface::setLoop(const int type) {
	switch( type ) {
	case dev_and_line_loop:
		stoped = true;
		driver->setLoopIn(1);
		driver->setLoopOut(1);
		break;
	case line_loop:
		stoped = true;
		driver->setLoopOut(1);
		driver->setLoopIn(0);
		break;
	case dev_loop:
		stoped = true;
		driver->setLoopOut(0);
		driver->setLoopIn(1);
		break;
	case no_loop:
		stoped = false;
		driver->setLoopOut(0);
		driver->setLoopIn(0);
		break;
	default:
		return -1;
	}
	return 0x5A;
}
std::string& CUInterface::getName(void) {
	return name;
}
int CUInterface::getPortSpeed(void) {
	return -(64+64);
}


int CUInterface::setEnable(uint8 en) {
	//option MC175572
	if( driver->setEnable(en) < 0 ) {
		return -1;
	}
	configData->enable = en;
	if( storer->SaveData() ) {
		return 1;
	}
	return -1;

}
int CUInterface::setDescription(char* desc, uint8 len) {
	if( desc == 0 || strlen(desc) > 31 ) {
		return -1;
	}
	memcpy( configData->desc, desc, len);
	configData->dlen = len;
	return 1;
}

/*
 * 0 is LT/ 1 is NT
 */
int CUInterface::setMode(uint8 mode, bool save) {

	//option MC175572
	if( driver->setMode(mode) < 0 ) {
		return -1;
	}

	configData->mode = mode;
	if( save ) {
		if( storer->SaveData() ) {
			return 1;
		}
	}
	return -1;
}


void CUInterface::startActive() {
	uint8 temp = driver->readNibbleReg(NR2);
	temp |= 0x08;
	driver->writeNibbleReg(NR2, temp);
}

bool CUInterface::haveInterrupt() {
	uint8 temp = driver->readNibbleReg(NR3);
	if( temp != 0 ) {
		return true;
	}
	return false;
}

bool CUInterface::Actived() {
	return driver->readNibbleReg(NR1) == 0x0B;
}

bool CUInterface::activing() {
	return (driver->readNibbleReg(NR1) & 1) == 1;
}
bool CUInterface::activeError() {
	return ((driver->readNibbleReg(NR1) >> 2)& 1) == 1;
}


bool CUInterface::active(void) {
	if( Actived() || stoped ) {
		return true;
	}
	printf("\nStart active Slot-%d-U-Port%d\n", getUID()>>24, portSn);
	setLinkLED((getUID()>>24)-1,portSn,1);
	driver->softReset();
	driver->initChip();

	if( getMode() == 0 ) {
		initLT();
	}
	else {
		initNT();
	}
	if( !activing() ) {
		startActive();
	}
	uint32 startTime = os_time_get();
	while( (os_time_get() - startTime) < (16 * 100) ) {
		os_dly_wait(1);
		if( haveInterrupt() ) {
			MC_Active_Result_E rst;
			if( getMode() == 0 ) {
				rst = isrLT();
			}
			else {
				rst = isrNT();
			}
			if( rst == act_success ) {
				setLinkLED((getUID()>>24)-1,portSn,0);
				printf("\nActive Slot-%d-U-Port%d succeed!\n", getUID()>>24, portSn);
				return true;
			}
// 			else if( rst == act_failed ) {
// 				printf("\n!!!Active Slot-%d-U-Port%d failed!!!\n", getUID()>>24, portSn);
// 				return false;
// 			}
		}
	}
	printf("\n!!!Active Slot-%d-U-Port%d failed!!!\n", getUID()>>24, portSn);
	return false;
}


void CUInterface::initLT() {
	driver->writeByteReg(BR0, 0x7f);
	driver->writeByteReg(BR1, 0x7f);
	driver->writeByteReg(BR2, 0xf0);
	driver->writeByteReg(BR9, 0x8c);
	driver->writeOverlayReg(OR7, 1);
	driver->writeR6Reg(0x01ff);
	driver->writeNibbleReg(NR4, 0x0e);//enable eoc, M4, activation interrupts

}
void CUInterface::initNT() {
	driver->writeByteReg(BR0, 0x77);
	driver->writeByteReg(BR1, 0x7f);
	driver->writeByteReg(BR2, 0xf0);
	driver->writeByteReg(BR9, 0x1c);
	driver->writeOverlayReg(OR7, 1);
	driver->writeNibbleReg(NR4, 0x0a);//enable M4, activation interrupts
}

MC_Active_Result_E CUInterface::isrLT() {
	switch( getInterruptType() ) {
	case int_act: {
		if( activeError() ) {
			return act_failed;
		}
//		uint8 temp = driver->readNibbleReg(NR1);
//		if( temp == 0x0b ) {
//			return act_continue;
//		}
//		else if( temp == 4 ) {
//			driver->writeNibbleReg(NR4, 0); //disable interrupts
//			return act_failed;
//		}
	}
		break;
	case int_M4: {
		uint8 temp = driver->readByteReg(BR1);
		if( (temp >> 7) & 1 == 1 ) {
			driver->writeByteReg(BR4, 0);
			driver->writeByteReg(BR5, 0);

			temp = driver->readByteReg(BR0);
			temp |= 0x80;
			driver->writeByteReg(BR0, temp);	//BR0(b7) <- 1;

			temp = driver->readNibbleReg(NR2);
			temp |= 1;
			driver->writeNibbleReg(NR2, temp);  //NR2(b0) <- 1;
			return act_success;
		}
	}
		break;
	case int_eoc:
		break;
	}
	return act_continue;
}

MC_Active_Result_E CUInterface::isrNT() {
	switch( getInterruptType() ) {
	case int_act: {
		uint8 temp = driver->readNibbleReg(NR1);
		if( temp == 0x0a || temp == 0x0b ) {
			driver->writeByteReg(BR4, 0);
			driver->writeByteReg(BR5, 0);

			driver->writeByteReg(BR0, 0xf7); //send M4 act to LT
			return act_continue;
		}
		else if( temp == 4 ) {
			driver->writeNibbleReg(NR4, 0); //disable interrupts
			return act_failed;

		}
	}
		break;
	case int_M4: {
		uint8 temp = driver->readByteReg(BR1);
		if( (temp >> 6) & 3 == 3 ) {
			temp = driver->readNibbleReg(NR2);
			temp |= 1;
			driver->writeNibbleReg(NR2, temp);
			return act_success;
		}
	}
		break;
	}
	return act_continue;
}




MC_Interrupt_E CUInterface::getInterruptType(void) {
	uint8 temp = driver->readNibbleReg(NR3);
	if( ((temp >> 3) & 1) == 1 ) {
		return int_act;
	}
	else if( ((temp >> 1) & 1) == 1 ) {
		return int_M4;
	}
	else if( ((temp >> 2) & 1) == 1 ) {
		return int_eoc;
	}
	return int_error;
}
