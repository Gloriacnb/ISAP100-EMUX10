/*
 * CSTM.cpp
 *
 *  Created on: 2013-2-26
 *      Author: Administrator
 */

#include <sstream>
#include "CSTM.h"
#include "CVC12.h"
#include "UID.h"
#include "AlarmMSSite.h"
#include "AlarmAUSite.h"
#include "AlarmHPSite.h"
#include "Mid_RC7880A1App.h"
#include "CPPTools.h"
#include "CMSSave.h"
#include <string.h>

std::map<uint32,CVC12*> CSTM::mapVc12;
std::map<uint32, CVC12*>::iterator CSTM::it;

const int VC12Number = 63;

CSTM::CSTM(uint32 stmuid,  STM_config_data* cfgData, CMSSave* stroer) : RealPortBase(stmuid) {

	int slot = UID::breakUID(stmuid).stm.slot;
	int sn = UID::breakUID(stmuid).stm.stm;
	configData = cfgData;
	name = "STM1-" + CPPTools::number2string(sn+1);
	Store = stroer;
	hardid = sn;

//	RC7880GlobalUnitAutoAlsEnableWrite(hardid, 1);
	if( cfgData->als == 0 )
		RC7880GlobalUnitAutoAlsEnableWrite(hardid, 0);
	else
		RC7880GlobalUnitAutoAlsEnableWrite(hardid, 1);

	setEnable(cfgData->enable, false);
	setJ0Transmit(cfgData->J0Transmit, cfgData->JTLen, false);

	ST_SDH_VC12 info = {slot, sn, 0, 0};
	for( int i = 0; i < VC12Number; i++ ) {
		info.lp = i;
		uint32 uid = UID::makeUID(&info);
		mapVc12.insert(
				std::pair<uint32, CVC12*>(
				uid,
				new CVC12(uid, &configData->vc12_data[i]))
				);
	}

	for( int i = MS_LOF; i < MS_type_size; i++ ) {
		configData->alarm_property[i].typeID = MS_type_base+i; //patch
		AlarmElement* ap = new AlarmMSSite(&configData->alarm_property[i], this, (MS_alarm_type_E)i);
		mapAlarm.insert( std::pair<uint32, AlarmElement*>( MS_type_base+i, ap ) );
	}
	for( int i = AU4_LOP; i < AU_type_size; i++ ) {
		configData->alarm_property[i+MS_type_size].typeID = AU_type_base+i; //patch
		AlarmElement* ap = new AlarmAUSite(&configData->alarm_property[i+MS_type_size], this, (AU_alarm_type_E)i);
		mapAlarm.insert( std::pair<uint32, AlarmElement*>( AU_type_base+i, ap ) );
	}
	for( int i = VC4_AIS; i < VC_type_size; i++ ) {
		configData->alarm_property[i+MS_type_size+AU_type_size].typeID = VC_type_base+i; //patch
		AlarmElement* ap = new AlarmHPSite(&configData->alarm_property[i+MS_type_size+AU_type_size], this, (VC_alarm_type_E)i);
		mapAlarm.insert( std::pair<uint32, AlarmElement*>( VC_type_base+i, ap ) );
	}
	ST_NM_Channel nminfo;
	nminfo.slot = slot;
	nminfo.subtype = subtype_dcc;
	nminfo.sn = sn;
	uint32 nmuid = UID::makeUID(&nminfo);
	dccr = new DCCSdhRcv(nmuid);
	dccs = new DCCSdhSnd(nmuid, stmuid);
}

CSTM::~CSTM() {
	// TODO Auto-generated destructor stub
}

CVC12* CSTM::GetVc12Object(uint32 uid) {
	it = mapVc12.find(uid);
	if( it != mapVc12.end() ) {
		return it->second;
	}
	return 0;

}


