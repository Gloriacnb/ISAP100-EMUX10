/*
 * CNME1Port.cpp
 *
 *  Created on: 2015Äê12ÔÂ24ÈÕ
 *      Author: Administrator
 */

#include "CNME1Port.h"
#include "UID.h"
#include "rc7880RegDriverfuncLib.h"
#include "CPPTools.h"
#include "CNME1Port_define.h"
#include "AlarmNmPortE1Site.h"
#include "CMSSave.h"
#include <string.h>

std::map<uint32, CNME1Port*> CNME1Port::group;

CNME1Port::CNME1Port(uint32 uid, UFE1_Config_Data_T* d, CMSSave* save) : RealPortBase(uid) {

    group.insert( std::pair<uint32, CNME1Port*>(uid, this));
    UN_Info info = UID::breakUID(uid);

	name = "E1-"+CPPTools::number2string(info.E1.E1+1);
	e1sn = info.E1.E1 + 22;
	nmPortSn = info.E1.E1;
	configData = d;
	storer = save;
	for( int i = 0; i < FE1_type_size; i++ ) {
		configData->alarm_property[i].typeID = FE1_type_base+i;
		AlarmElement* ap = new AlarmNmPortE1Site(&configData->alarm_property[i], this, (UFE1_alarm_type_E)i);
		mapAlarm.insert( std::pair<uint32, AlarmElement*>( FE1_type_base+i, ap ) );
	}
	ST_NM_Channel nminfo;
	nminfo.slot = info.E1.slot;
	nminfo.sn = info.E1.E1;
	nminfo.subtype = subtype_dcn;
	uint32 nmuid = UID::makeUID(&nminfo);
	dcnr = new DCNXe1Rcv(nmuid);
	dcns = new DCNXe1Snd(nmuid, uid);
}

CNME1Port::~CNME1Port() {
	std::map<uint32, AlarmElement*>::iterator it = mapAlarm.begin();
	while( it != mapAlarm.end() ) {
		delete (AlarmNmPortE1Site*)((*it).second);
		it++;
	}
	mapAlarm.clear();
    group.erase(getUID());
}

int CNME1Port::setLoop(const int type) {
	switch( type ) {
	case dev_and_line_loop:
		RC7880Tu12UnitTu12LoopWrite(e1sn, 1, 1);
		break;
	case line_loop:
		RC7880Tu12UnitTu12LoopWrite(e1sn, 1, 0);
		break;
	case dev_loop:
		RC7880Tu12UnitTu12LoopWrite(e1sn, 0, 1);
		break;
	case no_loop:
		RC7880Tu12UnitTu12LoopWrite(e1sn, 0, 0);
		break;
	default:
		return -1;
	}
	return 0x5A;
}


AlarmElement* CNME1Port::getAlarmObject(uint32 typeID) {
	std::map<uint32, AlarmElement*>::iterator almit;
	almit = mapAlarm.find(typeID);
//	bool rtn;
	if( almit != mapAlarm.end() ) {
		return (*almit).second;
	}
	return 0;
}

bool CNME1Port::setAlarmProperty(uint32 typeID, uint8* newVl) {
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

int CNME1Port::getAlarmName(uint32 almType, char* name) {
	switch( almType-FE1_type_base ) {
	case FE1_LOS:
		strcpy(name, "E1_LOS");
		break;
	case FE1_AIS:
		strcpy(name, "E1_AIS");
		break;
	case FE1_LOF:
		strcpy(name, "E1_LOF");
		break;
	default:
		return -1;
	}
	return 1;
}

bool CNME1Port::ifE1Alarm(UFE1_alarm_type_E sn) {
	uint8 temp;
	RC7880EOWUnitXE1AlarmRead(&temp, nmPortSn);
	switch( sn ) {
	case FE1_LOS:
		return (temp & 0x80) != 0;
	case FE1_AIS:
		return (temp & 0x40) != 0;
	case FE1_LOF:
		return (temp & 0x20) != 0;
//	case FE1_LOMF:
//		return (temp & 0x10) != 0;
	default:
		break;
	}
	return false;
}

void CNME1Port::processAlarm(void) {
	std::map<uint32, AlarmElement*>::iterator t = mapAlarm.begin();
	while( t != mapAlarm.end() ) {
		t->second->Run();
		t++;
	}
}

uint8 CNME1Port::getEnable(void) {
	return configData->enable;
}
bool CNME1Port::setEnable(uint8 en, bool save) {
	if( save ) {
		configData->enable = en;
		return storer->SaveData();
	}
	return false;
}
uint8 CNME1Port::getMode(void) {
	return configData->mode;
}

bool CNME1Port::setMode(uint8 m, bool save) {
	if( save ) {
		configData->mode = m;
		return storer->SaveData();
	}
	return false;
}

uint8* CNME1Port::getDesc(uint32* len) {
	*len = configData->dlen;
	return configData->desc;
}

bool CNME1Port::setDesc(uint8* desc, uint8 len) {
	configData->dlen = len;
	memcpy( configData->desc, desc, len);
	return storer->SaveData();
}
