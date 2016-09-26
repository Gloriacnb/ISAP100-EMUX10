/*
 * CMibSTM.h
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#ifndef CMIBSTM_H_
#define CMIBSTM_H_

#include "CMibGroup.h"

typedef enum {
	table_stm_alarm_property,
	table_stm_config,
	table_stm_overhead,
	table_stm_size
}Mib_STM_Table_E;

class CMibSTM : public CMibGroup {
	CMibSTM();
public:
	CMibSTM(uint32* oid, uint8 oidlen);
	virtual ~CMibSTM();

//	virtual table_info_T* getTableInfo(int sn);
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_stm_size];
};

#endif /* CMIBSTM_H_ */
