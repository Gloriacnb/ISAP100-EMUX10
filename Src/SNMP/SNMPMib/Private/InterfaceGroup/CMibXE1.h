/*
 * CMibXE1.h
 *
 *  Created on: 2015Äê12ÔÂ30ÈÕ
 *      Author: Administrator
 */

#ifndef CMIBXE1_H_
#define CMIBXE1_H_

#include "CMibGroup.h"

typedef enum {
	table_XE1_Port,
	table_XE1_alarm_property,
	table_XE1_size
}Mib_XE1_Table_E;


class CMibXE1 : public CMibGroup {
	CMibXE1();
public:
	CMibXE1(uint32* oid, uint8 oidlen);
	virtual ~CMibXE1();
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_XE1_size];
};

#endif /* CMIBXE1_H_ */
