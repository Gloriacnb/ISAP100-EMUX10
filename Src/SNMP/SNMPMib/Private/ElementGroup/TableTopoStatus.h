/*
 * TableTopoStatus.h
 *
 *  Created on: 2013-7-12
 *      Author: Administrator
 */

#ifndef TABLETOPOSTATUS_H_
#define TABLETOPOSTATUS_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	NM_Channel_uid, upstream_port_uid, upStream_device_ip, local_port_speed,

	topo_status_size
};

class TableTopoStatus: public CMibTable {
	TableTopoStatus();
public:
	TableTopoStatus(uint32*, uint32, table_info_T*);
	virtual ~TableTopoStatus();

	virtual column_info_T* getColInfo(int sn);

	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[topo_status_size];
};

class ColTopoStatus_uid: public CMibTableColumn {
	ColTopoStatus_uid();
public:
	ColTopoStatus_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table) :
			CMibTableColumn(sn, oid, oidLen, table) {

	}
	;
	virtual ~ColTopoStatus_uid() {
	}
	;
	virtual int CallbackGet(const index_info_T& index);
};

class ColTopoStatus_port: public CMibTableColumn {
	ColTopoStatus_port();
public:
	ColTopoStatus_port(int sn, uint32* oid, uint32 oidLen, CMibTable* table) :
			CMibTableColumn(sn, oid, oidLen, table) {

	}
	;
	virtual ~ColTopoStatus_port() {
	}
	;
	virtual int CallbackGet(const index_info_T& index);
};

class ColTopoStatus_ip: public CMibTableColumn {
	ColTopoStatus_ip();
public:
	ColTopoStatus_ip(int sn, uint32* oid, uint32 oidLen, CMibTable* table) :
			CMibTableColumn(sn, oid, oidLen, table) {

	}
	;
	virtual ~ColTopoStatus_ip() {
	}
	;
	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class ColTopoStatus_speed: public CMibTableColumn {
	ColTopoStatus_speed();
public:
	ColTopoStatus_speed(int sn, uint32* oid, uint32 oidLen, CMibTable* table) :
			CMibTableColumn(sn, oid, oidLen, table) {

	}
	;
	virtual ~ColTopoStatus_speed() {
	}
	;
	virtual int CallbackGet(const index_info_T& index);
};

#endif /* TABLETOPOSTATUS_H_ */
