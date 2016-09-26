/*
 * CMibMappingAddTable.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBMAPPINGADDTABLE_H_
#define CMIBMAPPINGADDTABLE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	mapping_add,
	mapping_count,
	mapping_add_size

}Mib_Mapping_Add_Column_E;


class CMibMappingAddTable : public CMibTable {
	CMibMappingAddTable();
public:
	CMibMappingAddTable(uint32*, uint32, table_info_T*);
	virtual ~CMibMappingAddTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[mapping_add_size];
};


class CMibMappingCol_add : public CMibTableColumn {
	CMibMappingCol_add();
public:
	CMibMappingCol_add(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingCol_add() {};

	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibMappingCol_count : public CMibTableColumn {
	CMibMappingCol_count();
public:
	CMibMappingCol_count(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingCol_count() {};

	virtual int CallbackGet(const index_info_T& index);
};

#endif /* CMIBMAPPINGADDTABLE_H_ */
