/*
 * AlarmAUSite.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef ALARMAUSITE_H_
#define ALARMAUSITE_H_

#include "AlarmElement.h"
#include "CSTM_define.h"

class CifSTMAlarmStatus;
class AlarmAUSite : public AlarmElement {
public:
	AlarmAUSite(Alarm_property_T*, CifSTMAlarmStatus*, AU_alarm_type_E);
	virtual ~AlarmAUSite();

private:
	virtual uint32 SourceID(void);
	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
	CifSTMAlarmStatus* state;	//获取告警状态驱动
	AU_alarm_type_E AlarmSn;	//枚举MS告警序号
};


#endif /* ALARMAUSITE_H_ */
