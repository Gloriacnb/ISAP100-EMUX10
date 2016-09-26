/*
 * CUnframeE1.cpp
 *
 *  Created on: 2013-2-23
 *      Author: Administrator
 */

#include "CUnframeE1.h"
#include <string.h>
#include <sstream>
#include "Mid_RC7880A1App.h"
#include "CMSSave.h"
#include "UID.h"
#include "AlarmUnframeE1site.h"
#include "CE1Channel.h"
#include <rtl.h>

std::map<uint32, CUnframeE1*> CUnframeE1::UE1_group;
std::map<uint32, CUnframeE1*>::iterator CUnframeE1::it;


CUnframeE1::CUnframeE1(int lid, int sn, uint32 uid, UE1_Config_Data_T* config, CMSSave* save) : RealPortBase(uid){
	logicID = lid;
	std::ostringstream os;
	os << "Slot-" << lid/4 + 1 << "-E1-" << lid%4 + 1;
	name = os.str();
	configData = config;
	storer = save;


	for( int i = 0; i < E1_type_size; i++ ) {
		configData->alarm_property[i].typeID = E1_type_base+i;
		AlarmElement* ap = new AlarmUnframeE1site(&configData->alarm_property[i], this, (UE1_alarm_type_E)i);
		mapAlarm.insert( std::pair<uint32, AlarmElement*>( E1_type_base+i, ap ) );
	}
	tsk_lock();////////////////////
	UE1_group.insert( std::pair<uint32, CUnframeE1*>(uid, this) );
	linkChannel = CE1Channel::getE1(uid);
	linkChannel->setActive(true);
	tsk_unlock();//////////////////
}

CUnframeE1::~CUnframeE1() {
	linkChannel->setActive(false);
	std::map<uint32, AlarmElement*>::iterator it = mapAlarm.begin();
	tsk_lock();////////////////////
	ST_E1 info = {logicID/4+1, logicID%4};
	uint32 uid = UID::makeUID(&info);
	UE1_group.erase(uid);
	uint32 size = UE1_group.size();
	tsk_unlock();////////////////////
	while( it != mapAlarm.end() ) {
		delete (AlarmUnframeE1site*)((*it).second);
		it++;
	}
	mapAlarm.clear();
}


int CUnframeE1::setEnable(uint8 en) {

	if( en  == 1 ) {
		UN_Info info = {0};
		try {
			info = UID::breakUID( linkChannel->GetMapPartner() );
		}
		catch(...) {
			return -1;
		}

		RC7880Tu12UnitTsSelectWrite(linkChannel->hid(), info.vc12.lp);
	}
	else {
		RC7880Tu12UnitTsSelectWrite(linkChannel->hid(), 63);
	}
	configData->enable = en;
	if( storer->SaveData() ) {
		return 1;
	}
	return -1;

}
int CUnframeE1::setDescription(char* desc, uint8 len) {
	if( desc == 0 || strlen(desc) > 31 ) {
		return -1;
	}
	memcpy( configData->desc, desc, len);
	configData->dlen = len;
	return 1;
}

AlarmElement* CUnframeE1::getAlarmObject(uint32 typeID) {
	std::map<uint32, AlarmElement*>::iterator almit;
	almit = mapAlarm.find(typeID);
//	bool rtn;
	if( almit != mapAlarm.end() ) {
		return (*almit).second;
	}
	return 0;
}

bool CUnframeE1::setAlarmProperty(uint32 typeID, uint8* newVl) {
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

int CUnframeE1::getAlarmName(uint32 almType, char* name) {
	switch( almType-E1_type_base ) {
	case E1_LOS:
		strcpy(name, "E1_LOS");
		break;
	case E1_AIS:
		strcpy(name, "E1_AIS");
		break;
	default:
		return -1;
	}
	return 1;
}


bool CUnframeE1::ifE1Alarm(UE1_alarm_type_E sn) {
	uint8 e1los;
	uint8 stbais;
	uint8 temp;
	if ( getEnable() == 0 ) {
		return false;
	}
	RC7880DrvTU12UnitAlarmRead(linkChannel->hid(), &e1los, &stbais, &temp);
	switch( sn ) {
	case E1_LOS:
		return (e1los & 0x80) != 0;
	case E1_AIS:
		return (stbais & 0x80) != 0;
	default:
		break;
	}
	return false;

}


void CUnframeE1::processAlarm(void) {
	std::map<uint32, AlarmElement*>::iterator t = mapAlarm.begin();
	while( t != mapAlarm.end() ) {
		t->second->Run();
		t++;
	}
}


int CUnframeE1::setLoop(const int type) {
	switch( type ) {
	case dev_and_line_loop:
		RC7880Tu12UnitTu12LoopWrite(linkChannel->hid(), 1, 1);
		break;
	case line_loop:
		RC7880Tu12UnitTu12LoopWrite(linkChannel->hid(), 1, 0);
		break;
	case dev_loop:
		RC7880Tu12UnitTu12LoopWrite(linkChannel->hid(), 0, 1);
		break;
	case no_loop:
		RC7880Tu12UnitTu12LoopWrite(linkChannel->hid(), 0, 0);
		break;
	default:
		return -1;
	}
	return 0x5A;
}
