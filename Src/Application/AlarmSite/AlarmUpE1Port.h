/*
 * AlarmUpE1Port.h
 *
 *  Created on: 2016年3月22日
 *      Author: Administrator
 */

#ifndef SRC_APPLICATION_ALARMSITE_ALARMUPE1PORT_H_
#define SRC_APPLICATION_ALARMSITE_ALARMUPE1PORT_H_

#include "AlarmElement.h"
#include "CUpE1Port_define.h"

class CUpE1Port;
class AlarmUpE1Port : public AlarmElement {
public:
	AlarmUpE1Port(Alarm_property_T* cfg, CUpE1Port* driver, UPE1_alarm_type_E sn);
	virtual ~AlarmUpE1Port();

	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
private:
	virtual uint32 SourceID(void);
	CUpE1Port* stateDriver;
	UPE1_alarm_type_E AlarmSn;
};

#endif /* SRC_APPLICATION_ALARMSITE_ALARMUPE1PORT_H_ */
