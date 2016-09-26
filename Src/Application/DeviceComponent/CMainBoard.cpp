/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **								
 **										ISAP100_Realese
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CMainBoard.cpp
 ** File path:			/ISAP100_Realese/Src/Application/DeviceComponent/CMainBoard.cpp
 ** Created by:          Shqp
 ** Created date:        2013-3-4
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
 * CMainBoard.cpp
 *
 *  Created on: 2013-3-4
 *      Author: Shqp
 */

#include "CMainBoard.h"
#include "CTSE1.h"
#include "CIsap100HardwareDesc.h"
#include "CE1Channel.h"
#include "CDeviceAttribute.h"
#include "UID.h"
#include "CNME1Port.h"
#include "CUpE1Port.h"
#include <string.h>

CMainBoard::CMainBoard(uint32 slot, int subType) {
	for( int i = 0; i < 4; i++ ) {
		new CE1Channel(slot-1,
			CIsap100HardwareDesc::upE1_channel_map[i], i);
		new CTSE1(slot-1, CIsap100HardwareDesc::upE1_channel_map[i], i);
	}

	EZ_FLASH_DATA_T storeInfo = { MB_FE1_Config_Block_Start, sizeof(configData),
			(uint32) &configData };
	FlashDriver.setInfo(storeInfo);
	if (!FlashDriver.ReadData()) {
		defaultFE1Config();
	}

	for (int i = 0; i < 2; ++i) {
		nmport[i] = 0;
		upe1[i] = 0;
	}
	if( subType == type_isap_A_4eth_iso || subType == type_isap_A_8eth_iso ) {
		ST_E1 info;
		info.slot = 100;
		for (int i = 0; i < 2; ++i) {
			info.E1 = i;
			uint32 uid = UID::makeUID(&info);
			nmport[i] = new CNME1Port(uid, &configData.fe1[i], &FlashDriver);
		}
	}
	else if( subType == type_emux_v12 || subType == type_emux_v10 ) {
		ST_E1 info;
		info.slot = 100;
		for (int i = 0; i < 2; ++i) {
			info.E1 = i;
			uint32 uid = UID::makeUID(&info);
			upe1[i] = new CUpE1Port(uid, i+2, &configData.upe1[i], &FlashDriver);
		}
	}

}

CMainBoard::~CMainBoard() {
	// TODO Auto-generated destructor stub
}

void CMainBoard::defaultFE1Config(void) {
	memset(&configData, 0, sizeof(configData));
	for (int i = 0; i < 2; ++i) {
		configData.fe1[i].enable = 1;
		configData.fe1[i].mode = 0;
		configData.upe1[i].enable = 1;
		configData.upe1[i].nmcfg.type = 0;
		configData.upe1[i].nmcfg.dcnCH.bitMap = (1<<30);
		configData.upe1[i].nmcfg.porten = 1;
		configData.upe1[i].nmcfg.topodir = 4;
	}

}

void CMainBoard::processAlarm(void) {
	for (int i = 0; i < 2; ++i) {
		if( nmport[i] != 0 ) {
			nmport[i]->processAlarm();
		}
		if( upe1[i] != 0 ) {
			upe1[i]->processAlarm();
		}
	}
}
