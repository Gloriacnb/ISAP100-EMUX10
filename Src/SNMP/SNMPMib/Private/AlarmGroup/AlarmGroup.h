/*
 * AlarmGroup.h
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#ifndef ALARMGROUP_H_
#define ALARMGROUP_H_

#include "CMibGroup.h"
/*
 *
 */

enum {
	table_alarm_number,
	table_current_alarm,
	table_history_alarm,
	table_global_property,
	table_alarm_size
};


class AlarmGroup : public CMibGroup {
	AlarmGroup();
public:
	AlarmGroup(uint32* oid, uint8 oidlen);
	virtual ~AlarmGroup();
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_alarm_size];
};

#endif /* ALARMGROUP_H_ */
