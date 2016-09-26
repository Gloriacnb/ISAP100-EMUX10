/*
 * SingleHistoryAlarm.cpp
 *
 *  Created on: 2013-5-7
 *      Author: Administrator
 */

#include "SingleHistoryAlarm.h"
#include "AlarmItem.h"


SingleHistoryAlarm SingleHistoryAlarm::cAlm;

SingleHistoryAlarm::SingleHistoryAlarm() {
	// TODO Auto-generated constructor stub

}

SingleHistoryAlarm::~SingleHistoryAlarm() {
	// TODO Auto-generated destructor stub
}

void SingleHistoryAlarm::addAlarmItem(AlarmItem* item) {
	mapAlarmItem.insert( std::pair<uint32, AlarmItem*>(item->itsSn(), item) );
}

uint32 SingleHistoryAlarm::getAlarmNumber(void) {
	return mapAlarmItem.size();
}
