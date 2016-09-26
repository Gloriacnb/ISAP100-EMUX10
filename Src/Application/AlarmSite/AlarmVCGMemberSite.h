/*
 * AlarmVCGMemberSite.h
 *
 *  Created on: 2013-5-14
 *      Author: Administrator
 */

#ifndef ALARMVCGMEMBERSITE_H_
#define ALARMVCGMEMBERSITE_H_

#include "AlarmElement.h"
#include "CVCG_define.h"



class CVCGMember;
class AlarmVCGMemberSite : public AlarmElement {
public:
	AlarmVCGMemberSite(Alarm_property_T*, CVCGMember*, Member_alarm_type_E);
	virtual ~AlarmVCGMemberSite();

private:
	virtual uint32 SourceID(void);
	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
	CVCGMember* state;	//获取告警状态驱动
	Member_alarm_type_E AlarmSn;	//枚举vcg member告警序号
};

#endif /* ALARMVCGMEMBERSITE_H_ */
