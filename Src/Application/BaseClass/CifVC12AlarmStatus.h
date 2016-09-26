/*
 * CifVC12AlarmStatus.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef CIFVC12ALARMSTATUS_H_
#define CIFVC12ALARMSTATUS_H_

#include "CVC12_define.h"
class CifVC12AlarmStatus {
public:
	CifVC12AlarmStatus();
	virtual ~CifVC12AlarmStatus();

	virtual bool ifTUAlarm(TU_Alarm_type_E sn) = 0;
	virtual bool ifLPAlarm(LP_Alarm_type_E sn) = 0;
	virtual uint32 getUID(void) = 0;
};

#endif /* CIFVC12ALARMSTATUS_H_ */
