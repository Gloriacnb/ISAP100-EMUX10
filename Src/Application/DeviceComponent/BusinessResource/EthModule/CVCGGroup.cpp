/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **								
 **										ISAP100_Realese
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CVCGGroup.cpp
 ** File path:			/ISAP100_Realese/Src/Application/DeviceComponent/BusinessResource/EthModule/CVCGGroup.cpp
 ** Created by:          Shqp
 ** Created date:        2013-3-19
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/
/*
 * CVCGGroup.cpp
 *
 *  Created on: 2013-3-19
 *      Author: Shqp
 */

#include "CVCGGroup.h"
#include "UID.h"
#include "Mid_FlashData.h"
#include <string.h>
#include "Mid_RC7880A1App.h"
#include "CVCG.h"
#include "DeviceLocal.h"
//#include ""

CVCGGroup::CVCGGroup(int n) {
	// TODO Auto-generated constructor stub
	storeInfo.BlockFirst = MB_VCG_Config_Block_Start;
	storeInfo.BufAddr = (uint32) &storeData;
	storeInfo.ByteNums = sizeof(storeData);
	FlashDriver.setInfo(storeInfo);

	if (!FlashDriver.ReadData()) {
		//restore default data

		RestoreDefauleConfig();
	}
	ST_VCG info = { 100, 0 };
	for (int i = 0; i < n; i++) {
		info.vcg = i;
		uint32 vcguid = UID::makeUID(&info);
		CVCG* pvcg = new CVCG(i, vcguid, &storeData.vcg[i], &FlashDriver);
		if (pvcg) {
			mapVCG.insert(std::pair<uint32, CVCG*>(vcguid, pvcg));
		} else {
			while (1)
				;
		}
	}
}

CVCGGroup::~CVCGGroup() {
	// TODO Auto-generated destructor stub
}

CVCG* CVCGGroup::GetObjectByUID(uint32 uid) {
	it = mapVCG.find(uid);
	if (it != mapVCG.end()) {
		return it->second;
	}
	return 0;
}

void CVCGGroup::RestoreDataVCG(int n, int vc12begin, int vc12num) {
	storeData.vcg[n].enable = 1;
	storeData.vcg[n].lcas = 1;
	storeData.vcg[n].band = vc12num;
	ST_SDH_VC12 info = { 100, 0, 0, vc12begin };
	for (int i = 0; i < storeData.vcg[n].band; i++) {
		info.lp = vc12begin + i;
		storeData.vcg[n].member[i].vc12 = UID::makeUID(&info);
		storeData.vcg[n].member[i].sncp = 0;
	}
	for (int i = 0; i < VCG_type_size; i++) {
		storeData.vcg[n].alarmProperty[i].typeID = i + VCG_type_base;
		storeData.vcg[n].alarmProperty[i].level = primary;
		storeData.vcg[n].alarmProperty[i].mask = 0;
		storeData.vcg[n].alarmProperty[i].trap = 1;
	}
	for (int i = 0; i < Member_type_size; i++) {
		storeData.vcg[n].alarmProperty[i + VCG_type_size].typeID = i
				+ Member_type_size;
		storeData.vcg[n].alarmProperty[i + VCG_type_size].level = secondary;
		storeData.vcg[n].alarmProperty[i + VCG_type_size].mask = 0;
		storeData.vcg[n].alarmProperty[i + VCG_type_size].trap = 1;
	}
}

void CVCGGroup::RestoreDefauleConfig(void) {
	memset(&storeData, 0, sizeof(storeData));
	switch (DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceSubtype()) {
	case 10: //8 eth 8306E
	case 11: // 4 eth old
	case 16:
	case 12: // 4 eth 8306e
		RestoreDataVCG(0, 20, 11);
		RestoreDataVCG(1, 31, 11);
		RestoreDataVCG(2, 42, 11);
		RestoreDataVCG(3, 53, 10);
		break;
	default:
		return;
	}
	FlashDriver.SaveData();
}

uint32 CVCGGroup::getFirstVCGUID(void) {
	it = mapVCG.begin();
	if (it != mapVCG.end()) {
		return it->first;
	}
	return 0;
}

uint32 CVCGGroup::getNextVCGUID(uint32 suid) {
	it = mapVCG.find(suid);
	if (it != mapVCG.end()) {
		it++;
		if (it != mapVCG.end()) {
			return it->first;
		}
	}
	return 0;
}

void CVCGGroup::processAlarm(void) {
	it = mapVCG.begin();
	while (it != mapVCG.end()) {
		it->second->processAlarm();
		it++;
	}
}

