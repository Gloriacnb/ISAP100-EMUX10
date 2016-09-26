/*
 * CMibE1PortTable.h
 *
 *  Created on: 2013-4-20
 *      Author: Administrator
 */

#ifndef CMIBE1PORTTABLE_H_
#define CMIBE1PORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	e1_port_name,
	e1_port_sn,
	e1_port_slot,
	e1_port_enable,
	e1_port_desc,
	e1_port_size

}Mib_E1_Port_Column_E;


class CMibE1PortTable : public CMibTable {
	CMibE1PortTable();
public:
	CMibE1PortTable(uint32*, uint32, table_info_T*);
	virtual ~CMibE1PortTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[e1_port_size];
};

/*
 * column define start
 */

class CMibE1PortCol_name : public CMibTableColumn {
	CMibE1PortCol_name();
public:
	CMibE1PortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1PortCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibE1PortCol_sn : public CMibTableColumn {
	CMibE1PortCol_sn();
public:
	CMibE1PortCol_sn(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1PortCol_sn() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibE1PortCol_slot : public CMibTableColumn {
	CMibE1PortCol_slot();
public:
	CMibE1PortCol_slot(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1PortCol_slot() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibE1PortCol_enable : public CMibTableColumn {
	CMibE1PortCol_enable();
public:
	CMibE1PortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1PortCol_enable() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};


class CMibE1PortCol_desc : public CMibTableColumn {
	CMibE1PortCol_desc();
public:
	CMibE1PortCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibE1PortCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};


//class CMibE1PortCol_mapping : public CMibTableColumn {
//	CMibE1PortCol_mapping();
//public:
//	CMibE1PortCol_mapping(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
//				: CMibTableColumn(sn, oid, oidLen, table) {
//
//	};
//	virtual ~CMibE1PortCol_mapping() {};
//
//	virtual int CallbackGet(const index_info_T& index);
//};

#endif /* CMIBE1PORTTABLE_H_ */
