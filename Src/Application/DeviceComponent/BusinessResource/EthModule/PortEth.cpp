/*
 * PortEth.cpp
 *
 *  Created on: 2014-4-4
 *      Author: Administrator
 */

#include "PortEth.h"
#include "CPPTools.h"
#include "UID.h"
#include "EthBoard.h"
#include "CSwitchBaseImpl.h"
#include "CErrorValueDefine.h"
#include <string.h>

std::map<uint32, PortEth*> PortEth::group;

PortEth::PortEth(uint32 uid, uint8 chip, uint8 portsn, UETH_Config_Data_T* cfg, CMSSave* save, EthBoard* b) : RealPortBase(uid) {

	group.insert(std::pair<uint32, PortEth*>(uid,this));
	UN_Info info = UID::breakUID(uid);
	name = "ETH-Port-" + CPPTools::number2string(info.FE.port+1);
	ConfigData = cfg;
	chipID = chip;
	portID = portsn;
	board = b;
	storer = save;
	setEnable(ConfigData->enable, false);
	if( ConfigData->enable != 0 ) {
		setAuto(ConfigData->autoAN, false);
		setPause(ConfigData->pause, false);
	//	setLinktype(ConfigData->linkType, false);
	//	setPVID(ConfigData->pvid, false);
	//	if( getLinktype() == 2 ) {
	//		for (int i = 0; i < ConfigData->evidNumber; ++i) {
	//			addEVID(ConfigData->evid[i]);
	//		}
	//	}
	}
}

PortEth::~PortEth() {
	// TODO Auto-generated destructor stub
}

std::string& PortEth::getName(void) {
	return name;

}


bool PortEth::setEnable(uint8 en, bool save ) {

	board->getSwitch(chipID)->SetPortPowerDown(portID, en^1);
	if( save ) {
		ConfigData->enable = en;
		return storer->SaveData();
	}
	return true;
}

