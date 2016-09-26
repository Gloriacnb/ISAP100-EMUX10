/*
 * CMibLoopPropertyTable.h
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#ifndef CMIBLOOPPROPERTYTABLE_H_
#define CMIBLOOPPROPERTYTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	loop_index,
	loop_type,
	loop_start_time,
	loop_end_time,
	loop_clear,
	loop_col_size
};


class CMibLoopPropertyTable : public CMibTable {
	CMibLoopPropertyTable();
public:
	CMibLoopPropertyTable(uint32*, uint32, table_info_T*);
	virtual ~CMibLoopPropertyTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[loop_col_size];
};

class CMibLoopPropertyCol_index : public CMibTableColumn {
	CMibLoopPropertyCol_index();
public:
	CMibLoopPropertyCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopPropertyCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibLoopPropertyCol_type : public CMibTableColumn {
	CMibLoopPropertyCol_type();
public:
	CMibLoopPropertyCol_type(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopPropertyCol_type() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibLoopPropertyCol_start : public CMibTableColumn {
	CMibLoopPropertyCol_start();
public:
	CMibLoopPropertyCol_start(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopPropertyCol_start() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibLoopPropertyCol_end : public CMibTableColumn {
	CMibLoopPropertyCol_end();
public:
	CMibLoopPropertyCol_end(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopPropertyCol_end() {};

	virtual int CallbackGet(const index_info_T& index);
};


class CMibLoopPropertyCol_clear : public CMibTableColumn {
	CMibLoopPropertyCol_clear();
public:
	CMibLoopPropertyCol_clear(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibLoopPropertyCol_clear() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBLOOPPROPERTYTABLE_H_ */
