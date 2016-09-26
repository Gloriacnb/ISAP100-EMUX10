/*
 * CMibVC12Port.h
 *
 *  Created on: 2013-3-3
 *      Author: Administrator
 */

#ifndef CMIBVC12PORT_H_
#define CMIBVC12PORT_H_

#include "CMibEntry.h"
#include "CMibColumn.h"

class CSnmpCell;

class CMibVC12Port : public CMibEntry{
public:
	CMibVC12Port();
	virtual ~CMibVC12Port();
	virtual uint32 InitialGroup(void);
};


class CMibVC12PortColumn : public CMibColumn {
public:
	CMibVC12PortColumn() {};
	virtual ~CMibVC12PortColumn() {};

	virtual uint32 GetResponse(CSnmpCell* objpCell);
	//Set的响应方法
	virtual uint32 SetResponse(CSnmpCell* objpCell);
	//GetNext调用方法1：获得第一个对象的OID
	virtual uint32 GetFirstValidOID(CSnmpCell* objpCell);
	//GetNext调用方法2：获得下一个对象的OID
	virtual uint32 GetNextValidOID(CSnmpCell* objpCell);
};

#endif /* CMIBVC12PORT_H_ */
