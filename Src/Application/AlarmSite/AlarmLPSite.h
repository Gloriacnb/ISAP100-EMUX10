/*
 * AlarmLPSite.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef ALARMLPSITE_H_
#define ALARMLPSITE_H_

#include "CVC12_define.h"
#include "AlarmElement.h"

class CifVC12AlarmStatus;

class AlarmLPSite : public AlarmElement {
	AlarmLPSite();
public:
	AlarmLPSite(Alarm_property_T*, CifVC12AlarmStatus*, LP_Alarm_type_E);
	virtual ~AlarmLPSite();

private:
	virtual uint32 SourceID(void);
	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
	CifVC12AlarmStatus* state;	//��ȡ�澯״̬����
	LP_Alarm_type_E AlarmSn;	//ö��MS�澯���
};

#endif /* ALARMLPSITE_H_ */
