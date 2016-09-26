/*
 * CMibXE1PortTable.h
 *
 *  Created on: 2015Äê12ÔÂ30ÈÕ
 *      Author: Administrator
 */

#ifndef CMIBXE1PORTTABLE_H_
#define CMIBXE1PORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	xe1_port_index,
	xe1_port_name,
	xe1_port_sn,
	xe1_port_mode,
	xe1_port_enable,
	xe1_port_desc,
	xe1_port_size

}Mib_XE1_Port_Column_E;


class CMibXE1PortTable : public CMibTable {
	CMibXE1PortTable();
public:
	CMibXE1PortTable(uint32*, uint32, table_info_T*);
	virtual ~CMibXE1PortTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[xe1_port_size];
};

class CMibXE1PortCol_uid : public CMibTableColumn {
	CMibXE1PortCol_uid();
public:
	CMibXE1PortCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1PortCol_uid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXE1PortCol_name : public CMibTableColumn {
	CMibXE1PortCol_name();
public:
	CMibXE1PortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1PortCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibXE1PortCol_sn : public CMibTableColumn {
	CMibXE1PortCol_sn();
public:
	CMibXE1PortCol_sn(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1PortCol_sn() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXE1PortCol_mode : public CMibTableColumn {
	CMibXE1PortCol_mode();
public:
	CMibXE1PortCol_mode(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1PortCol_mode() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibXE1PortCol_enable : public CMibTableColumn {
	CMibXE1PortCol_enable();
public:
	CMibXE1PortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1PortCol_enable() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};


class CMibXE1PortCol_desc : public CMibTableColumn {
	CMibXE1PortCol_desc();
public:
	CMibXE1PortCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXE1PortCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};

#endif /* CMIBXE1PORTTABLE_H_ */
