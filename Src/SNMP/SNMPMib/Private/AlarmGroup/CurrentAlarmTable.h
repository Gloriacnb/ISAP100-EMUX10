/*
 * CurrentAlarmTable.h
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#ifndef CURRENTALARMTABLE_H_
#define CURRENTALARMTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	current_alarm_index,
	current_alarm_type,
	current_alarm_level,
	current_alarm_source,
	current_alarm_start_time,
	current_alarm_start_secs,
	current_alarm_size

};


class CurrentAlarmTable : public CMibTable {
	CurrentAlarmTable();
public:
	CurrentAlarmTable(uint32*, uint32, table_info_T*);
	virtual ~CurrentAlarmTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[current_alarm_size];
};


class CurrentAlarmCol_index : public CMibTableColumn {
	CurrentAlarmCol_index();
public:
	CurrentAlarmCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CurrentAlarmCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CurrentAlarmCol_type : public CMibTableColumn {
	CurrentAlarmCol_type();
public:
	CurrentAlarmCol_type(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CurrentAlarmCol_type() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CurrentAlarmCol_level : public CMibTableColumn {
	CurrentAlarmCol_level();
public:
	CurrentAlarmCol_level(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CurrentAlarmCol_level() {};

	virtual int CallbackGet(const index_info_T& index);
};


class CurrentAlarmCol_source : public CMibTableColumn {
	CurrentAlarmCol_source();
public:
	CurrentAlarmCol_source(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CurrentAlarmCol_source() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CurrentAlarmCol_startTime : public CMibTableColumn {
	CurrentAlarmCol_startTime();
public:
	CurrentAlarmCol_startTime(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CurrentAlarmCol_startTime() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CurrentAlarmCol_startSecs : public CMibTableColumn {
	CurrentAlarmCol_startSecs();
public:
	CurrentAlarmCol_startSecs(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CurrentAlarmCol_startSecs() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};
#endif /* CURRENTALARMTABLE_H_ */
