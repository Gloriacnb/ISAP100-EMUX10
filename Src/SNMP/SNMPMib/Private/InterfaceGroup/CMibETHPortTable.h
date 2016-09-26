/*
 * CMibETHPortTable.h
 *
 *  Created on: 2014-4-16
 *      Author: Administrator
 */

#ifndef CMIBETHPORTTABLE_H_
#define CMIBETHPORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	eth_port_index,
	eth_port_name,
	eth_port_enable,
	eth_port_speed,
	eth_port_duplex,
	eth_port_pause,
	eth_port_auto,
	eth_port_desc,
	eth_port_linktype,
	eth_port_PVID,
	eth_port_EVIDlst,
	eth_port_addevid,
	eth_port_rmvevid,
	eth_port_size

};


class CMibETHPortTable : public CMibTable {
	CMibETHPortTable();
public:
	CMibETHPortTable(uint32*, uint32, table_info_T*);
	virtual ~CMibETHPortTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[eth_port_size];
};


/*
 * column define start
 */
class CMibETHPortCol_index : public CMibTableColumn {
    CMibETHPortCol_index();
public:
    CMibETHPortCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibETHPortCol_index() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibETHPortCol_name : public CMibTableColumn {
	CMibETHPortCol_name();
public:
	CMibETHPortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibETHPortCol_enable : public CMibTableColumn {
	CMibETHPortCol_enable();
public:
	CMibETHPortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_enable() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibETHPortCol_speed : public CMibTableColumn {
	CMibETHPortCol_speed();
public:
	CMibETHPortCol_speed(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_speed() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibETHPortCol_duplex : public CMibTableColumn {
	CMibETHPortCol_duplex();
public:
	CMibETHPortCol_duplex(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_duplex() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibETHPortCol_pause : public CMibTableColumn {
	CMibETHPortCol_pause();
public:
	CMibETHPortCol_pause(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_pause() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibETHPortCol_mtu : public CMibTableColumn {
	CMibETHPortCol_mtu();
public:
	CMibETHPortCol_mtu(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_mtu() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibETHPortCol_desc : public CMibTableColumn {
	CMibETHPortCol_desc();
public:
	CMibETHPortCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};

class CMibETHPortCol_linktype : public CMibTableColumn {
	CMibETHPortCol_linktype();
public:
	CMibETHPortCol_linktype(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_linktype() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibETHPortCol_pvid : public CMibTableColumn {
	CMibETHPortCol_pvid();
public:
	CMibETHPortCol_pvid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_pvid() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibETHPortCol_evidlst : public CMibTableColumn {
	CMibETHPortCol_evidlst();
public:
	CMibETHPortCol_evidlst(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_evidlst() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibETHPortCol_addevid : public CMibTableColumn {
	CMibETHPortCol_addevid();
public:
	CMibETHPortCol_addevid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_addevid() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibETHPortCol_rmvevid : public CMibTableColumn {
	CMibETHPortCol_rmvevid();
public:
	CMibETHPortCol_rmvevid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibETHPortCol_rmvevid() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBETHPORTTABLE_H_ */
