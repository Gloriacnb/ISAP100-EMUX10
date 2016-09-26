/*
 * CUpE1Port.cpp
 *
 *  Created on: 2014-4-10
 *      Author: Administrator
 */

#include "CUpE1Port.h"
#include "ChipSlotLogic.h"
#include "UID.h"
#include "CPPTools.h"
#include "CMSSave.h"
#include "SwitchPortInner.h"
#include <string.h>
#include "MidoptDCC.h"
#include <rtl.h>
#include "AlarmUpE1Port.h"

extern void insert_dcc_list(DCC_FRAME frame);
extern OS_TID t_dcc_rcv;

std::map<uint32, CUpE1Port*> CUpE1Port::NMPortMap;

CUpE1Port::CUpE1Port(uint32 uid, uint8 chid, UPE1_Config_Data_T* cfg, CMSSave* save) : RealPortBase(uid) {
	// TODO Auto-generated constructor stub
	NMPortMap.insert(std::pair<uint32, CUpE1Port*>(uid, this));
	hid = chid;
	UN_Info info = UID::breakUID(uid);

	name = "E1-"+CPPTools::number2string(info.E1.E1+1);
	ConfigData = cfg;
	storer = save;
	DcnWorking = true;

	for( int i = 0; i < UPE1_type_size; i++ ) {
		ConfigData->alarm_property[i].typeID = UPE1_type_base+i;
		AlarmElement* ap = new AlarmUpE1Port(&ConfigData->alarm_property[i], this, (UPE1_alarm_type_E)i);
		mapAlarm.insert( std::pair<uint32, AlarmElement*>( UPE1_type_base+i, ap ) );
	}

	ST_NM_Channel nminfo;
	nminfo.slot = info.E1.slot;
	nminfo.sn = info.E1.E1;
	nminfo.subtype = subtype_tsdcn;
	dcnsnd = new UpE1DCNChannelSnd(UID::makeUID(&nminfo), this);
	dcnrcv = new UpE1DCNChannelRcv(UID::makeUID(&nminfo));

	nminfo.subtype = subtype_sabit;
	dccsnd = new UpE1SabitChannelSnd(UID::makeUID(&nminfo), this);
	dccrcv = new UpE1SabitChannelRcv(UID::makeUID(&nminfo));

    //�ڴ˻ָ����ã������뵽������
    setType(ConfigData->nmcfg.type, false);
    if( ConfigData->nmcfg.type == 0 ) {
        //sabit dcc
    }
    else {
        //dcn
    	setTsMap(ConfigData->nmcfg.dcnCH.bitMap>>1, false);
    }
    setTopoDirection(ConfigData->nmcfg.topodir, false);
    setEnable(ConfigData->nmcfg.porten, false);
}

CUpE1Port::~CUpE1Port() {
	// TODO Auto-generated destructor stub
}

int CUpE1Port::setLoop(const int type) {
	switch( type ) {
	case dev_and_line_loop:
		setLoopout(hid, 1);
		setLoopin(hid, 1);
		break;
	case line_loop:
		setLoopout(hid, 1);
		setLoopin(hid, 0);
		break;
	case dev_loop:
		setLoopout(hid, 0);
		setLoopin(hid, 1);
		break;
	case no_loop:
		setLoopout(hid, 0);
		setLoopin(hid, 0);
		break;
	default:
		return -1;
	}
	return 0x5A;
}


AlarmElement* CUpE1Port::getAlarmObject(uint32 typeID) {
	std::map<uint32, AlarmElement*>::iterator almit;
	almit = mapAlarm.find(typeID);
//	bool rtn;
	if( almit != mapAlarm.end() ) {
		return (*almit).second;
	}
	return 0;
}

bool CUpE1Port::setAlarmProperty(uint32 typeID, uint8* newVl) {
	std::map<uint32, AlarmElement*>::iterator almit;
	almit = mapAlarm.find(typeID);
	bool rtn1, rtn2, rtn3;
	if( almit != mapAlarm.end() ) {
		rtn1 =(*almit).second->ChangePropertyLevel( (Alarm_level_E)newVl[0] );
		rtn2 = (*almit).second->ChangePropertyTrap(newVl[1]);
		rtn3 = (*almit).second->ChangePropertyMask(newVl[2]);
	}
	if( rtn1 && rtn2 && rtn3 ) {
		return storer->SaveData();
	}
	return false;
}

int CUpE1Port::getAlarmName(uint32 almType, char* name) {
	switch( almType-UPE1_type_base ) {
	case UPE1_LOS:
		strcpy(name, "E1_LOS");
		break;
	case UPE1_AIS:
		strcpy(name, "E1_AIS");
		break;
	case UPE1_LOF:
		strcpy(name, "E1_LOF");
		break;
//	case UPE1_LOM:
//		strcpy(name, "E1_LOM");
//		break;
	default:
		return -1;
	}
	return 1;
}

bool CUpE1Port::ifE1Alarm(UPE1_alarm_type_E sn) {
	switch( sn ) {
	case UPE1_LOS:
		return !do_upe1_alarm_wrk(hid);
	case UPE1_AIS:
		return do_upe1_alarm_ais(hid);
	case UPE1_LOF:
		return do_upe1_alarm_lof(hid) == 0;
//	case UPE1_LOM:
//		return do_upe1_alarm_lom(hid);
	default:
		break;
	}
	return false;
}

