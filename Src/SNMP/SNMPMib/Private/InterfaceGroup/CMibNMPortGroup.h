/*
 * CMibNMPortGroup.h
 *
 *  Created on: 2015年11月6日
 *      Author: Administrator
 */

#ifndef CMIBNMPORTGROUP_H_
#define CMIBNMPORTGROUP_H_

#include "CMibGroup.h"

typedef enum {
    table_nmport_list,
    table_nmport_option,
    table_useable_Port,
    table_nmport_size
}Mib_NMPort_Table_E;


class CMibNMPortGroup : public CMibGroup {
    CMibNMPortGroup();
public:
    CMibNMPortGroup(uint32* oid, uint8 oidlen);
    virtual ~CMibNMPortGroup();
    virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
    static table_info_T tableInfo[table_nmport_size];
};

#endif /* CMIBNMPORTGROUP_H_ */
