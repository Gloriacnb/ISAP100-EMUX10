/*
 * CMibBaseSwitchFunction.h
 *
 *  Created on: 2014-4-4
 *      Author: Administrator
 */

#ifndef CMIBBASESWITCHFUNCTION_H_
#define CMIBBASESWITCHFUNCTION_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	sw_mode,
//	priority_mode,
//	wrr,
	sw_mtu,
	sw_size

};


class CMibBaseSwitchFunction : public CMibTable {
	CMibBaseSwitchFunction();
public:
	CMibBaseSwitchFunction(uint32*, uint32, table_info_T*);
	virtual ~CMibBaseSwitchFunction();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[sw_size];
};


class CMibBaseSwitch_mode : public CMibTableColumn {
	CMibBaseSwitch_mode();
public:
	CMibBaseSwitch_mode(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibBaseSwitch_mode() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibBaseSwitch_mtu : public CMibTableColumn {
	CMibBaseSwitch_mtu();
public:
	CMibBaseSwitch_mtu(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibBaseSwitch_mtu() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBBASESWITCHFUNCTION_H_ */
