/*
 * GroupTopology.h
 *
 *  Created on: 2013-7-8
 *      Author: Administrator
 */

#ifndef GROUPTOPOLOGY_H_
#define GROUPTOPOLOGY_H_

#include "CMibGroup.h"

enum {
	table_topology_option,
	table_topology_status,
	table_topology_size
};

class GroupTopology : public CMibGroup {
	GroupTopology();
public:
	GroupTopology(uint32* oid, uint8 oidlen);
	virtual ~GroupTopology();

	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_topology_size];
};

#endif /* GROUPTOPOLOGY_H_ */
