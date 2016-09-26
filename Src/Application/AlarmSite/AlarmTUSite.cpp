/*
 * AlarmTUSite.cpp
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#include "AlarmTUSite.h"
#include "CifVC12AlarmStatus.h"

AlarmTUSite::AlarmTUSite(Alarm_property_T* cfg,
		CifVC12AlarmStatus* driver,
		TU_Alarm_type_E sn) : AlarmElement(cfg) {
	// TODO Auto-generated constructor stub
	state = driver;
	AlarmSn = sn;
}

AlarmTUSite::~AlarmTUSite() {
	// TODO Auto-generated destructor stub
}

Alarm_status_E AlarmTUSite::ReadCurrentStatus(void) {
	if( state->ifTUAlarm(AlarmSn) ) {
		return alarm;
	}
	return normal;

}
void AlarmTUSite::DisplayExtend(Alarm_event_E evt) {
	if( evt == alarm_raise ) {
	//给点灯任务发送事件通知

	}
}

uint32 AlarmTUSite::SourceID(void) {
	return state->getUID();
};
