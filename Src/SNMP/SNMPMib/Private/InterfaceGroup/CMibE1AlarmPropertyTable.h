/*
 * CMibE1AlarmPropertyTable.h
 *
 *  Created on: 2013-4-25
 *      Author: Administrator
 */

#ifndef CMIBE1ALARMPROPERTYTABLE_H_
#define CMIBE1ALARMPROPERTYTABLE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	E1_Alarm_type,
	E1_Alarm_Property,
	E1_Alarm_name,
	E1_Alarm_size

}Mib_E1_Alarm_Column_E;

class CMibE1AlarmPropertyTable : public CMibTable {
	CMibE1AlarmPropertyTable();
public:
	CMibE1AlarmPropertyTable(uint32*, uint32, table_info_T*);
	virtual ~CMibE1AlarmPropertyTable();

	virtual column_info_T* getColInfo(int sn);

	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[E1_Alarm_size];
};

class CMibE1AlarmCol_uid : public CMibTableColumn {
	CMibE1AlarmCol_uid();
public:
	CMibE1AlarmCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1AlarmCol_uid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibE1AlarmCol_Property : public CMibTableColumn {
	CMibE1AlarmCol_Property();
public:
	CMibE1AlarmCol_Property(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1AlarmCol_Property() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};


class CMibE1AlarmCol_Name : public CMibTableColumn {
	CMibE1AlarmCol_Name();
public:
	CMibE1AlarmCol_Name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1AlarmCol_Name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

#endif /* CMIBE1ALARMPROPERTYTABLE_H_ */
