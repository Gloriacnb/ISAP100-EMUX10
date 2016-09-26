/*
 * CMibDataPortTable.h
 *
 *  Created on: 2013-6-17
 *      Author: Administrator
 */

#ifndef CMIBDATAPORTTABLE_H_
#define CMIBDATAPORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	dt_port_name,
	dt_port_type,
	dt_port_enable,
	dt_port_desc,
	dt_port_size

}Mib_DT_Port_Column_E;


class CMibDataPortTable : public CMibTable {
	CMibDataPortTable();
public:
	CMibDataPortTable(uint32*, uint32, table_info_T*);
	virtual ~CMibDataPortTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[dt_port_size];
};

/*
 * column define start
 */

class CMibDataPortCol_name : public CMibTableColumn {
	CMibDataPortCol_name();
public:
	CMibDataPortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibDataPortCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibDataPortCol_type : public CMibTableColumn {
	CMibDataPortCol_type();
public:
	CMibDataPortCol_type(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibDataPortCol_type() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibDataPortCol_enable : public CMibTableColumn {
	CMibDataPortCol_enable();
public:
	CMibDataPortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibDataPortCol_enable() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibDataPortCol_Description : public CMibTableColumn {
	CMibDataPortCol_Description();
public:
	CMibDataPortCol_Description(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibDataPortCol_Description() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

#endif /* CMIBDATAPORTTABLE_H_ */
