/*
 * AlarmVCGMemberSite.cpp
 *
 *  Created on: 2013-5-14
 *      Author: Administrator
 */

#include "AlarmVCGMemberSite.h"
#include "CVCGMember.h"
#include "CVC12.h"

AlarmVCGMemberSite::AlarmVCGMemberSite(Alarm_property_T* p, CVCGMember* m, Member_alarm_type_E t)
		: AlarmElement(p){
	// TODO Auto-generated constructor stub
	state = m;
	AlarmSn = t;
}

AlarmVCGMemberSite::~AlarmVCGMemberSite() {
	// TODO Auto-generated destructor stub
}

uint32 AlarmVCGMemberSite::SourceID(void) {
	return state->getVC12()->getUID();
}
Alarm_status_E AlarmVCGMemberSite::ReadCurrentStatus(void) {

	return normal;
}
void AlarmVCGMemberSite::DisplayExtend(Alarm_event_E evt) {
	if( evt == alarm_raise ) {
	//给点灯任务发送事件通知

	}

}
