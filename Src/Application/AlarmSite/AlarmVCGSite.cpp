/*
 * AlarmVCGSite.cpp
 *
 *  Created on: 2013-4-8
 *      Author: Administrator
 */

#include "AlarmVCGSite.h"
#include "CifVCGAlarmStatus.h"

AlarmVCGSite::AlarmVCGSite(Alarm_property_T* cfg,
		CifVCGAlarmStatus* driver,
		VCG_alarm_type_E sn) : AlarmElement(cfg) {
	// TODO Auto-generated constructor stub
	state = driver;
	AlarmSn = sn;

}

AlarmVCGSite::~AlarmVCGSite() {
	// TODO Auto-generated destructor stub
}

Alarm_status_E AlarmVCGSite::ReadCurrentStatus(void) {
	if( state->ifVCGAlarm(AlarmSn) ) {
		return alarm;
	}
	return normal;
}
void AlarmVCGSite::DisplayExtend(Alarm_event_E evt) {
	if( evt == alarm_raise ) {
	//给点灯任务发送事件通知

	}
}

uint32 AlarmVCGSite::SourceID(void) {
	return state->getUID();
};
