/*
 * CVCGMember.cpp
 *
 *  Created on: 2013-5-14
 *      Author: Administrator
 */

#include "CVCGMember.h"
#include "AlarmVCGMemberSite.h"
#include "CVCG_define.h"
#include "RC6400.h"
#include "CVC12.h"

CVCGMember::CVCGMember(CVC12* v, uint32 sn,  Alarm_property_T* p) {
	vc12 = v;
	itsSN = sn;
	for( int i = 0; i < Member_type_size; i++ ) {
		AlarmElement* ap = new AlarmVCGMemberSite(&p[VCG_type_size+i], this, (Member_alarm_type_E)i);
		mapAlarm.insert( std::pair<uint32, AlarmElement*>( VCG_type_base+i, ap ) );
	}
}

CVCGMember::~CVCGMember() {
	std::map<uint32, AlarmElement*>::iterator it = mapAlarm.begin();
	while( it != mapAlarm.end() ) {
		delete (AlarmVCGMemberSite*)it->second;
		it++;
	}
}


void CVCGMember::processAlarm(void) {
	std::map<uint32, AlarmElement*>::iterator it = mapAlarm.begin();
	while( it != mapAlarm.end() ) {
		it->second->Run();
		it++;
	}
}


bool CVCGMember::ifMemberAlarm(Member_alarm_type_E t) {
	uint8 status = RC6400_VC12_AlarmR_Read_Single(vc12->GetHid());
	switch( t ) {
	case LaVCT_DNU: {
		uint8 ctrl = RC6400_VC12T_CTRL_Status_Read(vc12->GetHid());
		if( ctrl == 0x0f ) {
			return true;
		}
	}
		break;
	case LaVCR_TSF:
		if( (status >> 7) & 1 != 0 ) {
			return true;
		}
		break;
	case LaVCR_LOMF2:
		if( (status >> 6) & 1 != 0 ) {
			return true;
		}
		break;
	case LaVCR_FAIL:
		if( (status >> 3) & 1 != 0 ) {
			return true;
		}
		break;
	case LaVCR_CRCE:
		if( (status >> 1) & 1 != 0 ) {
			return true;
		}
		break;
	case LaVCR_SQM:
		if( (status >> 0) & 1 != 0 ) {
			return true;
		}
		break;
	}
	return false;
}

