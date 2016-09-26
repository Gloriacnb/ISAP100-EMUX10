/*
 * TableDevice.h
 *
 *  Created on: 2013-7-9
 *      Author: Administrator
 */

#ifndef TABLEDEVICE_H_
#define TABLEDEVICE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
	device_index,
	device_name,
	device_typeID,
	device_desc,
	device_status,
	device_net_position,
	device_Chassis,
	device_slot_number,
	device_special_command,
	device_clock_source,
	device_active_card_number,
	device_remote_reset,
	device_pcm_clock,
	device_column_size

};

class TableDevice : public CMibTable {
	TableDevice();
public:
	TableDevice(uint32*, uint32, table_info_T*);
	virtual ~TableDevice();

	virtual column_info_T* getColInfo(int sn);

	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[device_column_size];
};


class TableDeviceCol_index : public CMibTableColumn {
	TableDeviceCol_index();
public:
	TableDeviceCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class TableDeviceCol_name : public CMibTableColumn {
	TableDeviceCol_name();
public:
	TableDeviceCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class TableDeviceCol_typeID : public CMibTableColumn {
	TableDeviceCol_typeID();
public:
	TableDeviceCol_typeID(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_typeID() {};

	virtual int CallbackGet(const index_info_T& index);
};


class TableDeviceCol_desc : public CMibTableColumn {
	TableDeviceCol_desc();
public:
	TableDeviceCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class TableDeviceCol_status : public CMibTableColumn {
	TableDeviceCol_status();
public:
	TableDeviceCol_status(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_status() {};

	virtual int CallbackGet(const index_info_T& index);
};

class TableDeviceCol_netpos : public CMibTableColumn {
	TableDeviceCol_netpos();
public:
	TableDeviceCol_netpos(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_netpos() {};

	virtual int CallbackGet(const index_info_T& index);
};

class TableDeviceCol_chassis : public CMibTableColumn {
	TableDeviceCol_chassis();
public:
	TableDeviceCol_chassis(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_chassis() {};

	virtual int CallbackGet(const index_info_T& index);
};

class TableDeviceCol_slotnum : public CMibTableColumn {
	TableDeviceCol_slotnum();
public:
	TableDeviceCol_slotnum(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_slotnum() {};

	virtual int CallbackGet(const index_info_T& index);
};

class TableDeviceCol_command : public CMibTableColumn {
	TableDeviceCol_command();
public:
	TableDeviceCol_command(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_command() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class TableDeviceCol_clk : public CMibTableColumn {
	TableDeviceCol_clk();
public:
	TableDeviceCol_clk(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_clk() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class TableDeviceCol_cardnum : public CMibTableColumn {
	TableDeviceCol_cardnum();
public:
	TableDeviceCol_cardnum(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_cardnum() {};

	virtual int CallbackGet(const index_info_T& index);
};


class TableDeviceCol_rmtreset : public CMibTableColumn {
	TableDeviceCol_rmtreset();
public:
	TableDeviceCol_rmtreset(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_rmtreset() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};

class TableDeviceCol_pcmclk : public CMibTableColumn {
	TableDeviceCol_pcmclk();
public:
	TableDeviceCol_pcmclk(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableDeviceCol_pcmclk() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* TABLEDEVICE_H_ */
