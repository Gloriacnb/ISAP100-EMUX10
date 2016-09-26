/*
 * AlarmItem.h
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#ifndef ALARMITEM_H_
#define ALARMITEM_H_

#include "EZ_types.h"
#include <string>
#include "RTC.h"

class AlarmItem {
	AlarmItem();
public:
	AlarmItem(uint32 sn, uint16 type, uint8 lv, uint32 src, std::string& start);
	AlarmItem(uint32 sn, uint16 type, uint8 lv, uint32 src, uint32 secs);
	virtual ~AlarmItem();

	void setEndTime(std::string& end) {
		endTime = end;
	};
	uint32 itsSn(void) { return index;};
	uint16 itsType(void) { return typeID;};
	uint8 itsLevel(void) { return level;};
	uint32 itsSource(void) {return alarmSrc;};
	std::string& itsStartTime(void) {return startTime;};
	uint32 itsStartTimeSecs(void) {return RTC::converRunningSecsToUTC(startSecs);};
	std::string getStringItem(void);
private:
	uint32 index;
	uint16 typeID;
	uint8  level;
	uint32 alarmSrc;
	uint32 startSecs;
	std::string startTime;
	std::string endTime;
};

#endif /* ALARMITEM_H_ */
