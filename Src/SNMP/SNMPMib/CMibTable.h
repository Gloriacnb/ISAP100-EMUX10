/*
 * CMibTable.h
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#ifndef CMIBTABLE_H_
#define CMIBTABLE_H_


#include "CMibEntry.h"
#include "Mib_define.h"

class CMibTable : public CMibEntry {
	table_info_T* tInfo;
	CMibTable();
public:
	CMibTable(uint32* oid, uint32 oidLen, table_info_T*);
	virtual ~CMibTable();

	virtual column_info_T* getColInfo(int sn) = 0;
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen) = 0;
	table_info_T* getTableInfo(void) {
		return tInfo;
	}
	virtual int getFirstIndex(index_info_T*) = 0;
	virtual int getNextIndex(index_info_T*) = 0;

	void makeColumnOid(void);
};

#endif /* CMIBTABLE_H_ */
