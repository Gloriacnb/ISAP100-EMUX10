/*
 * CVC12CrossConnectionMagager.cpp
 *
 *  Created on: 2013-2-25
 *      Author: Administrator
 */

#include "CVC12CrossConnectionMagager.h"
#include "CVC12.h"
#include "Mid_RC7880A1App.h"
#include "CCrossConnection.h"
#include "CSTM.h"
#include "CE1Channel.h"
#include <string.h>
#include "UID.h"
#include "DeviceLocal.h"
#include "SDHGroup.h"

int CVC12CrossConnectionMagager::currentSn = 0;

CVC12CrossConnectionMagager::CVC12CrossConnectionMagager() {
	// TODO Auto-generated constructor stub
	storeInfo.BlockFirst	= SYS_Vc12_Cross_Block_Start;
	storeInfo.BufAddr 		= (uint32)&storeData;
	storeInfo.ByteNums		= sizeof(storeData);

	FlashDriver.setInfo(storeInfo);
	if( !FlashDriver.ReadData() ) {
		//default config
		RestoreDefaultConfig();
	}
	for( int i = 0; i < storeData.size; i++ ) {
		uint32 ccid = CreatConnection_start(storeData.ccdata[i].E1, storeData.ccdata[i].VC12);
		std::string name((const char*)storeData.ccdata[i].name);
		SetXcName_start(ccid, name);
		std::string desc((const char*)storeData.ccdata[i].desc);
		SetXcDescription_start(ccid, desc);

		uint8 portBack = DeviceLocal::instance().GetSdhObject().getPortBackup();
		if( portBack == 0 ) {
			setXcSncp_start(ccid, storeData.ccdata[i].sncp);
		}
	}

}

CVC12CrossConnectionMagager::~CVC12CrossConnectionMagager() {
	// TODO Auto-generated destructor stub
}


uint32 CVC12CrossConnectionMagager::CreatConnection_start(uint32 uiSour, uint32 uiDest) {
	CE1Channel* pE1 = CE1Channel::getE1(uiSour);
	CVC12* pvc12 = CSTM::GetVc12Object(uiDest);
	if( pE1 == 0 || pvc12 == 0 ) {
		return 0;
	}
	if( pE1->ifOccupied() || pvc12->ifOccupied() ) {
		return 0;
	}
	pvc12->occupyIt(uiSour);
	pE1->occupyIt(uiDest);
	RC7880Vc4UnitDxcConfigWrite(pvc12->GetHid(), direct_GH); //总线方向
	RC7880Tu12UnitTsSelectWrite(pE1->hid(), pvc12->GetHid()); //建立映射

	uint8 bus = 0;
	UN_Info info = UID::breakUID(pvc12->getUID());

	if( info.stm.stm == 0 ) {
		bus = VC4ID_A;
	}
	else {
		bus = VC4ID_B;
	}
	RC7880Tu12UnitBusConfigWrite(pE1->hid(), bus);
	++currentSn;
	cc.insert(
			std::pair<int, CCrossConnection*>
	(currentSn, new CCrossConnection(currentSn,uiSour, uiDest)));
	return currentSn;
}

