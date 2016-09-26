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
 * �ռ��澯״̬�� ������ȥ����
 * ȥ���㷨��Ȩ�غ�����Ȩ��ֵ���3 ���7 ��Ȩֵ����3��7֮��ʱ����Ϊ�ޱ仯��
 *
 * return 	1 �澯��ʧ
 * 			alarm_nochange �ޱ仯
 * 			alarm_raise �澯����
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
 * return true ���θø澯
 *        false ������
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
		//ɾ���澯��Ŀ
		if( item ) {
			SingleCurrentAlarm::instance().AlarmClear(item);
			item = 0;
		}
		else
			while(1);

	}
	DisplayExtend(evt);
}

