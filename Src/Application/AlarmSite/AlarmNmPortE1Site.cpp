/*
 * AlarmNmPortE1Site.cpp
 *
 *  Created on: 2015年12月28日
 *      Author: Administrator
 */

#include "AlarmNmPortE1Site.h"
#include "CNME1Port.h"

AlarmNmPortE1Site::AlarmNmPortE1Site(Alarm_property_T* cfg, CNME1Port* driver, UFE1_alarm_type_E sn)
	: AlarmElement(cfg) {
	stateDriver = driver;
	AlarmSn = sn;
}

AlarmNmPortE1Site::~AlarmNmPortE1Site() {

}

Alarm_status_E AlarmNmPortE1Site::ReadCurrentStatus(void) {
	if( stateDriver->ifE1Alarm(AlarmSn) ) {
		return alarm;
	}
	return normal;
}
void AlarmNmPortE1Site::DisplayExtend(Alarm_event_E evt) {
	if( evt == alarm_raise ) {
	//给点灯任务发送事件通知
	}
	else if( evt == alarm_clear ) {

	}
}

uint32 AlarmNmPortE1Site::SourceID(void) {
	return stateDriver->getUID();
};
