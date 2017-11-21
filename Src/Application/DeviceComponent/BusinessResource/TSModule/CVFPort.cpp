/*
 * CVFPort.cpp
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#include "CVFPort.h"
#include "UID.h"
#include "CTSChannel.h"
#include <string.h>
#include "CPPTools.h"
#include "Chip8VFLogic.h"
#include "CMSSave.h"
#include "Pcm821054.h"
#include "FVIdt821054Access.h"
#include <stdio.h>

std::map<uint32, CVFPort*> CVFPort::Group;
//static int DGainCmd =0x08;
//static int AGainCmd =0;
CVFPort::CVFPort(uint32 userIndex, uint8 psn, VF_Port_Config_T* cfgData, VF_Group_Config_T* grpConfig, CMSSave* driver)  : RealPortBase(userIndex){
	uid = userIndex;
	LinkChannel = CTSChannel::getTSChannelByUid(uid);
	if( LinkChannel ) {
		LinkChannel->setActive(1);
	}
	groupConfigData = grpConfig;
	configData = cfgData;
	cfgDriver = driver;
	portSn = psn;

	name = "slot-" + CPPTools::number2string(uid>>24) + "-VFPort-" + CPPTools::number2string(portSn+1);

	Group.insert(std::pair<uint32, CVFPort*>(uid, this));

	VFType = getPortType();
	setEnable(configData->enable, false);
	setWorkMode(configData->work_mode, false);
	setPolarTurn(configData->polar_turn, false);
//	if(( VFType== DEF_VFType_4W) || (VFType == DEF_VFType_2W)) {
//		setRcvGain(configData->rcv_gain, false);
//		setSndGain(configData->snd_gain, false);
//	}
//	else if( VFType == DEF_VFType_MT ) {
//        //���1.5V Ƶ��2100HZ
//		uint8 chipID, ch;
//		getHinfo(uid, portSn, &chipID, &ch);
//        uint16 coeWrite[2] = {0x3d00, 0xf5f4};
//    	writeIDTChipCoeRamBlock(chipID, ch, 2, coeWrite, 2);
//
//	}
}

CVFPort::~CVFPort() {
	// TODO Auto-generated destructor stub
	LinkChannel->setActive(0);
	Group.erase(uid);
}

uint8 CVFPort::getEnable(void) {
	return configData->enable;
}
int CVFPort::setEnable(uint8 en, bool save) {
	uint8 chipID, ch;
	uint8 pd = !en;

	getHinfo(uid, portSn, &chipID, &ch);
	if( setPowerDown(chipID,ch,pd) < 0 ) {
		return -1;
	}

	configData->enable = en;
	cfgDriver->SaveData();
	return 1;
}

uint8 CVFPort::getWorkMode(void) {
	return configData->work_mode;
}
int CVFPort::setWorkMode(uint8 mode, bool save) {
	uint8 slot = (uid >> 24)-1;
	if( itsType() == DEF_VFType_MT ) {
		uint8 chipID, ch;
		getHinfo(uid, portSn, &chipID, &ch);
		if( mode == DEF_MT_Wave ) {
            //SI1 ȥ�� 20ms
            WriteIdtChipLocRegister(chipID, ch, 2, 0x0f);
            setMTMode(slot, portSn, 1);

		}
		else {
            //SI1 ȥ�� 20ms
            WriteIdtChipLocRegister(chipID, ch, 2, 0x00);
            setMTMode(slot, portSn, 0);
		}
	}
	else if( itsType() == DEF_VFType_FXS ) {
		setHotLine(slot, portSn, mode);
	}
	else {
		return -1;
	}
	if( save ) {
		configData->work_mode = mode;
		cfgDriver->SaveData();
	}
	return 1;
}

uint8 CVFPort::getPolarTurn(void) {
	return configData->polar_turn;
}
int CVFPort::setPolarTurn(uint8 en, bool save) {
	uint8 slot = (uid >> 24)-1;
	uint8 dis = ((en == 0) ? 1:0);
	setPolarDisable(slot, portSn, dis);
	if( save ) {
		configData->polar_turn = en;
		cfgDriver->SaveData();
	}
	return 1;
}


char* CVFPort::getDesc(uint32* len) {
	*len = configData->desclen;
	return configData->desc;
}
int CVFPort::setDesc(const char* s, uint32 len) {
	configData->desclen = len;
	memcpy(configData->desc, s, len);
	cfgDriver->SaveData();
	return 1;
}

uint8 CVFPort::getPortType(void) {
	uint8 slot = (uid >> 24)-1;
	return getVFType(slot, portSn);
}

int CVFPort::setLoop(const int type) {
	uint8 chipID, ch;
	getHinfo(uid, portSn, &chipID, &ch);
	ch++;
	switch( type ) {
	case dev_and_line_loop:
		setLoopBackAnalogOnebit(chipID, ch, 1);
		setLoopBackDigitalOnebit(chipID, ch, 1);
		break;
	case line_loop:
		setLoopBackAnalogOnebit(chipID, ch, 1);
		setLoopBackDigitalOnebit(chipID, ch, 0);
		break;
	case dev_loop:
		setLoopBackAnalogOnebit(chipID, ch, 0);
		setLoopBackDigitalOnebit(chipID, ch, 1);
		break;
	case no_loop:
		setLoopBackAnalogOnebit(chipID, ch, 0);
		setLoopBackDigitalOnebit(chipID, ch, 0);
		break;
	default:
		return -1;
	}
	return 0x5A;
}


void CVFPort::getHinfo(uint32 userIndex, uint8 port, uint8* chipID, uint8* ch) {
	uint8 chip = (((userIndex>>24) - 1) << 2)+1;
	uint8 channel = port+1;

	if( port > 3 ) {
		++chip;
		channel -= 4;
	}

	*chipID = chip;
	*ch = channel;
}

void CVFPort::process2100HZ(void) {
	uint8 chipID, ch;
	getHinfo(uid, portSn, &chipID, &ch);
	if( (itsType() == DEF_VFType_MT) && (getWorkMode() == DEF_MT_Wave) ) {

		/*AD ����*/
//		uint8 onhook = getHookState(getUID()>>24, portSn);
//		if( onhook == 0 ) {
//			WriteIdtChipLocRegister(chipID, ch, 9, 0x0a);
//		}
//		else {
//			WriteIdtChipLocRegister(chipID, ch, 9, 0x00);
//		}

		/*DA ����*/
		int regV = 0;
		ReadIdtChipGlbRegister(chipID, 0x28, &regV);
		regV = (regV >> (ch-1)) & 1;
		if( regV == 0 ) {
			setRC((uid>>24)-1, portSn, 1);
		}
		else {
			setRC((uid>>24)-1, portSn, 0);
		}
	}
}

