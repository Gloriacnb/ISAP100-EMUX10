/*
 * AlarmHPSite.cpp
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#include "AlarmHPSite.h"
#include "CifSTMAlarmStatus.h"

AlarmHPSite::AlarmHPSite(Alarm_property_T* cfg,
		CifSTMAlarmStatus* driver,
		VC_alarm_type_E sn ) : AlarmElement(cfg) {
	// TODO Auto-generated constructor stub
	state = driver;
	AlarmSn = sn;
}

AlarmHPSite::~AlarmHPSite() {
	// TODO Auto-generated destructor stub
}

Alarm_status_E AlarmHPSite::ReadCurrentStatus(void) {
	if( state->ifVC4Alarm(AlarmSn) ) {
		return alarm;
	}
	return normal;

}
void AlarmHPSite::DisplayExtend(Alarm_event_E evt) {
	if( evt == alarm_raise ) {
	//给点灯任务发送事件通知

	}
}

uint32 AlarmHPSite::SourceID(void) {
	return state->getUID();
};
