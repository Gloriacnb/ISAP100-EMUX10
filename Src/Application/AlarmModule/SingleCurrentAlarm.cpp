/*
 * SingleCurrentAlarm.cpp
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#include "SingleCurrentAlarm.h"
#include "AlarmItem.h"
#include "RTC.h"
#include <rtl.h>
#include "SingleHistoryAlarm.h"


SingleCurrentAlarm SingleCurrentAlarm::cAlm;
uint32 SingleCurrentAlarm::AlarmIndex;

SingleCurrentAlarm::SingleCurrentAlarm() {
	// TODO Auto-generated constructor stub
	AlarmIndex = 0;
}

SingleCurrentAlarm::~SingleCurrentAlarm() {
	// TODO Auto-generated destructor stub
}

AlarmItem* SingleCurrentAlarm::AlarmRaised(uint16 type, uint8 lv, uint32 src) {
//	std::string s(RTC::getCurrentStringTime());
//	AlarmItem* item = new AlarmItem( AlarmIndex, type, lv, src, s );
	++AlarmIndex;
	uint32 time = RTC::getRunningSecs();//RTC::getCurrentSecsTime();
	AlarmItem* item = new AlarmItem( AlarmIndex, type, lv, src, time );

	tsk_lock();
	mapAlarmItem.insert(std::pair<uint32, AlarmItem*>(AlarmIndex, item));
	tsk_unlock();
	return item;

}
void SingleCurrentAlarm::AlarmClear(AlarmItem* item) {
	std::map<uint32, AlarmItem*>::iterator it = mapAlarmItem.find( item->itsSn() );
	//移到历史告警
	SingleHistoryAlarm::instance().addAlarmItem(item);

	if( it != mapAlarmItem.end() ) {
		tsk_lock();
		mapAlarmItem.erase(it);
		tsk_unlock();
	}
}

AlarmItem* SingleCurrentAlarm::getAlarmItemByIndex(uint32 index) {
	std::map<uint32, AlarmItem*>::iterator it = mapAlarmItem.find(index);
	if( it != mapAlarmItem.end() ) {
		return it->second;
	}
	return 0;
}
uint32 SingleCurrentAlarm::getFirstAlarmItemIndex(void) {
	std::map<uint32, AlarmItem*>::iterator it = mapAlarmItem.begin();
	if( it != mapAlarmItem.end() ) {
		return it->first;
	}
	return 0;

}
uint32 SingleCurrentAlarm::getNextAlarmItemIndex(uint32 index) {
	std::map<uint32, AlarmItem*>::iterator it = mapAlarmItem.find(index);
	if( it != mapAlarmItem.end() ) {
		++it;
		if(it != mapAlarmItem.end() ) {
			return it->first;
		}
	}
	return 0;

}


