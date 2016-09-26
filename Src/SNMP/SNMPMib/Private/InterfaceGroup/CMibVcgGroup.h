/*
 * CMibVcgGroup.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBVCGGROUP_H_
#define CMIBVCGGROUP_H_

#include "CMibGroup.h"
/*
 *
 */

typedef enum {
	table_vcg_config,
	table_vcg_member,
	table_vcg_size
}Mib_VCG_Table_E;


class CMibVcgGroup : public CMibGroup {
	CMibVcgGroup();
public:
	CMibVcgGroup(uint32* oid, uint8 oidlen);
	virtual ~CMibVcgGroup();
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_vcg_size];
};
#endif /* CMIBVCGGROUP_H_ */
