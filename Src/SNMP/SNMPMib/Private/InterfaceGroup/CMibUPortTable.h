/*
 * CMibUPortTable.h
 *
 *  Created on: 2013-7-30
 *      Author: Administrator
 */

#ifndef CMIBUPORTTABLE_H_
#define CMIBUPORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	u_port_name,
	u_port_sn,
	u_port_slot,
	u_port_enable,
	u_port_desc,
	u_port_mode,
	u_port_size

};


class CMibUPortTable : public CMibTable {
	CMibUPortTable();
public:
	CMibUPortTable(uint32*, uint32, table_info_T*);
	virtual ~CMibUPortTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[u_port_size];
};

/*
 * column define start
 */

class CMibUPortCol_name : public CMibTableColumn {
	CMibUPortCol_name();
public:
	CMibUPortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibUPortCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibUPortCol_sn : public CMibTableColumn {
	CMibUPortCol_sn();
public:
	CMibUPortCol_sn(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibUPortCol_sn() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibUPortCol_slot : public CMibTableColumn {
	CMibUPortCol_slot();
public:
	CMibUPortCol_slot(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibUPortCol_slot() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibUPortCol_enable : public CMibTableColumn {
	CMibUPortCol_enable();
public:
	CMibUPortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibUPortCol_enable() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};


class CMibUPortCol_desc : public CMibTableColumn {
	CMibUPortCol_desc();
public:
	CMibUPortCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibUPortCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};

class CMibUPortCol_mode : public CMibTableColumn {
	CMibUPortCol_mode();
public:
	CMibUPortCol_mode(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibUPortCol_mode() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};


#endif /* CMIBUPORTTABLE_H_ */