void CUpE1Port::processAlarm(void) {
	std::map<uint32, AlarmElement*>::iterator t = mapAlarm.begin();
	while( t != mapAlarm.end() ) {
		t->second->Run();
		t++;
	}
}

uint8 CUpE1Port::getEnable(void) {
	return ConfigData->nmcfg.porten;
}
bool CUpE1Port::setEnable(uint8 en, bool save) {
    if( en ) {
        if( DcnWorking ) {
        	setDcnInterruptEnable(hid, en);
        	setDccInterruptEnable(hid, 0);
        }
        else {
        	setDcnInterruptEnable(hid, 0);
        	setDccInterruptEnable(hid, en);
        }
    }
    else {
    	setDcnInterruptEnable(hid, 0);
    	setDccInterruptEnable(hid, 0);
    }
    if( save ) {
        ConfigData->nmcfg.porten = en;
        return storer->SaveData();
    }
    else {
        return true;
    }
    return false;
}

uint8 CUpE1Port::getType(void) {
	return ConfigData->nmcfg.type;
}

bool CUpE1Port::setType(uint8 ntype, bool save) {
	if( DcnWorking ) {
		setDcnInterruptEnable(hid, 1);
    	setDccInterruptEnable(hid, 0);
	}
	else {
		setDcnInterruptEnable(hid, 0);
    	setDccInterruptEnable(hid, 1);
	}
	if( ntype == 1 ) {
		DcnWorking = true;
	}
	else {
		DcnWorking = false;
		setTsMap(0, false);
	}
	if( save ) {
		ConfigData->nmcfg.type = ntype;
		return storer->SaveData();
	}
	return true;
}
uint32 CUpE1Port::getTopoDirection(void) {
	if( DcnWorking ) {
		return dcnrcv->getInnerPort()->getPortSn();
	}
	return dccrcv->getInnerPort()->getPortSn();
}

bool CUpE1Port::setTopoDirection(uint32 dir, bool save) {
	return false;
}

std::string CUpE1Port::getTsInfo(void) {
    uint32 bitmap = ConfigData->nmcfg.dcnCH.bitMap;
    std::string rtn;
    for (int i = 0; i < 32; ++i) {
        uint8 bitval = (bitmap >> i) & 1;
        if( bitval == 1 ) {
            rtn = rtn + CPPTools::number2string(i) + ",";
        }
    }
    return rtn;
}
bool CUpE1Port::addNMTs(uint32 tsuid, bool save) {
	return true;
}
bool CUpE1Port::deleteNMTs(uint32 tsuid, bool save) {
	return true;
}
uint8* CUpE1Port::getPortDescription(uint8* len) {
	*len = ConfigData->nmcfg.descLen;
	return ConfigData->nmcfg.desc;
}
bool CUpE1Port::setPortDescription(uint8* d, uint8 len, bool save) {
	if( save ) {
		ConfigData->nmcfg.descLen = len;
		memcpy( ConfigData->nmcfg.desc, d, len );
		return storer->SaveData();
	}
	return true;
}
uint32 CUpE1Port::getTsMap(void) {
	return ConfigData->nmcfg.dcnCH.bitMap >> 1;
}
bool CUpE1Port::setTsMap(uint32 map, bool save) {

//    if( !DcnWorking ) {
//        return false;
//    }
//    if( ((map<<1) == ConfigData->nmcfg.dcnCH.bitMap) && save ) {
//        return true;
//    }
    selectDcnTs(hid, map << 1 );
	if( save ) {
		ConfigData->nmcfg.dcnCH.bitMap = (map << 1);
		return storer->SaveData();
	}
    return false;
}


bool CUpE1Port::receivData(void) {
	LAYER2FRAME *frame = 0;
	DCC_FRAME df;
	bool flagok = false;
	if( DcnWorking ) {
		while( ifDcnHavePacket(hid) ) {
		 	uint16 pkgLen = getDcnPacketLen(hid);
		 	if( pkgLen > DEF_DCN_MTU ) {
		 		readDcnPacketOver(hid);
		 		continue;
		 	}
		 	frame = alloc_Eth_mem (pkgLen);
		 	/* if 'alloc_mem()' has failed, ignore this packet. */
		 	if (frame != NULL ) {
		 		uint8* dp = frame->frame;
		 		getDcnPacket(hid, dp, pkgLen);
				df.chuid = dcnrcv->getUID();
				df.frame = frame;
				insert_dcc_list(df);
				flagok = true;
		 	}
		 	else {
		 		readDcnPacketOver(hid);
		 	}
		}
	}
	else {
		while( ifSabitHavePacket(hid) ) {
		 	uint16 pkgLen = getSabitPacketLen(hid);
		 	if( pkgLen > DEF_DCC_MTU || pkgLen < 4 ) {
		 		readSabitPacketOver(hid);
		 		continue;
		 	}
		 	frame = alloc_Eth_mem (pkgLen);
		 	/* if 'alloc_mem()' has failed, ignore this packet. */
		 	if (frame != NULL ) {
		 		uint8* dp = frame->frame;
		 		getSabitPacket(hid, dp, pkgLen);
				df.chuid = dccrcv->getUID();
				df.frame = frame;
				insert_dcc_list(df);
				flagok = true;
		 	}
			readSabitPacketOver(hid);
		}
	}
	if( flagok ) {
		isr_evt_set(0x0001, t_dcc_rcv);
		return true;
	}
	return false;
}
