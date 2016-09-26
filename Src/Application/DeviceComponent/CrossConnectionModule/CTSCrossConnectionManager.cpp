/*
 * CTSCrossConnectionManager.cpp
 *
 *  Created on: 2013-5-2
 *      Author: Administrator
 */

#include "CTSCrossConnectionManager.h"
#include "CCrossConnection.h"
#include "CTSChannel.h"
#include "UID.h"
#include "CIsap100HardwareDesc.h"
#include "ChipSlotLogic.h"
#include <string.h>


int CTSCrossConnectionManager::currentSn = 0;

CTSCrossConnectionManager::CTSCrossConnectionManager() {

	storeInfo.BlockFirst	= SYS_TS_Cross_Block_Start;
	storeInfo.BufAddr 		= (uint32)&storeData;
	storeInfo.ByteNums		= sizeof(storeData);

	FlashDriver.setInfo(storeInfo);
	if( !FlashDriver.ReadData() ) {
		//default config
		RestoreDefaultConfig();
	}
	for( int i = 0; i < storeData.size; i++ ) {
		uint32 ccid = CreatConnection_start(storeData.ccdata[i].west, storeData.ccdata[i].east);
		std::string name((const char*)storeData.ccdata[i].name);
		SetXcName_start(ccid, name);
		std::string desc((const char*)storeData.ccdata[i].desc);
		SetXcDescription_start(ccid, desc);
	}

}

CTSCrossConnectionManager::~CTSCrossConnectionManager() {
	// TODO Auto-generated destructor stub
}

uint32 CTSCrossConnectionManager::CreatConnection_start(uint32 uiWestIndex, uint32 uiEastIndex) {
	CTSChannel* pWestSlot = CTSChannel::getTSChannelByUid(uiWestIndex);
	CTSChannel* pEastSlot = CTSChannel::getTSChannelByUid(uiEastIndex);
	if( pWestSlot == 0 || pEastSlot ==0 ) {
		return 0;
	}
	if( pWestSlot->ifOcuppy() || pEastSlot->ifOcuppy() ) {
		return 0;
	}

	uint8 westST,westTS,eastST,eastTS;
	try {
		uint8 slot = UID::breakUID(uiWestIndex).ts.slot;
		if( slot == 100 ) {
			westST = UID::breakUID(uiWestIndex).ts.E1;
			westTS = UID::breakUID(uiWestIndex).ts.TS;
		}
		else {
			westST = CIsap100HardwareDesc::slot_stbus_map[slot-1];
			westTS = UID::breakUID(uiWestIndex).ts.TS;
		}

		slot = UID::breakUID(uiEastIndex).ts.slot;
		if( slot == 100 ) {
			eastST = UID::breakUID(uiEastIndex).ts.E1;
			eastTS = UID::breakUID(uiEastIndex).ts.TS;
		}
		else {
			eastST = CIsap100HardwareDesc::slot_stbus_map[slot-1];
			eastTS = UID::breakUID(uiEastIndex).ts.TS;
		}
	}
	catch(...) {
		return 0;
	}
	//操作硬件
	CreatCrossConnection(westST, westTS, eastST, eastTS);

	CreatCrossConnection(eastST, eastTS, westST, westTS);
	//设置时隙为占用状态
	pWestSlot->setMapPartner(uiEastIndex);
	pEastSlot->setMapPartner(uiWestIndex);
	++currentSn;
	cc.insert(
			std::pair<int, CCrossConnection*>
	(currentSn, new CCrossConnection(currentSn,uiWestIndex, uiEastIndex)));
	return currentSn;

}

uint32 CTSCrossConnectionManager::CreatConnection(uint32 uiSour, uint32 uiDest) {
	CreatConnection_start(uiSour, uiDest);
	//save data add here
 	makeConfigData();
 	FlashDriver.SaveData();
	return currentSn;
}


