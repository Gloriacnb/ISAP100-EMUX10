/*
 * CMibVFPortTable.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#ifndef CMIBVFPORTTABLE_H_
#define CMIBVFPORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	vf_port_name,
	vf_port_type,
	vf_port_enable,
	vf_port_work_model,
	vf_port_polar_turn,
	vf_port_snd_gain,
	vf_port_rcv_gain,
	vf_port_desc,
	vf_port_size

}Mib_VF_Port_Column_E;


class CMibVFPortTable : public CMibTable {
	CMibVFPortTable();
public:
	CMibVFPortTable(uint32*, uint32, table_info_T*);
	virtual ~CMibVFPortTable();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[vf_port_size];
};

/*
 * column define start
 */

class CMibVFPortCol_name : public CMibTableColumn {
	CMibVFPortCol_name();
public:
	CMibVFPortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVFPortCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibVFPortCol_type : public CMibTableColumn {
	CMibVFPortCol_type();
public:
	CMibVFPortCol_type(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVFPortCol_type() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibVFPortCol_enable : public CMibTableColumn {
	CMibVFPortCol_enable();
public:
	CMibVFPortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVFPortCol_enable() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVFPortCol_mode : public CMibTableColumn {
	CMibVFPortCol_mode();
public:
	CMibVFPortCol_mode(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVFPortCol_mode() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVFPortCol_polar : public CMibTableColumn {
	CMibVFPortCol_polar();
public:
	CMibVFPortCol_polar(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVFPortCol_polar() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVFPortCol_RcvGain : public CMibTableColumn {
	CMibVFPortCol_RcvGain();
public:
	CMibVFPortCol_RcvGain(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVFPortCol_RcvGain() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVFPortCol_SndGain : public CMibTableColumn {
	CMibVFPortCol_SndGain();
public:
	CMibVFPortCol_SndGain(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVFPortCol_SndGain() {};

	virtual int CallbackGet(const index_info_T& index);
	virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibVFPortCol_Description : public CMibTableColumn {
	CMibVFPortCol_Description();
public:
	CMibVFPortCol_Description(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibVFPortCol_Description() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

#endif /* CMIBVFPORTTABLE_H_ */
