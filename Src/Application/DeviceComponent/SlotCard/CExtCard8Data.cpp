/*
 * CExtCard8Data.cpp
 *
 *  Created on: 2013-5-24
 *      Author: Administrator
 */

#include "CExtCard8Data.h"
#include "CIsap100HardwareDesc.h"
#include "CDataPort.h"
#include <string.h>
#include "Chip8DataLogic.h"
#include "UID.h"

CExtCard8Data::CExtCard8Data(uint8 slot, std::string& name) : CBaseCard(name, slot) {
	// TODO Auto-generated constructor stub
	EZ_FLASH_DATA_T storeInfo = {
			Data_Part(slot+1),
			sizeof(configData),
			(uint32)&configData };
	FlashDriver.setInfo(storeInfo);
	if( !FlashDriver.ReadData() ) {
		//restore default data

		RestoreDefaultConfig();
	}

	for( int i = 0; i < portNumber; i++ ) {
		ST_Time_Slot info = {slot+1, CIsap100HardwareDesc::slot_stbus_map[slot], CIsap100HardwareDesc::VF_port_channel_Map[i]};
		uint32 uid = UID::makeUID(&info);

		dp[i] = new CDataPort(uid, i, &configData.port[i], &FlashDriver);
	}

}

CExtCard8Data::~CExtCard8Data() {
	// TODO Auto-generated destructor stub
	for( int i = 0; i < portNumber; i++ ) {
		delete dp[i];
	}
}

int CExtCard8Data::GetCartTypeID() {
	return itsTypeID;
}
int CExtCard8Data::getNextVersionIndex(uint8 sn) {
	if( sn >= ext8DtVersionSize ) {
		return -1;
	}
	return sn+1;
}
int CExtCard8Data::getVersion(uint8 id, STVersion& ver) {
	switch( id ) {
	case ext8DtVersionPCB:
		strcpy(ver.ucpVerName, "Ext8DataPCBVersion");
		ver.uiVerNum = 16;
		return 1;
	case ext8DtVersionChip:
		strcpy(ver.ucpVerName, "Ext8DataChipVersion");
		ver.uiVerNum = get8DataVersion(getSn());
		if( ver.uiVerNum < 16 ) {
			ver.uiVerNum = 16;
		}
		return 1;
	}
	return -1;
}


void CExtCard8Data::RestoreDefaultConfig(void) {
	for( int i = 0; i < portNumber; i++ ) {
		configData.port[i].desclen = 0;
		configData.port[i].enable = 1;
	}
	FlashDriver.SaveData();
}
