/*
 * AlarmLPSite.cpp
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#include "AlarmLPSite.h"
#include "CifVC12AlarmStatus.h"

AlarmLPSite::AlarmLPSite(Alarm_property_T* cfg,
		CifVC12AlarmStatus* driver,
		LP_Alarm_type_E sn) : AlarmElement(cfg) {
	// TODO Auto-generated constructor stub
	state = driver;
	AlarmSn = sn;
}

AlarmLPSite::~AlarmLPSite() {
	// TODO Auto-generated destructor stub
}

Alarm_status_E AlarmLPSite::ReadCurrentStatus(void) {
	if( state->ifLPAlarm(AlarmSn) ) {
		return alarm;
	}
	return normal;

}
void AlarmLPSite::DisplayExtend(Alarm_event_E evt) {
	if( evt == alarm_raise ) {
	//������������¼�֪ͨ

	}
}

uint32 AlarmLPSite::SourceID(void) {
	return state->getUID();
};
