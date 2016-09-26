/*
 * CMibSTMConfig.h
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#ifndef CMIBSTMCONFIG_H_
#define CMIBSTMCONFIG_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	stm_cfg_uid,
	stm_cfg_name,
	stm_cfg_enable,
	stm_cfg_als_enable,
	stm_cfg_port_backup,
	stm_cfg_desc,
	stm_cfg_als_mode,
	stm_cfg_size

}Mib_STM_config_Column_E;

class CMibSTMConfig : public CMibTable {
	CMibSTMConfig();
public:
	CMibSTMConfig(uint32*, uint32, table_info_T*);
	virtual ~CMibSTMConfig();

	virtual column_info_T* getColInfo(int sn);

	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[stm_cfg_size];
};


class CMibSTMConfigCol_uid : public CMibTableColumn {
	CMibSTMConfigCol_uid();
public:
	CMibSTMConfigCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibSTMConfigCol_uid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibSTMConfigCol_name : public CMibTableColumn {
	CMibSTMConfigCol_name();
public:
	CMibSTMConfigCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMConfigCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibSTMConfigCol_enable : public CMibTableColumn {
	CMibSTMConfigCol_enable();
public:
	CMibSTMConfigCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMConfigCol_enable() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibSTMConfigCol_als : public CMibTableColumn {
	CMibSTMConfigCol_als();
public:
	CMibSTMConfigCol_als(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMConfigCol_als() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibSTMConfigCol_port_backup : public CMibTableColumn {
	CMibSTMConfigCol_port_backup();
public:
	CMibSTMConfigCol_port_backup(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMConfigCol_port_backup() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibSTMConfigCol_desc : public CMibTableColumn {
	CMibSTMConfigCol_desc();
public:
	CMibSTMConfigCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMConfigCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};

class CMibSTMConfigCol_alsmode : public CMibTableColumn {
	CMibSTMConfigCol_alsmode();
public:
	CMibSTMConfigCol_alsmode(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMConfigCol_alsmode() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBSTMCONFIG_H_ */
