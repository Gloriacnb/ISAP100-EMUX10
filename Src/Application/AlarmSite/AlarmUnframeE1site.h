/*
 * AlarmUnframeE1site.h
 *
 *  Created on: 2013-4-25
 *      Author: Administrator
 */

#ifndef ALARMUNFRAMEE1SITE_H_
#define ALARMUNFRAMEE1SITE_H_

#include "AlarmElement.h"
#include "CUnframeE1_define.h"

class CUnframeE1;
class AlarmUnframeE1site : public AlarmElement {
public:
	AlarmUnframeE1site(Alarm_property_T* cfg, CUnframeE1* driver, UE1_alarm_type_E sn);
	virtual ~AlarmUnframeE1site();

	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);

private:
	virtual uint32 SourceID(void);
	CUnframeE1* stateDriver;
	UE1_alarm_type_E AlarmSn;
};

#endif /* ALARMUNFRAMEE1SITE_H_ */
