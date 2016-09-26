/*
 * CMibTSChannelTable.h
 *
 *  Created on: 2013-4-26
 *      Author: Administrator
 */

#ifndef CMIBTSCHANNELTABLE_H_
#define CMIBTSCHANNELTABLE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	ts_Channel_uid,
	ts_Channel_mapping,
	ts_Channel_status,
	ts_Channel_size

}Mib_TS_Channel_Column_E;


class CMibTSChannelTable : public CMibTable {
	CMibTSChannelTable();
public:
	CMibTSChannelTable(uint32*, uint32, table_info_T*);
	virtual ~CMibTSChannelTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[ts_Channel_size];
};

class CMibTSChannelCol_uid : public CMibTableColumn {
	CMibTSChannelCol_uid();
public:
	CMibTSChannelCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibTSChannelCol_uid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibTSChannelCol_Mapping : public CMibTableColumn {
	CMibTSChannelCol_Mapping();
public:
	CMibTSChannelCol_Mapping(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibTSChannelCol_Mapping() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibTSChannelCol_Status : public CMibTableColumn {
	CMibTSChannelCol_Status();
public:
	CMibTSChannelCol_Status(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibTSChannelCol_Status() {};

	virtual int CallbackGet(const index_info_T& index);
};
#endif /* CMIBTSCHANNELTABLE_H_ */
