/*
 * CifSTMAlarmStatus.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef CIFSTMALARMSTATUS_H_
#define CIFSTMALARMSTATUS_H_

#include "CSTM_define.h"

class CifSTMAlarmStatus {
public:
	CifSTMAlarmStatus();
	virtual ~CifSTMAlarmStatus();

	virtual bool ifMSAlarm(MS_alarm_type_E sn) = 0;
	virtual bool ifAU4Alarm(AU_alarm_type_E sn) = 0;
	virtual bool ifVC4Alarm(VC_alarm_type_E sn) = 0;

	virtual uint32 getUID(void) = 0;



};

#endif /* CIFSTMALARMSTATUS_H_ */
