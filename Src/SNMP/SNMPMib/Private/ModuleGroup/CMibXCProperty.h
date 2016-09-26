/*
 * CMibXCProperty.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBXCPROPERTY_H_
#define CMIBXCPROPERTY_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	xc_index,
	xc_west_id,
	xc_east_id,
	xc_name,
	xc_description,
	xc_delete,
	xc_property_size

}Mib_XC_Property_Column_E;


class CMibXCProperty : public CMibTable {
	CMibXCProperty();
public:
	CMibXCProperty(uint32*, uint32, table_info_T*);
	virtual ~CMibXCProperty();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[xc_property_size];
};


class CMibXCPropertyCol_index : public CMibTableColumn {
	CMibXCPropertyCol_index();
public:
	CMibXCPropertyCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXCPropertyCol_westid : public CMibTableColumn {
	CMibXCPropertyCol_westid();
public:
	CMibXCPropertyCol_westid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_westid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXCPropertyCol_eastid : public CMibTableColumn {
	CMibXCPropertyCol_eastid();
public:
	CMibXCPropertyCol_eastid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_eastid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXCPropertyCol_name : public CMibTableColumn {
	CMibXCPropertyCol_name();
public:
	CMibXCPropertyCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibXCPropertyCol_desc : public CMibTableColumn {
	CMibXCPropertyCol_desc();
public:
	CMibXCPropertyCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibXCPropertyCol_delete : public CMibTableColumn {
	CMibXCPropertyCol_delete();
public:
	CMibXCPropertyCol_delete(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_delete() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBXCPROPERTY_H_ */