uint32 CVC12CrossConnectionMagager::CreatConnection(uint32 uiSour, uint32 uiDest) {
	CreatConnection_start(uiSour, uiDest);
	//save data add here
 	makeConfigData();
 	FlashDriver.SaveData();
	return currentSn;
}
uint32 CVC12CrossConnectionMagager::DeleteOneE1XCConnect(uint32 n) {
	it = cc.find(n);
	if( it != cc.end() ) {
		uint32 e1 = it->second->GetWestUID();
		uint32 vc12 = it->second->GetEastUID();
		CE1Channel* pE1 = CE1Channel::getE1(e1);
		CVC12* pvc12 = CSTM::GetVc12Object(vc12);
		if( pE1 == 0 || pvc12 == 0 ) {
			return 0;
		}
		if( pE1->ifOccupied() && pvc12->ifOccupied() ) {
			pvc12->occupyIt(0);
			pE1->occupyIt(0);
		}

		/*
		 * 增加对当前vc12的同编号vc12连接情况的判断
		 * 只有当同编号vc12未占用时，才将空分交叉设置为bypass
		 */
		uint32 Partner = pvc12->getPartnerUID();
		CVC12* partnervc12 = CSTM::GetVc12Object(Partner);
		if( partnervc12 == 0 ) {
			return false;
		}
		if( !partnervc12->ifOccupied() ) {
			RC7880Vc4UnitDxcConfigWrite(pvc12->GetHid(), direct_AB);
		}
		RC7880Tu12UnitTsSelectWrite(pE1->hid(), mapping_Idle);

		setXcSncp_start(n,0); //删除映射的同时，解除SNCP
		cc.erase(it);
		//save data add here
 		makeConfigData();
 		FlashDriver.SaveData();
		return n;
	}
	return 0;
}
int CVC12CrossConnectionMagager::GetFirstSnOfConnection(void) {
	if( cc.empty() ) {
		return 0;
	}
	it = cc.begin();
	return it->first;
}
int CVC12CrossConnectionMagager::GetNextSnConnection(int iStartSn) {
	it = cc.find(iStartSn);
	if( it != cc.end() ) {
		if( ++it != cc.end() ) {
			return it->first;
		}
	}
	return 0;
}
uint32 CVC12CrossConnectionMagager::GetXcName(uint32 uiXcUID, MyString& name) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		name.assign(it->second->GetName());
		return 0x5A;
	}
	return 0;
}
uint32 CVC12CrossConnectionMagager::GetXcDescription(uint32 uiXcUID, MyString& desc) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		desc.assign(it->second->GetDescription());
		return 0x5A;
	}
	return 0;
}
uint32 CVC12CrossConnectionMagager::SetXcName(uint32 uiXcUID, MyString& name) {
	if( SetXcName_start(uiXcUID, name) != 0 ) {
		//save data add here
 		makeConfigData();
 		FlashDriver.SaveData();
		return 0x5A;
	}
	return 0;
}
uint32 CVC12CrossConnectionMagager::SetXcName_start(uint32 uiXcUID, MyString& name) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		it->second->SetName(name);
		return 1;
	}
	return 0;
}
uint32 CVC12CrossConnectionMagager::SetXcDescription(uint32 uiXcUID, MyString& desc) {
	if( SetXcDescription_start(uiXcUID, desc) != 0 ) {
		//save data add here
 		makeConfigData();
 		FlashDriver.SaveData();
		return 0x5A;
	}
	return 0;
}
uint32 CVC12CrossConnectionMagager::SetXcDescription_start(uint32 uiXcUID, MyString& desc) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		it->second->SetDescription(desc);
		return 1;
	}
	return 0;
}

uint32 CVC12CrossConnectionMagager::setXcSncp_start(uint32 uiXcUID, uint32 en) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		it->second->setSncp(en);
		uint8 protectMode = 0;
		if( en == 0 ) {
			protectMode = DISABLE_PROTECT;
		}
		else {
			protectMode = AUTO_PROTECT;
		}
		CE1Channel* pE1 = CE1Channel::getE1(GetCCE1ID(uiXcUID));
		RC7880Tu12UnitProtectModeWrite(pE1->hid(), protectMode);
	}
	return 1;
}


uint32 CVC12CrossConnectionMagager::GetCCE1ID(uint32 uiNodeUID) {
	it = cc.find(uiNodeUID);
	if( it != cc.end() ) {
		return it->second->GetWestUID();
	}
	return 0;
}
uint32 CVC12CrossConnectionMagager::GetCCVC12ID(uint32 uiNodeUID) {
	it = cc.find(uiNodeUID);
	if( it != cc.end() ) {
		return it->second->GetEastUID();
	}
	return 0;
}

uint32 CVC12CrossConnectionMagager::getXcSncp(uint32 uiXcUID) {
	it = cc.find(uiXcUID);
	if( it != cc.end() ) {
		return it->second->GetSNCP();
	}
	return 0xff;
}
uint32 CVC12CrossConnectionMagager::setXcSncp(uint32 uiXcUID, uint32 en) {
	setXcSncp_start(uiXcUID, en);
	makeConfigData();
	FlashDriver.SaveData();
	return 0x5A;
}


void CVC12CrossConnectionMagager::makeConfigData(void) {
	it = cc.begin();
	int i = 0;
	while( it != cc.end() ) {
		storeData.ccdata[i].E1 = it->second->GetWestUID();
		storeData.ccdata[i].VC12 = it->second->GetEastUID();
		strcpy( (char*)storeData.ccdata[i].name, it->second->GetName().c_str() );
		strcpy( (char*)storeData.ccdata[i].desc, it->second->GetDescription().c_str() );
		storeData.ccdata[i].sncp = it->second->GetSNCP();
		it++;
		i++;
	}
	storeData.size = i;
}

void CVC12CrossConnectionMagager::RestoreDefaultConfig(void) {
	storeData.size = 20;
	uint32 e1 = CE1Channel::GetFirstE1Uid();
	uint32 vc12 = CSTM::GetFirstVC12Uid();
	for( int i = 0; i < 20; i++ ) {
		storeData.ccdata[i].E1 = e1;
		storeData.ccdata[i].VC12 = vc12;
		memset(storeData.ccdata[i].desc, 0, 32);
		memset(storeData.ccdata[i].name, 0, 32);
		storeData.ccdata[i].sncp = 0;
		e1 = CE1Channel::GetNextE1Uid(e1);
		vc12 = CSTM::GetNextVC12Uid(vc12);
	}
	FlashDriver.SaveData();
}

uint32 CVC12CrossConnectionMagager::GetCurrentMappingNumber(void) {
	return cc.size();
}

