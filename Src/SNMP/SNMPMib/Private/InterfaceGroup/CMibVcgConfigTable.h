/*
 * CMibVcgConfigTable.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBVCGCONFIGTABLE_H_
#define CMIBVCGCONFIGTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	vcg_port_index,
	vcg_port_name,
	vcg_port_lcas,
	vcg_port_member_number,
	vcg_port_member_add,
	vcg_port_member_delete,
	vcg_port_member_clear,
	vcg_port_desc,
	vcg_port_enable,
	vcg_port_size

}Mib_E1_Port_Column_E;


class CMibVcgConfigTable : public CMibTable {
	CMibVcgConfigTable();
public:
	CMibVcgConfigTable(uint32*, uint32, table_info_T*);
	virtual ~CMibVcgConfigTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[vcg_port_size];
};

/*
 * column define start
 */

class CMibVCGPortCol_index : public CMibTableColumn {
	CMibVCGPortCol_index();
public:
	CMibVCGPortCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};


class CMibVCGPortCol_name : public CMibTableColumn {
	CMibVCGPortCol_name();
public:
	CMibVCGPortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};


class CMibVCGPortCol_lcas : public CMibTableColumn {
	CMibVCGPortCol_lcas();
public:
	CMibVCGPortCol_lcas(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_lcas() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};


class CMibVCGPortCol_enable : public CMibTableColumn {
	CMibVCGPortCol_enable();
public:
	CMibVCGPortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_enable() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVCGPortCol_MbNumber : public CMibTableColumn {
	CMibVCGPortCol_MbNumber();
public:
	CMibVCGPortCol_MbNumber(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_MbNumber() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibVCGPortCol_mbadd : public CMibTableColumn {
	CMibVCGPortCol_mbadd();
public:
	CMibVCGPortCol_mbadd(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_mbadd() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVCGPortCol_mbdelete : public CMibTableColumn {
	CMibVCGPortCol_mbdelete();
public:
	CMibVCGPortCol_mbdelete(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_mbdelete() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVCGPortCol_mbclear : public CMibTableColumn {
	CMibVCGPortCol_mbclear();
public:
	CMibVCGPortCol_mbclear(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_mbclear() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVCGPortCol_desc : public CMibTableColumn {
	CMibVCGPortCol_desc();
public:
	CMibVCGPortCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGPortCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

#endif /* CMIBVCGCONFIGTABLE_H_ */
