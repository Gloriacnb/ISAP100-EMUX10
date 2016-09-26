/*
 * AlarmElement.cpp
 *
 *  Created on: 2013-3-28
 *      Author: Administrator
 */

#include "AlarmElement.h"
#include "SingleCurrentAlarm.h"

//using namespace std;


AlarmElement::AlarmElement(Alarm_property_T* cfgData) {
	weight = weightBotton;
	configData = cfgData;
	sn = 0;
	currentStatus = normal;
	StatusByFilt = normal;
	item = 0;
}

AlarmElement::~AlarmElement() {
	if(item) {
		SingleCurrentAlarm::instance().AlarmClear(item);
	}
}

void AlarmElement::Run(void) {
	currentStatus = ReadCurrentStatus();
	if( FiltAlarm() ) {
		StatusByFilt = normal;
	}
	else {
		StatusByFilt = currentStatus;
	}
	Alarm_event_E evt = CollectAlarm();
	Display(evt);
}

/*
 * 收集告警状态， 并经过去抖。
 * 去抖算法用权重衡量，权重值最低3 最高7 当权值处于3和7之间时，认为无变化。
 *
 * return 	1 告警消失
 * 			alarm_nochange 无变化
 * 			alarm_raise 告警产生
 */
Alarm_event_E AlarmElement::CollectAlarm(void) {
	if( StatusByFilt  == alarm ) {
		++weight;
		if( (weight == weightTop) && (item == 0) ) {
			return alarm_raise;
		}
		else if( weight > weightTop ){
			weight = weightTop;
		}
	}
	else {
		--weight;
		if( (weight == weightBotton) && (item != 0) ) {
			return alarm_clear;
		}
		else if( weight < weightBotton ) {
			weight = weightBotton;
		}
	}

	return alarm_nochange;

}


/*
 * return true 屏蔽该告警
 *        false 不屏蔽
 */
bool AlarmElement::FiltAlarm(void) {

	if( configData->mask == 1 ) {
		return true;
	}
	std::vector<AlarmElement*>::iterator it = higher_alarm.begin();
	while( it != higher_alarm.end() ) {
		if( (*it)->CurrentStatus() == alarm ) {
			return true;
		}
		it++;
	}

	return false;
}


void AlarmElement::Display(Alarm_event_E evt) {
	if( configData->trap == 1 ) {
		//send trap here;
	}
	if( evt == alarm_raise ) {
		//make current alarm node
		if( item ) {
			while(1);
		}
		item = SingleCurrentAlarm::instance().AlarmRaised(
				configData->typeID, configData->level, SourceID() );
	}
	else if( evt == alarm_clear ) {
		//删除告警条目
		if( item ) {
			SingleCurrentAlarm::instance().AlarmClear(item);
			item = 0;
		}
		else
			while(1);

	}
	DisplayExtend(evt);
}

