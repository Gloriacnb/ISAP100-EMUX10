/*
 * CMibE1ChannelTable.h
 *
 *  Created on: 2013-4-25
 *      Author: Administrator
 */

#ifndef CMIBE1CHANNELTABLE_H_
#define CMIBE1CHANNELTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	e1_Channel_uid,
	e1_Channel_mapping,
	e1_Channel_status,
	e1_Channel_size

}Mib_E1_Channel_Column_E;


class CMibE1ChannelTable : public CMibTable {
	CMibE1ChannelTable();
public:
	CMibE1ChannelTable(uint32*, uint32, table_info_T*);
	virtual ~CMibE1ChannelTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[e1_Channel_size];
};

class CMibE1ChannelCol_uid : public CMibTableColumn {
	CMibE1ChannelCol_uid();
public:
	CMibE1ChannelCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1ChannelCol_uid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibE1ChannelCol_Mapping : public CMibTableColumn {
	CMibE1ChannelCol_Mapping();
public:
	CMibE1ChannelCol_Mapping(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1ChannelCol_Mapping() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibE1ChannelCol_Status : public CMibTableColumn {
	CMibE1ChannelCol_Status();
public:
	CMibE1ChannelCol_Status(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1ChannelCol_Status() {};

	virtual int CallbackGet(const index_info_T& index);
};


#endif /* CMIBE1CHANNELTABLE_H_ */
