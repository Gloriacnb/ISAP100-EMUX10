/*
 * CExtCard8VF.cpp
 *
 *  Created on: 2012-12-26
 *      Author: Administrator
 */

#include "CExtCard8VF.h"
#include "Chip8VFLogic.h"
#include "Pcm821054.h"
#include "CIsap100HardwareDesc.h"
#include "CVFPort.h"
#include <string.h>
#include "UID.h"
#include <stdio.h>
#include "Task_define.h"

__task void T_MT_Wave(void* card );

CExtCard8VF::~CExtCard8VF() {
	// TODO Auto-generated destructor stub
	os_tsk_delete(TaskMtWave);
	for( int i = 0; i < portNumber; i++ ) {
		delete vf[i];
	}

}

CExtCard8VF::CExtCard8VF(uint8 slot, std::string& name) : CBaseCard(name, slot) {
//	slotNumber = slot;
	EZ_FLASH_DATA_T storeInfo = {
			Data_Part(slot+1),
			sizeof(configData),
			(uint32)&configData };
	stroer.setInfo(storeInfo);
	if( !stroer.ReadData() ) {
		//restore default data

		RestoreDefaultConfig();
	}
	Init821054(getSn());
	InitExt8VFChip(slot, &configData);
	for( int i = 0; i < portNumber; i++ ) {
		ST_Time_Slot info = {slot+1, CIsap100HardwareDesc::slot_stbus_map[slot], CIsap100HardwareDesc::VF_port_channel_Map[i]};
		uint32 uid = UID::makeUID(&info);

		vf[i] = new CVFPort(uid, i,	&configData.port[i],&configData.group[i/4], &stroer);
	}

	TaskMtWave = os_tsk_create_ex(T_MT_Wave, P_MT, this);
}


int CExtCard8VF::GetCartTypeID() {
	return itsTypeID;
}


void CExtCard8VF::RestoreDefaultConfig(void) {
	memset( &configData, 0, sizeof(configData));
	for( int i = 0; i < portNumber; i++ ) {
		configData.port[i].enable = 1;
		configData.port[i].rcv_gain = 48;
		configData.port[i].snd_gain = 29;
	}
}


int CExtCard8VF::getNextVersionIndex(uint8 sn) {
	if( sn >= ext8VFVersionSize ) {
		return -1;
	}
	return sn+1;
}
int CExtCard8VF::getVersion(uint8 id, STVersion& ver) {
	switch( id ) {
	case ext8VFVersionPCB:
		strcpy(ver.ucpVerName, "Ext8VFPCBVersion");
		ver.uiVerNum = 16;
		return 1;
	case ext8VFVersionChip:
		strcpy(ver.ucpVerName, "Ext8VFChipVersion");
		ver.uiVerNum = get8VFVersion(getSn());
		if( ver.uiVerNum < 16 ) {
			ver.uiVerNum = 16;
		}
		return 1;
	}
	return -1;
}

__task void T_MT_Wave(void* card ) {
	CExtCard8VF* vfcard = (CExtCard8VF*)card;
	while( 1 ) {
		os_dly_wait(5);
		for (int i = 0; i < vfcard->portNumber; ++i) {
			vfcard->vf[i]->process2100HZ();
		}
	}
}
