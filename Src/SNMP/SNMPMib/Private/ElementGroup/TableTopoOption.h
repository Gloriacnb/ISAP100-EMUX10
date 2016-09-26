/*
 * TableTopoOption.h
 *
 *  Created on: 2013-7-12
 *      Author: Administrator
 */

#ifndef TABLETOPOOPTION_H_
#define TABLETOPOOPTION_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	topo_start_search,
	topo_option_size
};

class TableTopoOption : public CMibTable {
	TableTopoOption();
public:
	TableTopoOption(uint32*, uint32, table_info_T*);
	virtual ~TableTopoOption();

	virtual column_info_T* getColInfo(int sn);

	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[topo_option_size];
};

class TableTopoOptionCol_search : public CMibTableColumn {
	TableTopoOptionCol_search();
public:
	TableTopoOptionCol_search(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableTopoOptionCol_search() {};
	virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* TABLETOPOOPTION_H_ */
