/*
 * CMibXCAddTable.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBXCADDTABLE_H_
#define CMIBXCADDTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	xc_add,
	xc_count,
	xc_add_size

}Mib_XC_Add_Column_E;


class CMibXCAddTable : public CMibTable {
	CMibXCAddTable();
public:
	CMibXCAddTable(uint32*, uint32, table_info_T*);
	virtual ~CMibXCAddTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[xc_add_size];
};


class CMibXCCol_add : public CMibTableColumn {
	CMibXCCol_add();
public:
	CMibXCCol_add(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCCol_add() {};

	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibXCCol_count : public CMibTableColumn {
	CMibXCCol_count();
public:
	CMibXCCol_count(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCCol_count() {};

	virtual int CallbackGet(const index_info_T& index);
};
#endif /* CMIBXCADDTABLE_H_ */
