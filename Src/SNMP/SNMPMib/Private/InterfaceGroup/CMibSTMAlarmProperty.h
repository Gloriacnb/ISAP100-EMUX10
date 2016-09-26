/*
 * CMibSTMAlarmProperty.h
 *
 *  Created on: 2013-4-24
 *      Author: Administrator
 */

#ifndef CMIBSTMALARMPROPERTY_H_
#define CMIBSTMALARMPROPERTY_H_



#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	stm_Alarm_type,
	stm_Alarm_Property,
	stm_Alarm_name,
	stm_Alarm_size

}Mib_STM_Alarm_Column_E;

class CMibSTMAlarmProperty : public CMibTable {
	CMibSTMAlarmProperty();
public:
	CMibSTMAlarmProperty(uint32*, uint32, table_info_T*);
	virtual ~CMibSTMAlarmProperty();

	virtual column_info_T* getColInfo(int sn);

	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[stm_Alarm_size];
};

class CMibSTMAlarmCol_uid : public CMibTableColumn {
	CMibSTMAlarmCol_uid();
public:
	CMibSTMAlarmCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibSTMAlarmCol_uid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibSTMAlarmCol_Property : public CMibTableColumn {
	CMibSTMAlarmCol_Property();
public:
	CMibSTMAlarmCol_Property(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibSTMAlarmCol_Property() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};


class CMibSTMAlarmCol_Name : public CMibTableColumn {
	CMibSTMAlarmCol_Name();
public:
	CMibSTMAlarmCol_Name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibSTMAlarmCol_Name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

#endif /* CMIBSTMALARMPROPERTY_H_ */
