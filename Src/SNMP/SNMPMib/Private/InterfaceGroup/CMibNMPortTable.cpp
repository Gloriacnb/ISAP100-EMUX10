/*
 * CMibNMPortTable.cpp
 *
 *  Created on: 2015骞�1鏈�鏃�
 *      Author: Administrator
 */

#include "CMibNMPortTable.h"
#include <string.h>
#include "CCommonDefine.h"
#include "CUpE1Port.h"

column_info_T CMibNMPortTable::colInfo[nmport_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {4, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {5, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {6, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
        {7, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
        {8, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {9, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {10, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
        {11, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


CMibNMPortTable::CMibNMPortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibNMPortTable::~CMibNMPortTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibNMPortTable::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* CMibNMPortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case nmport_index:
        return new CMibNMPortCol_index(sn, oid, oidLen, this);
    case nmport_name:
        return new CMibNMPortCol_name(sn, oid, oidLen, this);
    case nmport_enable:
        return new CMibNMPortCol_enable(sn, oid, oidLen, this);
    case nmport_type:
        return new CMibNMPortCol_type(sn, oid, oidLen, this);
    case nmport_link_info:
        return new CMibNMPortCol_linkinfo(sn, oid, oidLen, this);
    case nmport_nm_tsadd:
        return new CMibNMPortCol_tsadd(sn, oid, oidLen, this);
    case nmport_nm_tsdelete:
        return new CMibNMPortCol_tsdelete(sn, oid, oidLen, this);
    case nmport_topo_direction:
        return new CMibNMPortCol_topodirection(sn, oid, oidLen, this);
    case nmport_topo_info:
        return new CMibNMPortCol_topoInfo(sn, oid, oidLen, this);
    case nmport_description:
        return new CMibNMPortCol_description(sn, oid, oidLen, this);
    case nmport_tsmap:
        return new CMibNMPortCol_tsmap(sn, oid, oidLen, this);
    default:
        return 0;
    }
}
int CMibNMPortTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    CUpE1Port* nmp = CUpE1Port::getFirstInstance();
    if( nmp ) {
        uint32 uid = nmp->getUID();
        index->index[1] = uid;
        return 1;
    }
    return -1;
}
int CMibNMPortTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    CUpE1Port* nmp = CUpE1Port::getNextInstance(index->index[1]);
    if( nmp ) {
        uint32 uid = nmp->getUID();
        index->index[1] = uid;
        return 1;
    }
    return -1;
}


int CMibNMPortCol_index::CallbackGet(const index_info_T& index) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        return nmp->getUID();
    }
    return -1;
}

int CMibNMPortCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        strcpy((char*)name,nmp->getName().c_str());
        *len = nmp->getName().size();
        return 1;
    }
    return -1;
}

int CMibNMPortCol_enable::CallbackGet(const index_info_T& index) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        return nmp->getEnable();
    }
    return -1;
}
int CMibNMPortCol_enable::callbackSet( const index_info_T& index, uint32 en) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        if( nmp->setEnable(en) ) {
            return 0x5A;
        }
    }
    return -1;
}


int CMibNMPortCol_type::CallbackGet(const index_info_T& index) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        return nmp->getType();
    }
    return -1;
}

int CMibNMPortCol_type::callbackSet( const index_info_T& index, uint32 type) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        if( nmp->setType(type) ) {
            return 0x5A;
        }
    }
    return -1;

}

int CMibNMPortCol_linkinfo::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        std::string s = nmp->getTsInfo();
        strcpy((char*)buf, s.c_str());
        *len = s.size();
        return 1;
    }
    return -1;
}

int CMibNMPortCol_tsadd::callbackSet( const index_info_T& index, uint32 ts) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        if( nmp->addNMTs(ts) ) {
            return 0x5A;
        }
    }
    return -1;
}

int CMibNMPortCol_tsdelete::callbackSet( const index_info_T& index, uint32 ts) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        if( nmp->deleteNMTs(ts) ) {
            return 0x5A;
        }
    }
    return -1;

}

int CMibNMPortCol_topodirection::CallbackGet(const index_info_T& index) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        return nmp->getTopoDirection();
    }
    return -1;
}
int CMibNMPortCol_topodirection::callbackSet( const index_info_T& index, uint32 swport) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        if( nmp->setTopoDirection(swport) ) {
            return 0x5A;
        }
    }
    return -1;
}

int CMibNMPortCol_topoInfo::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        memcpy( buf, nmp->getTopoInfo(), 4);
        *len = 4;
    }
    return 1;
}

int CMibNMPortCol_description::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        uint8 l = 0;
        uint8* d = nmp->getPortDescription(&l);
        memcpy(buf, d, l);
        *len = l;
        return 0x5a;
    }
    return -1;

}

int CMibNMPortCol_description::callbackSet( const index_info_T& index, uint8* buf, uint32 len) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        if( nmp->setPortDescription(buf, len) ) {
            return 0x5A;
        }
    }
    return -1;

}

int CMibNMPortCol_tsmap::CallbackGet(const index_info_T& index) {
     CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
     if( nmp ) {
         return nmp->getTsMap();
     }
     return -1;
}

int CMibNMPortCol_tsmap::callbackSet( const index_info_T& index, uint32 value) {
    CUpE1Port* nmp = CUpE1Port::getInstance(index.index[1]);
    if( nmp ) {
        if( nmp->setTsMap(value) ) {
            return 0x5A;
        }
    }
    return -1;
}