bool PortEth::setSpeed(uint8 speed, bool save ) {

	stPortEthernetPHY stpPHYMode = {0};
	stpPHYMode.ucANEnabled = ConfigData->autoAN;
	stpPHYMode.ucLinkSpeed = speed;
	stpPHYMode.ucFullDuplex = ConfigData->duplex;
	stpPHYMode.ucCapability = 1;
	board->getSwitch(chipID)->SetEthernetPHY(portID, &stpPHYMode);
	if( save ) {
		ConfigData->speed = speed;
		return storer->SaveData();
	}
	return true;
}
bool PortEth::setDuplex(uint8 dup, bool save ) {
	stPortEthernetPHY stpPHYMode = {0};
	stpPHYMode.ucANEnabled = ConfigData->autoAN;
	stpPHYMode.ucLinkSpeed = ConfigData->speed;
	stpPHYMode.ucFullDuplex = dup;
	stpPHYMode.ucCapability = 1;
	board->getSwitch(chipID)->SetEthernetPHY(portID, &stpPHYMode);
	if( save ) {
		ConfigData->duplex = dup;
		return storer->SaveData();
	}
	return true;
}
bool PortEth::setPause(uint8 en, bool save ) {
	if( board->getSwitch(chipID)->SetSwitchFlowControl(portID, en)
			== CErrorValueDefine::uiConstReturnSuccess ) {
		if( save ) {
			ConfigData->pause = en;
			return storer->SaveData();
		}
		return true;
	}
	return false;
}
bool PortEth::setAuto(uint8 at, bool save ) {
	stPortEthernetPHY stpPHYMode = {0};
	stpPHYMode.ucANEnabled = at;
	stpPHYMode.ucLinkSpeed = ConfigData->speed;
	stpPHYMode.ucFullDuplex = ConfigData->duplex;
	stpPHYMode.ucCapability = 1;
	if( board->getSwitch(chipID)->SetEthernetPHY(portID, &stpPHYMode)
			== CErrorValueDefine::uiConstReturnSuccess ) {
		if( save ) {
			ConfigData->autoAN = at;
			return storer->SaveData();
		}
		return true;
	}
	return false;
}
bool PortEth::setDescription(uint8* desc, uint32 len, bool save ) {
	ConfigData->dlen = len;
	memcpy(ConfigData->desc, desc, len);
	return storer->SaveData();
}
bool PortEth::setLinktype(uint8 type, bool save ) {
	if( type == ConfigData->linkType ) {
		return true;
	}
	if( type == 1 ) {
		for(int i = 0; i < ConfigData->evidNumber; i++) {
			board->getSwitch(chipID)->DeletePortMemberFromVLANGroup(ConfigData->evid[i],portID);
			ConfigData->evid[i]	= 0;
		}
		board->getSwitch(chipID)->SetPortAcceptFrameType(portID,3);  //只允许不带Tag的通过
	}else if( type == 2 ) {
		board->getSwitch(chipID)->SetPortAcceptFrameType(portID,1);  //带Tag和不带Tag都允许通过
	}
	if( save ) {
		ConfigData->linkType = type;
		return storer->SaveData();
	}
	return true;

}
bool PortEth::setPVID(uint16 vid, bool save ) {
	if( vid == ConfigData->pvid ) {
		return true;
	}
	board->getSwitch(chipID)->DeletePortMemberFromVLANGroup(ConfigData->pvid,portID);	  	//从原vlan组中移除port
	board->getSwitch(chipID)->AddPortMemberToVLANGroup(vid, portID);						//加入到新VLAN组
	board->getSwitch(chipID)->SetPortVID(portID, vid);										//设置PVID
	board->getSwitch(chipID)->SetVLANTaggingMode(vid, portID,CSwitchBaseImpl::uiConstTaggingModeRemove);	//只移除TAG

	if( save ) {
		ConfigData->pvid = vid;
		return storer->SaveData();
	}
	return true;
}
bool PortEth::addEVID(uint16 vid, bool save ) {
	if( ConfigData->evidNumber < 15) {
		board->getSwitch(chipID)->AddPortMemberToVLANGroup(vid,portID);			//将port加入到已知vlan组中
		board->getSwitch(chipID)->SetVLANTaggingMode(vid,portID,CSwitchBaseImpl::uiConstTaggingModeInsert);  //设置端口Tag模式	只插入不移除
		if( save ) {
			ConfigData->evid[ConfigData->evidNumber] = vid;
			ConfigData->evidNumber++;
			return storer->SaveData();
		}
		return true;
	}
	return false;
}
bool PortEth::removeEVID(uint16 vid, bool save ) {
	for(int i = 0; i < ConfigData->evidNumber; i++) {
		if(ConfigData->evid[i] == vid) {
			board->getSwitch(chipID)->DeletePortMemberFromVLANGroup(ConfigData->evid[i],portID);	  //	从vlan组中移除port
			if(save) {
				for(int j = i; j < ConfigData->evidNumber; j++) {
					if(j == 14) {
						ConfigData->evid[j] = 0;
					}
					else {
						ConfigData->evid[j] = ConfigData->evid[j+1];
					}
				}
				ConfigData->evidNumber--;
				return storer->SaveData();
			}
			return true;
		}
	}
	return false;
}



uint32 PortEth::getTxCounter() {
	uint32 v;
	board->getSwitch(chipID)->GetTxCounter(portID, &v);
	return v;
}
uint32 PortEth::getRxCounter() {
	uint32 v;
	board->getSwitch(chipID)->GetRxCounter(portID, &v);
	return v;
}
uint32 PortEth::getRxDropCounter() {
	uint32 v;
	board->getSwitch(chipID)->GetDropCounter(portID, &v);
	return v;
}
uint32 PortEth::getRxCRCerrCounter() {
	uint32 v;
	board->getSwitch(chipID)->getCrcErrorCounterNoClear(portID, &v);
	return v;
}