bool CSTM::ifMSAlarm(MS_alarm_type_E sn) {
	uint8 alm1;	//los,lof,lom,aulop,rstim,hpuneq,hptim hpplm
	uint8 alm2; //msexc,msdeg,hpexc,hpdeg,-,-,-,-
	uint8 alm3; //msais,auais,hpais,hprdi,msrdi,-,-,-
	RC7880DrvVC4UnitAlarmRead(hardid, &alm1, &alm2, &alm3);
	/*端口 禁止后无告警*/
	if ( getEnable() == 0 ) {
		return false;
	}
	uint8 status = 0;
	switch( sn ) {

	case MS_AIS:
		status = alm3 >> 7;
		break;
	case MS_BIP:
		//status = alm2 >> 7;
		break;
	case MS_DEG:
		status = alm2 >> 6;
		break;
	case MS_EXC:
		status = alm2 >> 7;
		break;
	case MS_LOF:
		status = alm1 >> 6;
		break;
	case MS_LOM:
		status = alm1 >> 5;
		break;
	case MS_LOS:
		status = alm1 >> 7;
		break;
	case MS_OOF:
		break;
	case MS_RDI:
		status = alm3 >> 3;
		break;
	}
	status &= 0x01;
	if( status == 0 ) {
		return false;
	}
	return true;
}
bool CSTM::ifAU4Alarm(AU_alarm_type_E sn) {
	/*端口 禁止后无告警*/
	if( configData->enable == 0 ) {
		return false;
	}
	uint8 alm1;	//los,lof,lom,aulop,rstim,hpuneq,hptim hpplm
	uint8 alm2; //msexc,msdeg,hpexc,hpdeg,-,-,-,-
	uint8 alm3; //msais,auais,hpais,hprdi,msrdi,-,-,-
	RC7880DrvVC4UnitAlarmRead(hardid, &alm1, &alm2, &alm3);

	uint8 status = 0;

	switch( sn ) {

	case AU4_AIS:
		status = alm3 >> 6;
		break;
	case AU4_LOP:
		status = alm1 >> 6;
		break;
	}

	status &= 0x01;
	if( status == 0 ) {
		return false;
	}
	return true;
}
bool CSTM::ifVC4Alarm(VC_alarm_type_E sn) {
	/*端口 禁止后无告警*/
	if( configData->enable == 0 ) {
		return false;
	}
	uint8 alm1;	//los,lof,lom,aulop,rstim,hpuneq,hptim hpplm
	uint8 alm2; //msexc,msdeg,hpexc,hpdeg,-,-,-,-
	uint8 alm3; //msais,auais,hpais,hprdi,msrdi,-,-,-
	uint8 status = 0;
	RC7880DrvVC4UnitAlarmRead(hardid, &alm1, &alm2, &alm3);
	switch( sn ) {

	case VC4_AIS:
		status = alm3 >> 5;
		break;
	case VC4_BIP:
		//status = alm2 >> 5;
		break;
	case VC4_DEG:
		status = alm2 >> 4;
		break;
	case VC4_EXC:
		status = alm2 >> 5;
		break;
	case VC4_LOM:
		status = alm1 >> 5;
		break;
	case VC4_OOM:
		RC7880DrvVC4UnitOOMAlarmRead(hardid, &alm1);
		status = alm1 >> 0;
		break;
	case VC4_RDI:
		status = alm3 >> 4;
		break;
	case VC4_REI:
		break;
	case VC4_SLM:
		status = alm1 >> 0;
		break;
	case VC4_TIM:
		status = alm1 >> 1;
		break;
	case VC4_UNEQ:
		status = alm1 >> 2;
		break;
	}

	status &= 0x01;
	if( status == 0 ) {
		return false;
	}
	return true;
}

bool CSTM::setAlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl) {
	std::map<uint32, AlarmElement*>::iterator almit;
	almit = mapAlarm.find(typeID);
	bool rtn;
	if( almit != mapAlarm.end() ) {
		switch( opt ) {
		case opt_level:
			rtn = (*almit).second->ChangePropertyLevel( (Alarm_level_E)newVl );
			break;
		case opt_trap:
			rtn = (*almit).second->ChangePropertyTrap(newVl);
			break;
		case opt_mask:
			rtn = (*almit).second->ChangePropertyMask(newVl);
			break;
		default:
			return false;
		}
	}
	if( rtn ) {
		return Store->SaveData();
	}
	return rtn;
}