uint32 CTSCrossConnectionManager::DeleteOneTSXCConnect(uint32 n) {
	it = cc.find(n);
	if( it != cc.end() ) {
		uint32 west = it->second->GetWestUID();
		uint32 east = it->second->GetEastUID();
		CTSChannel::getTSChannelByUid(west)->setMapPartner(0);
		CTSChannel::getTSChannelByUid(east)->setMapPartner(0);

		uint8 westST,westTS,eastST,eastTS;
		try {
			uint8 slot = UID::breakUID(west).ts.slot;
			if( slot == 100 ) {
				westST = UID::breakUID(west).ts.E1;
				westTS = UID::breakUID(west).ts.TS;
			}
			else {
				westST = CIsap100HardwareDesc::slot_stbus_map[slot-1];
				westTS = UID::breakUID(west).ts.TS;
			}

			slot = UID::breakUID(east).ts.slot;
			if( slot == 100 ) {
				eastST = UID::breakUID(east).ts.E1;
				eastTS = UID::breakUID(east).ts.TS;
			}
			else {
				eastST = CIsap100HardwareDesc::slot_stbus_map[slot-1];
				eastTS = UID::breakUID(east).ts.TS;
			}
		}
		catch(...) {
			return 0;
		}

		RemoveCrossConnection(westST, westTS);
		RemoveCrossConnection(eastST, eastTS);
		cc.erase(it);
		//save data add here
 		makeConfigData();
 		FlashDriver.SaveData();
		return n;
	}
	return 0;
}


int CTSCrossConnectionManager::GetFirstSnOfConnection(void) {
	if( cc.empty() ) {
		return 0;
	}
	it = cc.begin();
	return it->first;
}
int CTSCrossConnectionManager::GetNextSnConnection(int iStartSn) {
	it = cc.find(iStartSn);
	if( it != cc.end() ) {
		if( ++it != cc.end() ) {
			return it->first;
		}
	}
	return 0;
}


uint32 CTSCrossConnectionManager::GetXcName(uint32 uiXcUID, MyString& name) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		name.assign(it->second->GetName());
		return 0x5A;
	}
	return 0;
}
uint32 CTSCrossConnectionManager::GetXcDescription(uint32 uiXcUID, MyString& desc) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		desc.assign(it->second->GetDescription());
		return 0x5A;
	}
	return 0;
}
uint32 CTSCrossConnectionManager::SetXcName(uint32 uiXcUID, MyString& name) {
	if( SetXcName_start(uiXcUID, name) != 0 ) {
		//save data add here
 		makeConfigData();
 		FlashDriver.SaveData();
		return 0x5A;
	}
	return 0;
}
uint32 CTSCrossConnectionManager::SetXcName_start(uint32 uiXcUID, MyString& name) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		it->second->SetName(name);
		return 1;
	}
	return 0;
}
uint32 CTSCrossConnectionManager::SetXcDescription(uint32 uiXcUID, MyString& desc) {
	if( SetXcDescription_start(uiXcUID, desc) != 0 ) {
		//save data add here
 		makeConfigData();
 		FlashDriver.SaveData();
		return 0x5A;
	}
	return 0;
}
uint32 CTSCrossConnectionManager::SetXcDescription_start(uint32 uiXcUID, MyString& desc) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		it->second->SetDescription(desc);
		return 1;
	}
	return 0;
}

uint32 CTSCrossConnectionManager::GetWestID(uint32 uiNodeUID) {
	it = cc.find(uiNodeUID);
	if( it != cc.end() ) {
		return it->second->GetWestUID();
	}
	return 0;
}
uint32 CTSCrossConnectionManager::GetEastID(uint32 uiNodeUID) {
	it = cc.find(uiNodeUID);
	if( it != cc.end() ) {
		return it->second->GetEastUID();
	}
	return 0;
}

void CTSCrossConnectionManager::makeConfigData(void) {
	it = cc.begin();
	int i = 0;
	while( it != cc.end() ) {
		storeData.ccdata[i].west = it->second->GetWestUID();
		storeData.ccdata[i].east = it->second->GetEastUID();
		strcpy( (char*)storeData.ccdata[i].name, it->second->GetName().c_str() );
		strcpy( (char*)storeData.ccdata[i].desc, it->second->GetDescription().c_str() );
		it++;
		i++;
	}
	storeData.size = i;
}

void CTSCrossConnectionManager::RestoreDefaultConfig(void) {
	storeData.size = 0;
//	uint32 e1 = CE1Channel::GetFirstE1Uid();
//	uint32 vc12 = CSTM::GetFirstVC12Uid();
//	for( int i = 0; i < 20; i++ ) {
//		storeData.ccdata[i].west = e1;
//		storeData.ccdata[i].east = vc12;
//		e1 = CE1Channel::GetNextE1Uid(e1);
//		vc12 = CSTM::GetNextVC12Uid(vc12);
//	}
//	FlashDriver.SaveData();
}

uint32 CTSCrossConnectionManager::GetCurrentMappingNumber(void) {
	return cc.size();
}

