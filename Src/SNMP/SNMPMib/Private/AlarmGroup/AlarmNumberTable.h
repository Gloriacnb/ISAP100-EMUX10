/*
 * AlarmNumberTable.h
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#ifndef ALARMNUMBERTABLE_H_
#define ALARMNUMBERTABLE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	current_alarm_number,
	history_alarm_number,
	alarm_number_size

};


class AlarmNumberTable : public CMibTable {
	AlarmNumberTable();
public:
	AlarmNumberTable(uint32*, uint32, table_info_T*);
	virtual ~AlarmNumberTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[alarm_number_size];
};


class AlarmNumber_current : public CMibTableColumn {
	AlarmNumber_current();
public:
	AlarmNumber_current(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~AlarmNumber_current() {};

	virtual int CallbackGet(const index_info_T& index);
};

class AlarmNumber_history : public CMibTableColumn {
	AlarmNumber_history();
public:
	AlarmNumber_history(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~AlarmNumber_history() {};

	virtual int CallbackGet(const index_info_T& index);
};
#endif /* ALARMNUMBERTABLE_H_ */
