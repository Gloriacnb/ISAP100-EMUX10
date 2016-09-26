/*
 * AlarmHPSite.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef ALARMHPSITE_H_
#define ALARMHPSITE_H_

#include "AlarmElement.h"
#include "CSTM_define.h"

class CifSTMAlarmStatus;
class AlarmHPSite : public AlarmElement {
public:
	AlarmHPSite(Alarm_property_T*, CifSTMAlarmStatus*, VC_alarm_type_E);
	virtual ~AlarmHPSite();

private:
	virtual uint32 SourceID(void);
	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
	CifSTMAlarmStatus* state;	//��ȡ�澯״̬����
	VC_alarm_type_E AlarmSn;	//ö��MS�澯���
};

#endif /* ALARMHPSITE_H_ */
