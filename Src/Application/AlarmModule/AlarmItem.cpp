/*
 * AlarmItem.cpp
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#include "AlarmItem.h"
#include "CPPTools.h"

AlarmItem::AlarmItem(uint32 sn, uint16 type, uint8 lv, uint32 src, std::string& start) {
	// TODO Auto-generated constructor stub
	index = sn;
	typeID = type;
	level = lv;
	alarmSrc = src;
	startTime.assign(start);
	startSecs = 0;
}

AlarmItem::AlarmItem(uint32 sn, uint16 type, uint8 lv, uint32 src, uint32 secs) {
	index = sn;
	typeID = type;
	level = lv;
	alarmSrc = src;
	startSecs = secs;
}



AlarmItem::~AlarmItem() {
	// TODO Auto-generated destructor stub
}


std::string AlarmItem::getStringItem(void) {
	std::string stringItem =
			CPPTools::number2string(index) + "," +
			CPPTools::number2string(typeID) + "," +
			CPPTools::number2string(level) + "," +
			CPPTools::number2string(alarmSrc) + "," +
			CPPTools::number2string(RTC::converRunningSecsToUTC(startSecs));
	return stringItem;

}

