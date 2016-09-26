/*
 * PerformanceGroup.h
 *
 *  Created on: 2014-4-17
 *      Author: Administrator
 */

#ifndef PERFORMANCEGROUP_H_
#define PERFORMANCEGROUP_H_


#include "CMibGroup.h"
/*
 *
 */

enum {
	table_eth_performance,
	table_performance_size
};


class PerformanceGroup : public CMibGroup {
	PerformanceGroup();
public:
	PerformanceGroup(uint32* oid, uint8 oidlen);
	virtual ~PerformanceGroup();
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_performance_size];
};


#endif /* PERFORMANCEGROUP_H_ */
