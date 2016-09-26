/*
 * CMibSTMOverheadTable.h
 *
 *  Created on: 2013-4-19
 *      Author: Administrator
 */

#ifndef CMIBSTMOVERHEADTABLE_H_
#define CMIBSTMOVERHEADTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	stm_oh_J0_Transmit,
	stm_oh_J0_expected,
	stm_oh_J0_Receive,
	stm_oh_size

}Mib_STM_overhead_Column_E;


class CMibSTMOverheadTable : public CMibTable{
	CMibSTMOverheadTable();
public:
	CMibSTMOverheadTable(uint32*, uint32, table_info_T*);
	virtual ~CMibSTMOverheadTable();

	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[stm_oh_size];
};

class CMibSTMOverheadCol_J0Transmit : public CMibTableColumn {
	CMibSTMOverheadCol_J0Transmit();
public:
	CMibSTMOverheadCol_J0Transmit(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMOverheadCol_J0Transmit() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};


class CMibSTMOverheadCol_J0Expected : public CMibTableColumn {
	CMibSTMOverheadCol_J0Expected();
public:
	CMibSTMOverheadCol_J0Expected(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMOverheadCol_J0Expected() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};


class CMibSTMOverheadCol_J0Receive : public CMibTableColumn {
	CMibSTMOverheadCol_J0Receive();
public:
	CMibSTMOverheadCol_J0Receive(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMOverheadCol_J0Receive() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};


#endif /* CMIBSTMOVERHEADTABLE_H_ */
