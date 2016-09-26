/*
 * CMibLoopAddTable.h
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#ifndef CMIBLOOPADDTABLE_H_
#define CMIBLOOPADDTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	loop_add,
	loop_count,
	loop_add_size

};


class CMibLoopAddTable : public CMibTable {
	CMibLoopAddTable();
public:
	CMibLoopAddTable(uint32*, uint32, table_info_T*);
	virtual ~CMibLoopAddTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[loop_add_size];
};

class CMibLoopAddColumn_add : public CMibTableColumn {
	CMibLoopAddColumn_add();
public:
	CMibLoopAddColumn_add(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopAddColumn_add() {};

	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibLoopCol_count : public CMibTableColumn {
	CMibLoopCol_count();
public:
	CMibLoopCol_count(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopCol_count() {};

	virtual int CallbackGet(const index_info_T& index);
};


#endif /* CMIBLOOPADDTABLE_H_ */
