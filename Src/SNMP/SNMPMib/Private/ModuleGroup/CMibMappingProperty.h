/*
 * CMibMappingProperty.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBMAPPINGPROPERTY_H_
#define CMIBMAPPINGPROPERTY_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	mapping_index,
	mapping_west_id,
	mapping_east_id,
	mapping_name,
	mapping_description,
	mapping_delete,
	mappint_sncp,
	mapping_property_size

}Mib_Mapping_Property_Column_E;


class CMibMappingProperty : public CMibTable {
	CMibMappingProperty();
public:
	CMibMappingProperty(uint32*, uint32, table_info_T*);
	virtual ~CMibMappingProperty();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[mapping_property_size];
};


class CMibMappingPropertyCol_index : public CMibTableColumn {
	CMibMappingPropertyCol_index();
public:
	CMibMappingPropertyCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingPropertyCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibMappingPropertyCol_westid : public CMibTableColumn {
	CMibMappingPropertyCol_westid();
public:
	CMibMappingPropertyCol_westid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingPropertyCol_westid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibMappingPropertyCol_eastid : public CMibTableColumn {
	CMibMappingPropertyCol_eastid();
public:
	CMibMappingPropertyCol_eastid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingPropertyCol_eastid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibMappingPropertyCol_name : public CMibTableColumn {
	CMibMappingPropertyCol_name();
public:
	CMibMappingPropertyCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingPropertyCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibMappingPropertyCol_desc : public CMibTableColumn {
	CMibMappingPropertyCol_desc();
public:
	CMibMappingPropertyCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingPropertyCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibMappingPropertyCol_delete : public CMibTableColumn {
	CMibMappingPropertyCol_delete();
public:
	CMibMappingPropertyCol_delete(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingPropertyCol_delete() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibMappingPropertyCol_sncp : public CMibTableColumn {
	CMibMappingPropertyCol_sncp();
public:
	CMibMappingPropertyCol_sncp(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibMappingPropertyCol_sncp() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBMAPPINGPROPERTY_H_ */
