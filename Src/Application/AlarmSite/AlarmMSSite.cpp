/*
 * AlarmMSSite.cpp
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#include "AlarmMSSite.h"
#include "CifSTMAlarmStatus.h"

AlarmMSSite::AlarmMSSite(Alarm_property_T* cfg, CifSTMAlarmStatus* driver,
		MS_alarm_type_E sn) :
		AlarmElement(cfg) {
	// TODO Auto-generated constructor stub
	state = driver;
	AlarmSn = sn;
}

AlarmMSSite::~AlarmMSSite() {
	// TODO Auto-generated destructor stub
}

Alarm_status_E AlarmMSSite::ReadCurrentStatus(void) {
	if (state->ifMSAlarm(AlarmSn)) {
		return alarm;
	}
	return normal;

}
void AlarmMSSite::DisplayExtend(Alarm_event_E evt) {
	if (evt == alarm_raise) {
		//给点灯任务发送事件通知

	}
}

uint32 AlarmMSSite::SourceID(void) {
	return state->getUID();
}
;
