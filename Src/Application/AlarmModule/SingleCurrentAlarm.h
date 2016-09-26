/*
 * SingleCurrentAlarm.h
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#ifndef SINGLECURRENTALARM_H_
#define SINGLECURRENTALARM_H_

//#include "AlarmItem.h"
#include "EZ_types.h"
#include <map>

class AlarmItem;
class SingleCurrentAlarm {
	SingleCurrentAlarm();
	SingleCurrentAlarm(const SingleCurrentAlarm&);
	SingleCurrentAlarm& operator= (SingleCurrentAlarm&);
	virtual ~SingleCurrentAlarm();

	static SingleCurrentAlarm cAlm;
public:
	static SingleCurrentAlarm& instance(void) {
		return cAlm;
	};
	AlarmItem* AlarmRaised(uint16 type, uint8 lv, uint32 src);
	void AlarmClear(AlarmItem* item);

	AlarmItem* getAlarmItemByIndex(uint32 index);
	uint32 getFirstAlarmItemIndex(void);
	uint32 getNextAlarmItemIndex(uint32 index);
	uint32 getAlarmNumber(void) {
		return mapAlarmItem.size();
	};

private:
	std::map<uint32, AlarmItem*> mapAlarmItem;
	static uint32 AlarmIndex;
};

#endif /* SINGLECURRENTALARM_H_ */
