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
	//Set����Ӧ����
	virtual uint32 SetResponse(CSnmpCell* objpCell);
	//GetNext���÷���1����õ�һ�������OID
	virtual uint32 GetFirstValidOID(CSnmpCell* objpCell);
	//GetNext���÷���2�������һ�������OID
	virtual uint32 GetNextValidOID(CSnmpCell* objpCell);
};

#endif /* CMIBVC12PORT_H_ */