bool CSTM::setAlarmProperty(uint32 typeID, uint8* newVl) {
	std::map<uint32, AlarmElement*>::iterator almit;
	almit = mapAlarm.find(typeID);
	bool rtn1, rtn2, rtn3;
	if( almit != mapAlarm.end() ) {
		rtn1 =(*almit).second->ChangePropertyLevel( (Alarm_level_E)newVl[0] );
		rtn2 = (*almit).second->ChangePropertyTrap(newVl[1]);
		rtn3 = (*almit).second->ChangePropertyMask(newVl[2]);
	}
	if( rtn1 && rtn2 && rtn3 ) {
		return Store->SaveData();
	}
	return false;
}

bool CSTM::setVC12AlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl) {
	it = mapVc12.begin();
	while( it != mapVc12.end() ) {
		(*it).second->setAlarmProperty(typeID, opt, newVl);
	}
	return true;
}

int CSTM::getAlarmName(uint32 almType, char* name) {

	if( (almType >= MS_type_base) && (almType < MS_type_size+MS_type_base) ) {
		return getSTMAlarmName(almType, name);
	}
	else if( (almType >= AU_type_base) && (almType < AU_type_size+AU_type_base) ) {
		return getAU4AlarmName(almType, name);
	}
	else if( (almType >= VC_type_base) && (almType < VC_type_size+VC_type_base) ) {
		return getVC4AlarmName(almType, name);
	}
	return -1;
}

AlarmElement* CSTM::getAlarmObject(uint32 typeID) {
	std::map<uint32, AlarmElement*>::iterator almit;
	almit = mapAlarm.find(typeID);
//	bool rtn;
	if( almit != mapAlarm.end() ) {
		return (*almit).second;
	}
	return 0;
}


void CSTM::setEnable(uint8 nvalue, bool save) {
	if( nvalue == 0 ) {
//		RC7880AU4UnitForceAUAISSendWrite(hardid, 1);
//		RC7880Vc4UnitForceMSAISSendWrite(hardid, 1);
		OpticalTXOff(hardid, 1);
	}
	else {
//		RC7880AU4UnitForceAUAISSendWrite(hardid, 0);
//		RC7880Vc4UnitForceMSAISSendWrite(hardid, 0);
		OpticalTXOff(hardid, 0);

	}
	if( save ) {
		configData->enable = nvalue;
		Store->SaveData();
	}
}

void CSTM::setAls(uint8 en) {
	OpticalAlsEnable(hardid,en);
	configData->als = en;
	Store->SaveData();
}


void CSTM::setDescription( uint8* desc, uint8 len) {
	configData->descLen = len;
	for( int i = 0; i < len; i++ ) {
		configData->desc[i] = desc[i];
	}
	Store->SaveData();
}

uint8* CSTM::getJ0Received(uint32* len) {
	//read from 7880A1
	static Vc4UnitOverHead_t oh;
	RC7880DrvVC4UnitRcvOverHeadRead(hardid, &oh);
	*len = 15;//strlen((char*)oh.nj0);
	return &oh.nj0[1];
}

void CSTM::setJ0Transmit(uint8* j0, uint8 len, bool save) {
	if( len < 16 ) {

		configData->JTLen = len;
		for( int i = 0; i < len; i++ ) {
			configData->J0Transmit[i] = j0[i];
		}
		configData->J0Transmit[len] = '\0';
		RC7880DrvVC4UnitJ0SendWrite16( hardid, j0, 1);

		if( save ) {
			Store->SaveData();
		}
	}
}
void CSTM::setJ0Expected(uint8* j0, uint8 len) {
	configData->JELen = len;
	for( int i = 0; i < len; i++ ) {
		configData->J0Expected[i] = j0[i];
	}
//	RC7880DrvVC4UnitExceptOverHeadWrite
	Store->SaveData();
}


