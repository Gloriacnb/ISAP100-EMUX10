/*
 * CVFPortG.cpp
 *
 *  Created on: 2017年11月17日
 *      Author: Administrator
 */

#include "CVFPortG.h"
#include "UID.h"
#include "CTSChannel.h"
#include <string.h>
#include "CPPTools.h"
#include "Chip8VFLogic.h"
#include "CMSSave.h"
#include "Pcm821054.h"
#include "FVIdt821054Access.h"
#include <stdio.h>

#define AD_MAX 49
#define DA_MAX 49

static uint16 sndgain[AD_MAX]={
	0x7DEB, 0x76E0, 0x703A, 0x69F2, 0x6405, 0x5E6D, 0x5925, 0x5428,
	0x4F73, 0x4B01, 0x46CF, 0x42D9, 0x7DEB, 0x76E0, 0x703A, 0x69F2,
	0x6405, 0x5E6D, 0x5925, 0x5428, 0x4F73, 0x4B01, 0x46CF, 0x42D9,
	0x3F1C, 0x3B94, 0x383F, 0x3519, 0x3221, 0x2F53, 0x2CAD, 0x2A2D,
	0x27D1, 0x2597, 0x237D, 0x2181, 0x1FA1, 0x1DDC, 0x1C30, 0x1A9C,
	0x191F, 0x17B8, 0x1664, 0x1523, 0x13F5, 0x12D7, 0x11C9, 0x10CA,
	0x1009,
};//-14dBm0~+10dBm0


static uint16 rcvgain[DA_MAX]={
	0x00C6, 0x00D1, 0x00DE, 0x00EB, 0x00F9, 0x0108, 0x0117, 0x0128,
	0x013A, 0x014C, 0x0160, 0x0175, 0x00C6, 0x00D1, 0x00DE, 0x00EB,
	0x00F9, 0x0108, 0x0117, 0x0128, 0x013A, 0x014C, 0x0160, 0x0175,
	0x018B, 0x01A2, 0x01BB, 0x01D5, 0x01F1, 0x020F, 0x022E, 0x024F,
	0x0272, 0x0297, 0x02BF, 0x02E8, 0x0315, 0x0343, 0x0375, 0x03A9,
	0x03E1, 0x041C, 0x045A, 0x049C, 0x04E2, 0x052C, 0x057B, 0x05CE,
	0x0614,
};//-14dBm0~+10dBm0
//static int DGainCmd =0x08;
//static int AGainCmd =0;
CVFPortG::CVFPortG(uint32 userIndex, uint8 psn, VF_Port_Config_T* cfgData, VF_Group_Config_T* grpConfig, CMSSave* driver)
		: CVFPort(userIndex, psn, cfgData, grpConfig, driver){
	if(( VFType== DEF_VFType_4W) || (VFType == DEF_VFType_2W)) {
		setRcvGain(configData->rcv_gain, false);
		setSndGain(configData->snd_gain, false);
	}
}

CVFPortG::~CVFPortG() {
	// TODO Auto-generated destructor stub
	LinkChannel->setActive(0);
	Group.erase(uid);
}

uint8 CVFPortG::getSndGain(void) {
	return configData->snd_gain;
}


uint8 CVFPortG::getRcvGain(void) {
	return configData->rcv_gain;
}

int CVFPortG::setSndGain(uint8 vl, bool save) {
	uint8 chipID, ch;
	getHinfo(uid, portSn, &chipID, &ch);
	if( vl < AD_MAX ) {
		if( writeIDTChipCoeRamBlock(chipID,ch, 3, &sndgain[vl], 1) >= 0 ) {
			if( vl < 12 ) {//打开模拟增益
				int d = 0;
				ReadIdtChipLocRegister(chipID, ch, 8, &d);
				WriteIdtChipLocRegister(chipID, ch, 8, d | 0x20);
			}
			else {
				//关闭模拟增益
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


int CVFPortG::setRcvGain(uint8 vl, bool save) {
	uint8 chipID, ch;
	getHinfo(uid, portSn, &chipID, &ch);
	if( vl < DA_MAX ) {
		if( writeIDTChipCoeRamBlock(chipID,ch, 4, &rcvgain[vl], 1) >= 0) {
			if( vl < 12 ) {
				//打开模拟增益 6DB
				int d = 0;
				ReadIdtChipLocRegister(chipID, ch, 8, &d);
				WriteIdtChipLocRegister(chipID, ch, 8, d | 0x10);
			}
			else {
				//关闭模拟增益
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


