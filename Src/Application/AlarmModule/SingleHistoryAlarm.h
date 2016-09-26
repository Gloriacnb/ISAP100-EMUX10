/*
 * SingleHistoryAlarm.h
 *
 *  Created on: 2013-5-7
 *      Author: Administrator
 */

#ifndef SINGLEHISTORYALARM_H_
#define SINGLEHISTORYALARM_H_

#include "EZ_types.h"
#include <map>

class AlarmItem;
class SingleHistoryAlarm {
	SingleHistoryAlarm();
	SingleHistoryAlarm(const SingleHistoryAlarm&);
	SingleHistoryAlarm& operator= (SingleHistoryAlarm&);
	virtual ~SingleHistoryAlarm();

	static SingleHistoryAlarm cAlm;
public:
	static SingleHistoryAlarm& instance(void) {
		return cAlm;
	};

	void addAlarmItem(AlarmItem* item);
	uint32 getAlarmNumber(void);
private:
	std::map<uint32, AlarmItem*> mapAlarmItem;
};

#endif /* SINGLEHISTORYALARM_H_ */
