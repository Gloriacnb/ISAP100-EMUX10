/*
 * AlarmTUSite.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef ALARMTUSITE_H_
#define ALARMTUSITE_H_

#include "CVC12_define.h"
#include "AlarmElement.h"

class CifVC12AlarmStatus;
class AlarmTUSite : public AlarmElement {
	AlarmTUSite();
public:
	AlarmTUSite(Alarm_property_T*, CifVC12AlarmStatus*, TU_Alarm_type_E);
	virtual ~AlarmTUSite();

private:
	virtual uint32 SourceID(void);
	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
	CifVC12AlarmStatus* state;	//��ȡ�澯״̬����
	TU_Alarm_type_E AlarmSn;	//ö��MS�澯���
};

#endif /* ALARMTUSITE_H_ */
