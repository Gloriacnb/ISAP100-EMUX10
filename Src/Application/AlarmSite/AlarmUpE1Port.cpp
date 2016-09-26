/*
 * AlarmUpE1Port.cpp
 *
 *  Created on: 2016年3月22日
 *      Author: Administrator
 */

#include "AlarmUpE1Port.h"
#include "CUpE1Port.h"

AlarmUpE1Port::AlarmUpE1Port(Alarm_property_T* cfg, CUpE1Port* driver, UPE1_alarm_type_E sn)
	: AlarmElement(cfg) {

	stateDriver = driver;
	AlarmSn = sn;
}

AlarmUpE1Port::~AlarmUpE1Port() {
	// TODO Auto-generated destructor stub
}

Alarm_status_E AlarmUpE1Port::ReadCurrentStatus(void) {
	if( stateDriver->ifE1Alarm(AlarmSn) ) {
		return alarm;
	}
	return normal;
}
void AlarmUpE1Port::DisplayExtend(Alarm_event_E evt) {
	if( evt == alarm_raise ) {
	//������������¼�֪ͨ
	}
	else if( evt == alarm_clear ) {

	}
}

uint32 AlarmUpE1Port::SourceID(void) {
	return stateDriver->getUID();
};
