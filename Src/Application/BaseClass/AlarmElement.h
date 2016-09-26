/*
 * AlarmElement.h
 *
 *  Created on: 2013-3-28
 *      Author: Administrator
 *      Descripe:
 *      告警实例类，例如 第一路E1的los告警，就是一个实例，同种类告警自动统计
 */

#ifndef ALARMELEMENT_H_
#define ALARMELEMENT_H_

#include <string>
#include "EZ_types.h"
#include <vector>
#include "AlarmElement_define.h"


class AlarmItem;
class AlarmElement {
	const static uint8 weightTop = 7;
	const static uint8 weightBotton = 3;
	AlarmElement();
public:
	AlarmElement(Alarm_property_T*);
	virtual ~AlarmElement();

	void Run(void);

	virtual Alarm_status_E ReadCurrentStatus(void) = 0;
	virtual void DisplayExtend(Alarm_event_E) = 0;
	virtual uint32 SourceID(void) = 0;

	void AddHigherAlarm(AlarmElement*);

	Alarm_status_E CurrentStatus(void) {
		return currentStatus;
	};

	bool ChangePropertyLevel(uint32 newLevel) {
		if( newLevel > prompt || newLevel < emerg ) {
			return false;
		}
		configData->level = (Alarm_level_E)newLevel;
		return true;
	};
	bool ChangePropertyTrap(uint32 newValue) {
		if( newValue > 1 ) {
			return false;
		}
		configData->trap = newValue;
		return true;
	};
	bool ChangePropertyMask(uint32 newValue) {
		if( newValue > 1 ) {
			return false;
		}
		configData->mask = newValue;
		return true;
	};

	uint8 getPropertyLevel(void) {
		return configData->level;
	};
	uint8 getPropertyTrap(void) {
		return configData->trap;
	};
	uint8 getPropertyMask(void) {
		return configData->mask;
	};

private:
	std::string name;	//告警名称
	uint32 sn;			//告警序列号
	Alarm_property_T* configData;
	uint8 weight;
	Alarm_status_E currentStatus;
	Alarm_status_E StatusByFilt;
	std::vector<AlarmElement*> higher_alarm;
	Alarm_event_E CollectAlarm(void);
	bool FiltAlarm(void);
	void Display(Alarm_event_E);
	AlarmItem* item;


};

#endif /* ALARMELEMENT_H_ */
