/*
 * AlarmUnframeE1site.cpp
 *
 *  Created on: 2013-4-25
 *      Author: Administrator
 */

#include "AlarmUnframeE1site.h"
#include "CUnframeE1.h"

AlarmUnframeE1site::AlarmUnframeE1site(Alarm_property_T* cfg, CUnframeE1* driver, UE1_alarm_type_E sn)
		: AlarmElement(cfg) {
	stateDriver = driver;
	AlarmSn = sn;
}

AlarmUnframeE1site::~AlarmUnframeE1site() {
	// TODO Auto-generated destructor stub
}

Alarm_status_E AlarmUnframeE1site::ReadCurrentStatus(void) {
	if( stateDriver->ifE1Alarm(AlarmSn) ) {
		return alarm;
	}
	return normal;
}
void AlarmUnframeE1site::DisplayExtend(Alarm_event_E evt) {
	if( evt == alarm_raise ) {
		//给点灯任务发送事件通知
	}
}

uint32 AlarmUnframeE1site::SourceID(void) {
	return stateDriver->getUID();
};