void CSTM::processAlarm(void) {
	std::map<uint32, AlarmElement*>::iterator it = mapAlarm.begin();
	while( it != mapAlarm.end() ) {
		it->second->Run();
		it++;
	}
}


int CSTM::setLoop(const int type) {
	switch( type ) {
	case dev_and_line_loop:
		RC7880DrvVC4UnitLportLoopWrite(hardid, 1, 1);
		break;
	case dev_loop:
		RC7880DrvVC4UnitLportLoopWrite(hardid, 1, 0);
		break;
	case line_loop:
		RC7880DrvVC4UnitLportLoopWrite(hardid, 0, 1);
		break;
	case no_loop:
		RC7880DrvVC4UnitLportLoopWrite(hardid, 0, 0);
		break;
	default:
		return -1;
	}
	return 0x5A;
}

uint32 CSTM::getFirstAlarmType(void) {
	std::map<uint32, AlarmElement*>::iterator it = mapAlarm.begin();
	if( it != mapAlarm.end() ) {
		return it->first;
	}
	return 0;
}

uint32 CSTM::getNextAlarmType(uint32 sid) {

	std::map<uint32, AlarmElement*>::iterator it = mapAlarm.find(sid);
	if( it != mapAlarm.end() ) {
		++it;
		if( it != mapAlarm.end() ) {
			return it->first;
		}
	}
	return 0;
}

int CSTM::getSTMAlarmName(uint32 almType, char* name) {
	switch( almType-MS_type_base ) {
	case MS_LOF:
		strcpy(name, "MS_LOF");
		break;
	case MS_LOM:
		strcpy(name, "MS_LOM");
		break;
	case MS_LOS:
		strcpy(name, "MS_LOS");
		break;
	case MS_OOF:
		strcpy(name, "MS_OOF");
		break;
	case MS_AIS:
		strcpy(name, "MS_AIS");
		break;
	case MS_RDI:
		strcpy(name, "MS_RDI");
		break;
	case J0_TIM:
		strcpy(name, "J0_TIM");
		break;
	case B1_EXC:
		strcpy(name, "B1_EXC");
		break;
	case B2_EXC:
		strcpy(name, "B2_EXC");
		break;
	case RS_BIP:
		strcpy(name, "RS_BIP");
		break;
	case MS_BIP:
		strcpy(name, "MS_BIP");
		break;
	case MS_EXC:
		strcpy(name, "MS_EXC");
		break;
	case MS_DEG:
		strcpy(name, "MS_DEG");
		break;
	default:
		return -1;
	}
	return 1;
}
int CSTM::getVC4AlarmName(uint32 almType, char* name) {
	switch( almType-VC_type_base ) {
	case VC4_AIS:
		strcpy(name, "VC4_AIS");
		break;
	case VC4_UNEQ:
		strcpy(name, "VC4_UNEQ");
		break;
	case VC4_RDI:
		strcpy(name, "VC4_RDI");
		break;
	case VC4_SLM:
		strcpy(name, "VC4_SLM");
		break;
	case VC4_TIM:
		strcpy(name, "VC4_TIM");
		break;
	case VC4_LOM:
		strcpy(name, "VC4_LOM");
		break;
	case VC4_EXC:
		strcpy(name, "VC4_EXC");
		break;
	case VC4_REI:
		strcpy(name, "VC4_REI");
		break;
	case VC4_BIP:
		strcpy(name, "VC4_BIP");
		break;
	case VC4_OOM:
		strcpy(name, "VC4_OOM");
		break;
	case VC4_DEG:
		strcpy(name, "VC4_DEG");
		break;
	default:
		return -1;
	}
	return 1;

}
int CSTM::getAU4AlarmName(uint32 almType, char* name) {
	switch( almType-AU_type_base ) {
	case AU4_LOP:
		strcpy(name, "AU4_LOP");
		break;
	case AU4_AIS:
		strcpy(name, "AU4_AIS");
		break;
	default:
		return -1;
	}
	return 1;
}

