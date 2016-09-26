/*
 * CMibTS.h
 *
 *  Created on: 2013-4-26
 *      Author: Administrator
 */

#ifndef CMIBTS_H_
#define CMIBTS_H_


#include "CMibGroup.h"

typedef enum {
	table_ts_channel,
	table_ts_vf_port,
	table_ts_vf_alarm_property,
	table_ts_data_port,
	table_ts_data_alarm_property,
	table_ts_size
}Mib_TS_Table_E;

class CMibTS : public CMibGroup {
	CMibTS();
public:
	CMibTS(uint32* oid, uint8 oidlen);
	virtual ~CMibTS();

//	virtual table_info_T* getTableInfo(int sn);
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_ts_size];
};


#endif /* CMIBTS_H_ */
