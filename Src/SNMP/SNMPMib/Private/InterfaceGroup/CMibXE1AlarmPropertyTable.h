/*
 * CMibXE1AlarmPropertyTable.h
 *
 *  Created on: 2015Äê12ÔÂ30ÈÕ
 *      Author: Administrator
 */

#ifndef CMIBXE1ALARMPROPERTYTABLE_H_
#define CMIBXE1ALARMPROPERTYTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	XE1_Alarm_type,
	XE1_Alarm_Property,
	XE1_Alarm_name,
	XE1_Alarm_size

}Mib_XE1_Alarm_Column_E;

class CMibXE1AlarmPropertyTable : public CMibTable {
	CMibXE1AlarmPropertyTable();
public:
	CMibXE1AlarmPropertyTable(uint32*, uint32, table_info_T*);
	virtual ~CMibXE1AlarmPropertyTable();

	virtual column_info_T* getColInfo(int sn);

	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[XE1_Alarm_size];
};

class CMibXE1AlarmCol_uid : public CMibTableColumn {
	CMibXE1AlarmCol_uid();
public:
	CMibXE1AlarmCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1AlarmCol_uid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXE1AlarmCol_Property : public CMibTableColumn {
	CMibXE1AlarmCol_Property();
public:
	CMibXE1AlarmCol_Property(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1AlarmCol_Property() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};


class CMibXE1AlarmCol_Name : public CMibTableColumn {
	CMibXE1AlarmCol_Name();
public:
	CMibXE1AlarmCol_Name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1AlarmCol_Name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};
#endif /* CMIBXE1ALARMPROPERTYTABLE_H_ */
