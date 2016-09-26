/*
 * CMibVcgMemberTable.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBVCGMEMBERTABLE_H_
#define CMIBVCGMEMBERTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	vcg_member_index,
	vcg_member_sncp,
	vcg_member_size

}Mib_VCG_member_Column_E;


class CMibVcgMemberTable : public CMibTable {
	CMibVcgMemberTable();
public:
	CMibVcgMemberTable(uint32*, uint32, table_info_T*);
	virtual ~CMibVcgMemberTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[vcg_member_size];
};



class CMibVCGMemberCol_index : public CMibTableColumn {
	CMibVCGMemberCol_index();
public:
	CMibVCGMemberCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGMemberCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};


class CMibVCGMemberCol_sncp : public CMibTableColumn {
	CMibVCGMemberCol_sncp();
public:
	CMibVCGMemberCol_sncp(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVCGMemberCol_sncp() {};
	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );

};

#endif /* CMIBVCGMEMBERTABLE_H_ */
