/*
 * CVFPortA.cpp
 *
 *  Created on: 2017年11月17日
 *      Author: Administrator
 */

#include "CVFPortA.h"
#include "Pcm821054.h"
#include "FVIdt821054Access.h"
#include "CMSSave.h"

#define AD_MAX 64
#define DA_MAX 64

static uint16 sndgain[AD_MAX]={
	0xccc0,	0xcf80, 0xd220, 0xd4a8, 0xd738, 0xd990, 0xdbb8, 0xddb0,
	0xdfb0, 0xe164, 0xe330, 0xe4d8, 0xe658, 0xe7bc, 0xe90c, 0xea54,
	0xeb98, 0xecc0, 0xedd4, 0xeecc, 0xefd0, 0xf0b4, 0xf188, 0xf260,
	0xf324, 0xf3d4, 0xf48c, 0xf528, 0xf5d0, 0xf666, 0xf6e8, 0xf764,
	0xf7dc, 0xf850, 0xf8c4, 0xf930, 0xf990, 0xf9e8, 0xfa44, 0xfa94,
	0xfae4, 0xfb30, 0xfb74, 0xfbb4, 0xfbf0, 0xfc28, 0xfc63, 0xfc98,
	0xfcc8, 0xfcf4, 0xfd24, 0xfd4c, 0xfd70, 0xfd98, 0xfdb8, 0xfdd8,
	0xfdf8, 0xfe14, 0xfe30, 0xfe4c, 0xfe64, 0xfe78, 0xfe90, 0xfea4,
};//-14dBm0~+17.5dBm0

static uint16 rcvgain[DA_MAX]={
	0xff30, 0xff24, 0xff18, 0xff08, 0xfefc, 0xfeec, 0xfedc, 0xfec8,
	0xfeb8, 0xfea4, 0xfe90, 0xfe7c, 0xfe64, 0xfe4c, 0xfe30, 0xfe18,
	0xfdfc, 0xfddc, 0xfdb4, 0xfd98, 0xfd6c, 0xfd4c, 0xfd20, 0xfcf0,
	0xfcc4, 0xfc94, 0xfc60, 0xfc2c, 0xfbf4, 0xfbb4, 0xfb74, 0xfb30,
	0xfae8, 0xfa9c, 0xfa4c, 0xf9f4, 0xf998, 0xf938, 0xf8d4, 0xf868,
	0xf7f9, 0xf780, 0xf700, 0xf674, 0xf5e4, 0xf54c, 0xf4a8, 0xf3fc,
	0xf34c, 0xf288, 0xf1c0, 0xf0e0, 0xeff8, 0xef08, 0xee10, 0xecf4,
	0xebd4, 0xeaa0, 0xe95c, 0xe808, 0xe698, 0xe518, 0xe384, 0xe1dc,
};//-27.5dBm0~+4dBm0


CVFPortA::CVFPortA(uint32 userIndex, uint8 psn, VF_Port_Config_T* cfgData, VF_Group_Config_T* grpConfig, CMSSave* driver)
		: CVFPort(userIndex, psn, cfgData, grpConfig, driver){
	if(( VFType== DEF_VFType_4W) || (VFType == DEF_VFType_2W)) {
		setRcvGain(groupConfigData->rcv_gain, false);
		setSndGain(groupConfigData->snd_gain, false);
	}
}

CVFPortA::~CVFPortA() {
	// TODO Auto-generated destructor stub
}

uint8 CVFPortA::getSndGain(void) {
	return groupConfigData->snd_gain;
}


uint8 CVFPortA::getRcvGain(void) {
	return groupConfigData->rcv_gain;
}

int CVFPortA::setSndGain(uint8 vl, bool save) {
	uint8 chipID, ch;
	getHinfo(uid, portSn, &chipID, &ch);
	if( vl < AD_MAX ) {
		if( writeIDTChipCoeRamBlock(chipID,ch, 3, &sndgain[vl], 1) >= 0 ) {
			groupConfigData->snd_gain = vl;//0/6
			if( save ) {
				cfgDriver->SaveData();
			}
			return 1;
		}
	}
	return -1;
}


int CVFPortA::setRcvGain(uint8 vl, bool save) {
	uint8 chipID, ch;
	getHinfo(uid, portSn, &chipID, &ch);
	if( vl < DA_MAX ) {
		if( writeIDTChipCoeRamBlock(chipID,ch, 4, &rcvgain[vl], 1) >= 0) {
			groupConfigData->rcv_gain = vl;//0/6
			if( save ) {
				cfgDriver->SaveData();
			}
			cfgDriver->SaveData();
			return 1;
		}
	}
	return -1;
}
