/*
 * CMibLoopablePortTable.h
 *
 *  Created on: 2013-6-3
 *      Author: Administrator
 */

#ifndef CMIBLOOPABLEPORTTABLE_H_
#define CMIBLOOPABLEPORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	loopable_port_index,
	loopable_port_name,
	loopable_port_size
};


class CMibLoopablePortTable : public CMibTable {
	CMibLoopablePortTable();
public:
	CMibLoopablePortTable(uint32*, uint32, table_info_T*);
	virtual ~CMibLoopablePortTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[loopable_port_size];
};

class CMibLoopablePort_index : public CMibTableColumn {
	CMibLoopablePort_index();
public:
	CMibLoopablePort_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopablePort_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibLoopablePort_name : public CMibTableColumn {
	CMibLoopablePort_name();
public:
	CMibLoopablePort_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopablePort_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

#endif /* CMIBLOOPABLEPORTTABLE_H_ */
