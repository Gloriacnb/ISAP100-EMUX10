/*
 * CMibETH.h
 *
 *  Created on: 2014-4-16
 *      Author: Administrator
 */

#ifndef CMIBETH_H_
#define CMIBETH_H_


#include "CMibGroup.h"
/*
 *
 */

typedef enum {
	table_eth_config,
	table_eth_size
}Mib_ETH_Table_E;


class CMibETH : public CMibGroup {
	CMibETH();
public:
	CMibETH(uint32* oid, uint8 oidlen);
	virtual ~CMibETH();
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_eth_size];
};

#endif /* CMIBETH_H_ */
