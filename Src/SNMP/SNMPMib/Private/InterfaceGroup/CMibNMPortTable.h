/*
 * CMibNMPortTable.h
 *
 *  Created on: 2015年11月6日
 *      Author: Administrator
 */

#ifndef CMIBNMPORTTABLE_H_
#define CMIBNMPORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
    nmport_index,
    nmport_name,
    nmport_enable,
    nmport_type,
    nmport_link_info,
    nmport_nm_tsadd,
    nmport_nm_tsdelete,
    nmport_topo_direction, //swport id
    nmport_topo_info,
    nmport_description,
    nmport_tsmap,
    nmport_size
}Mib_E1_Port_Column_E;


class CMibNMPortTable : public CMibTable {
    CMibNMPortTable();
public:
    CMibNMPortTable(uint32*, uint32, table_info_T*);
    virtual ~CMibNMPortTable();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[nmport_size];
};

/*
 * column define start
 */

class CMibNMPortCol_index : public CMibTableColumn {
    CMibNMPortCol_index();
public:
    CMibNMPortCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_index() {};

    virtual int CallbackGet(const index_info_T& index);
};


class CMibNMPortCol_name : public CMibTableColumn {
    CMibNMPortCol_name();
public:
    CMibNMPortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibNMPortCol_enable : public CMibTableColumn {
    CMibNMPortCol_enable();
public:
    CMibNMPortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_enable() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibNMPortCol_type : public CMibTableColumn {
    CMibNMPortCol_type();
public:
    CMibNMPortCol_type(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_type() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibNMPortCol_linkinfo : public CMibTableColumn {
    CMibNMPortCol_linkinfo();
public:
    CMibNMPortCol_linkinfo(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_linkinfo() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibNMPortCol_tsadd : public CMibTableColumn {
    CMibNMPortCol_tsadd();
public:
    CMibNMPortCol_tsadd(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_tsadd() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibNMPortCol_tsdelete : public CMibTableColumn {
    CMibNMPortCol_tsdelete();
public:
    CMibNMPortCol_tsdelete(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_tsdelete() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibNMPortCol_topodirection : public CMibTableColumn {
    CMibNMPortCol_topodirection();
public:
    CMibNMPortCol_topodirection(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_topodirection() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibNMPortCol_topoInfo : public CMibTableColumn {
    CMibNMPortCol_topoInfo();
public:
    CMibNMPortCol_topoInfo(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_topoInfo() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibNMPortCol_description : public CMibTableColumn {
    CMibNMPortCol_description();
public:
    CMibNMPortCol_description(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_description() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
    virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibNMPortCol_tsmap : public CMibTableColumn {
    CMibNMPortCol_tsmap();
public:
    CMibNMPortCol_tsmap(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibNMPortCol_tsmap() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};


#endif /* CMIBNMPORTTABLE_H_ */
