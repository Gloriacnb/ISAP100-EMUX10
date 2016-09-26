/*
 * AlarmNmPortE1Site.h
 *
 *  Created on: 2015Äê12ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef ALARMNMPORTE1SITE_H_
#define ALARMNMPORTE1SITE_H_

#include "AlarmElement.h"
#include "CNME1Port_define.h"

class CNME1Port;

class AlarmNmPortE1Site: public AlarmElement {
public:
	AlarmNmPortE1Site(Alarm_property_T* cfg, CNME1Port* driver, UFE1_alarm_type_E sn);
	virtual ~AlarmNmPortE1Site();

	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
private:
	virtual uint32 SourceID(void);
	CNME1Port* stateDriver;
	UFE1_alarm_type_E AlarmSn;
};

#endif /* ALARMNMPORTE1SITE_H_ */
