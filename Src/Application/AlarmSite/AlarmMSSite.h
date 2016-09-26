/*
 * AlarmMSSite.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef ALARMMSSITE_H_
#define ALARMMSSITE_H_

#include "AlarmElement.h"
#include "CSTM_define.h"

class CifSTMAlarmStatus;
class AlarmMSSite : public AlarmElement {
public:
	AlarmMSSite(Alarm_property_T*, CifSTMAlarmStatus*, MS_alarm_type_E);
	virtual ~AlarmMSSite();

private:
	virtual uint32 SourceID(void);
	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
	CifSTMAlarmStatus* state;	//��ȡ�澯״̬����
	MS_alarm_type_E AlarmSn;	//ö��MS�澯���
};

#endif /* ALARMMSSITE_H_ */
