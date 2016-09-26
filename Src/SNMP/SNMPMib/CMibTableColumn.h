/*
 * CMibTableColumn.h
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#ifndef CMIBTABLECOLUMN_H_
#define CMIBTABLECOLUMN_H_

#include "CMibColumn.h"
#include "Mib_define.h"

class CMibTable;
class CMibTableColumn: public CMibColumn {
	CMibTableColumn();
public:
	CMibTableColumn(int sn, uint32* oid, uint32 oidLen, CMibTable*);
	virtual ~CMibTableColumn();

	virtual uint32 GetResponse(CSnmpCell* objpCell);
	virtual uint32 SetResponse(CSnmpCell* objpCell);
	virtual uint32 GetFirstValidOID(CSnmpCell* objpCell);
	virtual uint32 GetNextValidOID(CSnmpCell* objpCell);

	/*
	 * 派生类需根据自己的值类型实现以下函数之一。
	 */
	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet(const index_info_T& index, uint32);

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);

private:
	column_info_T* col_info;
	table_info_T* table_Info;
	uint8 oid_len;
	uint8 pos_index_begin;
	uint8 pos_col;
	CMibTable* table;
	void makeoid(index_info_T&, CSnmpCell*);
	index_info_T extractIndex(CSnmpCell*);
};

#endif /* CMIBTABLECOLUMN_H_ */
