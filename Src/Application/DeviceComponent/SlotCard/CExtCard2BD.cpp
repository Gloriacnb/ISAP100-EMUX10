/*
 * CExtCard2BD.cpp
 *
 *  Created on: 2013-7-29
 *      Author: Administrator
 */

#include "CExtCard2BD.h"
#include "CUInterface.h"
#include "UID.h"
#include "MidMC145572.h"
#include <string.h>
#include "Chip2BDLogic.h"

CExtCard2BD::CExtCard2BD(uint8 slot, std::string& name) : CBaseCard(name, slot) {
	// TODO Auto-generated constructor stub
	EZ_FLASH_DATA_T storeInfo = {
			Data_Part(slot+1),
			sizeof(configData),
			(uint32)&configData };
	stroer.setInfo(storeInfo);
	if( !stroer.ReadData() ) {
		//restore default data

		RestoreDefaultConfig();
	}

	for( int i = 0; i < PortNumber; i++ ) {
		//int lid = getSn()*4 + i;
		ST_E1 info = {getSn() + 1, i};
		uint32 uid = UID::makeUID(&info);
		MidMC145572* mc = new MidMC145572(getSn(), i);
		uif[i] = new CUInterface(i, uid, &configData.port[i], &stroer, mc);
	}

}

CExtCard2BD::~CExtCard2BD() {
	// TODO Auto-generated destructor stub
	for( int i = 0; i < PortNumber; i++ ) {
		delete uif[i];
	}
}

void CExtCard2BD::RestoreDefaultConfig() {
	for( int i = 0; i < PortNumber; i++ ) {
		configData.port[i].mode = 0;
	}
	stroer.SaveData();
}

int CExtCard2BD::getNextVersionIndex(uint8 sn) {
	if( sn >= ext2BDVersionSize ) {
		return -1;
	}
	return sn+1;
}

int CExtCard2BD::getVersion(uint8 id, STVersion& ver) {
	switch( id ) {
	case ext2BDVersionPCB:
		ver.uiVerNum = 16;
		strcpy(ver.ucpVerName, "Ext2BDPCBVersion");
		return 1;
	case ext2BDVersionChip:
		strcpy(ver.ucpVerName, "Ext2BDChipVersion");
		ver.uiVerNum = get2BDChipVersion(getSn());
		return 1;
	}
	return -1;
}
