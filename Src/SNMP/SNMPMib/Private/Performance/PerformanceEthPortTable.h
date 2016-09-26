/*
 * PerformanceEthPortTable.h
 *
 *  Created on: 2014-4-17
 *      Author: Administrator
 */

#ifndef PERFORMANCEETHPORTTABLE_H_
#define PERFORMANCEETHPORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	eth_tx_counter,
	eth_rx_counter,
	eth_rx_drop_counter,
	eth_rx_crcerr_counter,
	eth_performance_size

};


class PerformanceEthPortTable : public CMibTable {
	PerformanceEthPortTable();
public:
	PerformanceEthPortTable(uint32*, uint32, table_info_T*);
	virtual ~PerformanceEthPortTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[eth_performance_size];
};


class PerformanceEth_tx : public CMibTableColumn {
	PerformanceEth_tx();
public:
	PerformanceEth_tx(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~PerformanceEth_tx() {};

	virtual int CallbackGet(const index_info_T& index);
};

class PerformanceEth_rx : public CMibTableColumn {
	PerformanceEth_rx();
public:
	PerformanceEth_rx(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~PerformanceEth_rx() {};

	virtual int CallbackGet(const index_info_T& index);
};

class PerformanceEth_drop : public CMibTableColumn {
	PerformanceEth_drop();
public:
	PerformanceEth_drop(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~PerformanceEth_drop() {};

	virtual int CallbackGet(const index_info_T& index);
};

class PerformanceEth_crc : public CMibTableColumn {
	PerformanceEth_crc();
public:
	PerformanceEth_crc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~PerformanceEth_crc() {};

	virtual int CallbackGet(const index_info_T& index);
};

#endif /* PERFORMANCEETHPORTTABLE_H_ */
