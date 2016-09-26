/*
 * AlarmVCGSite.h
 *
 *  Created on: 2013-4-8
 *      Author: Administrator
 */

#ifndef ALARMVCGSITE_H_
#define ALARMVCGSITE_H_

#include "AlarmElement.h"
#include "CVCG_define.h"



class CifVCGAlarmStatus;
class AlarmVCGSite : public AlarmElement {
public:
	AlarmVCGSite(Alarm_property_T*, CifVCGAlarmStatus*, VCG_alarm_type_E);
	virtual ~AlarmVCGSite();

private:
	virtual uint32 SourceID(void);
	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
	CifVCGAlarmStatus* state;	//��ȡ�澯״̬����
	VCG_alarm_type_E AlarmSn;	//ö��MS�澯���
};

#endif /* ALARMVCGSITE_H_ */
