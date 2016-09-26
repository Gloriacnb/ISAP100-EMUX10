/*
 * CMibVersionInfoTable.h
 *
 *  Created on: 2013-5-17
 *      Author: Administrator
 */

#ifndef CMIBVERSIONINFOTABLE_H_
#define CMIBVERSIONINFOTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	version_index,
	version_name,
	version_number,
	version_column_size

}Mib_Version_Column_E;


class CMibVersionInfoTable : public CMibTable {
	CMibVersionInfoTable();
public:
	CMibVersionInfoTable(uint32*, uint32, table_info_T*);
	virtual ~CMibVersionInfoTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[version_column_size];
};

/*
 * column define start
 */
class CMibVersionCol_index : public CMibTableColumn {
	CMibVersionCol_index();
public:
	CMibVersionCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVersionCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibVersionCol_name : public CMibTableColumn {
	CMibVersionCol_name();
public:
	CMibVersionCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVersionCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibVersionCol_number : public CMibTableColumn {
	CMibVersionCol_number();
public:
	CMibVersionCol_number(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVersionCol_number() {};

	virtual int CallbackGet(const index_info_T& index);
};



#endif /* CMIBVERSIONINFOTABLE_H_ */
