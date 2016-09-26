/*
 * AlarmAUSite.cpp
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#include "AlarmAUSite.h"
#include "CifSTMAlarmStatus.h"

AlarmAUSite::AlarmAUSite(Alarm_property_T* cfg, CifSTMAlarmStatus* driver,
		AU_alarm_type_E sn) :
		AlarmElement(cfg) {
	// TODO Auto-generated constructor stub
	state = driver;
	AlarmSn = sn;
}

AlarmAUSite::~AlarmAUSite() {
	// TODO Auto-generated destructor stub
}

Alarm_status_E AlarmAUSite::ReadCurrentStatus(void) {
	if (state->ifAU4Alarm(AlarmSn)) {
		return alarm;
	}
	return normal;

}
void AlarmAUSite::DisplayExtend(Alarm_event_E evt) {
	if (evt == alarm_raise) {
		//������������¼�֪ͨ

	}
}

uint32 AlarmAUSite::SourceID(void) {
	return state->getUID();
}
;
