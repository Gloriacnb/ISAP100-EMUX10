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
#define AD_MAX 64
#define DA_MAX 64

//static uint16 sndgain[AD_MAX]={
//	0xccc0,	0xcf80, 0xd220, 0xd4a8, 0xd738, 0xd990, 0xdbb8, 0xddb0,
//	0xdfb0, 0xe164, 0xe330, 0xe4d8, 0xe658, 0xe7bc, 0xe90c, 0xea54,
//	0xeb98, 0xecc0, 0xedd4, 0xeecc, 0xefd0, 0xf0b4, 0xf188, 0xf260,
//	0xf324, 0xf3d4, 0xf48c, 0xf528, 0xf5d0, 0xf666, 0xf6e8, 0xf764,
//	0xf7dc, 0xf850, 0xf8c4, 0xf930, 0xf990, 0xf9e8, 0xfa44, 0xfa94,
//	0xfae4, 0xfb30, 0xfb74, 0xfbb4, 0xfbf0, 0xfc28, 0xfc63, 0xfc98,
//	0xfcc8, 0xfcf4, 0xfd24, 0xfd4c, 0xfd70, 0xfd98, 0xfdb8, 0xfdd8,
//	0xfdf8, 0xfe14, 0xfe30, 0xfe4c, 0xfe64, 0xfe78, 0xfe90, 0xfea4,
//};//-14dBm0~+17.5dBm0
static uint16 sndgain[AD_MAX]={
	0x7DEB, 0x76E0, 0x703A, 0x69F2, 0x6405, 0x5E6D, 0x5925, 0x5428,
	0x4F73, 0x4B01, 0x46CF, 0x42D9, 0x7DEB, 0x76E0, 0x703A, 0x69F2,
	0x6405, 0x5E6D, 0x5925, 0x5428, 0x4F73, 0x4B01, 0x46CF, 0x42D9,
	0x3F1C, 0x3B94, 0x383F, 0x3519, 0x3221, 0x2F53, 0x2CAD, 0x2A2D,
	0x27D1, 0x2597, 0x237D, 0x2181, 0x1FA1, 0x1DDC, 0x1C30, 0x1A9C,
	0x191F, 0x17B8, 0x1664, 0x1523, 0x13F5, 0x12D7, 0x11C9, 0x10CA,
	0x1009, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};//-14dBm0~+17.5dBm0

//static uint16 rcvgain[DA_MAX]={
//	0xff30, 0xff24, 0xff18, 0xff08, 0xfefc, 0xfeec, 0xfedc, 0xfec8,
//	0xfeb8, 0xfea4, 0xfe90, 0xfe7c, 0xfe64, 0xfe4c, 0xfe30, 0xfe18,
//	0xfdfc, 0xfddc, 0xfdb4, 0xfd98, 0xfd6c, 0xfd4c, 0xfd20, 0xfcf0,
//	0xfcc4, 0xfc94, 0xfc60, 0xfc2c, 0xfbf4, 0xfbb4, 0xfb74, 0xfb30,
//	0xfae8, 0xfa9c, 0xfa4c, 0xf9f4, 0xf998, 0xf938, 0xf8d4, 0xf868,
//	0xf7f9, 0xf780, 0xf700, 0xf674, 0xf5e4, 0xf54c, 0xf4a8, 0xf3fc,
//	0xf34c, 0xf288, 0xf1c0, 0xf0e0, 0xeff8, 0xef08, 0xee10, 0xecf4,
//	0xebd4, 0xeaa0, 0xe95c, 0xe808, 0xe698, 0xe518, 0xe384, 0xe1dc,
//};//-27.5dBm0~+4dBm0

static uint16 rcvgain[DA_MAX]={
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x00C6, 0x00D1, 0x00DE, 0x00EB, 0x00F9,
	0x0108, 0x0117, 0x0128, 0x013A, 0x014C, 0x0160, 0x0175, 0x00C6,
	0x00D1, 0x00DE, 0x00EB, 0x00F9, 0x0108, 0x0117, 0x0128, 0x013A,
	0x014C, 0x0160, 0x0175, 0x018B, 0x01A2, 0x01BB, 0x01D5, 0x01F1,
	0x020F, 0x022E, 0x024F, 0x0272, 0x0297, 0x02BF, 0x02E8, 0x0315,
};//-14dBm0~+4dBm0
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
	if(( VFType== DEF_VFType_4W) || (VFType == DEF_VFType_2W)) {
		setRcvGain(configData->rcv_gain, false);
		setSndGain(configData->snd_gain, false);
	}
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

uint8 CVFPort::getSndGain(void) {
	return configData->snd_gain;
}
int CVFPort::setSndGain(uint8 vl, bool save) {
	uint8 chipID, ch;
	getHinfo(uid, portSn, &chipID, &ch);
	if( vl < AD_MAX ) {
		if( sndgain[vl] == 0 ) {
			configData->snd_gain = vl;//0/6
			if( save ) {
				cfgDriver->SaveData();
			}
			return 1;
		}
		if( writeIDTChipCoeRamBlock(chipID,ch, 3, &sndgain[vl], 1) >= 0 ) {
			if( vl < 12 ) {
				int d = 0;
				ReadIdtChipLocRegister(chipID, ch, 8, &d);
				WriteIdtChipLocRegister(chipID, ch, 8, d | 0x20);
			}
			else {
				int d = 0;
				ReadIdtChipLocRegister(chipID, ch, 8, &d);
				WriteIdtChipLocRegister(chipID, ch, 8, d & ~0x20);
			}
			configData->snd_gain = vl;//0/6
			if( save ) {
				cfgDriver->SaveData();
			}
			return 1;
		}
	}
	return -1;
}

uint8 CVFPort::getRcvGain(void) {
	return configData->rcv_gain;
}

int CVFPort::setRcvGain(uint8 vl, bool save) {
	uint8 chipID, ch;
	getHinfo(uid, portSn, &chipID, &ch);
	if( vl < DA_MAX ) {
		if( rcvgain[vl] == 0 ) {
			configData->rcv_gain = vl;//0/6
			if( save ) {
				cfgDriver->SaveData();
			}
			cfgDriver->SaveData();
			return 1;
		}
		if( writeIDTChipCoeRamBlock(chipID,ch, 4, &rcvgain[vl], 1) >= 0) {
			if( vl < 39 ) {
				int d = 0;
				ReadIdtChipLocRegister(chipID, ch, 8, &d);
				WriteIdtChipLocRegister(chipID, ch, 8, d | 0x10);
			}
			else {
				int d = 0;
				ReadIdtChipLocRegister(chipID, ch, 8, &d);
				WriteIdtChipLocRegister(chipID, ch, 8, d & ~0x10);
			}
			configData->rcv_gain = vl;//0/6
			if( save ) {
				cfgDriver->SaveData();
			}
			cfgDriver->SaveData();
			return 1;
		}
	}
	return -1;
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

