/*
 * CifVCGAlarmStatus.h
 *
 *  Created on: 2013-4-8
 *      Author: Administrator
 */

#ifndef CIFVCGALARMSTATUS_H_
#define CIFVCGALARMSTATUS_H_

#include "CVCG_define.h"
class CifVCGAlarmStatus {
public:
	CifVCGAlarmStatus();
	virtual ~CifVCGAlarmStatus();

	virtual bool ifVCGAlarm(VCG_alarm_type_E sn) = 0;
	virtual uint32 getUID(void) = 0;
};

#endif /* CIFVCGALARMSTATUS_H_ */
