/*
 * SNMP_Process.cpp
 *
 *  Created on: 2013-2-20
 *      Author: Administrator
 */

#include "SNMP_Process.h"

#include "CSnmpMib.h"
#include "EZ_types.h"
#include "CUDPData.h"

CSnmpMib snmp;

uint16 Process_SNMP(uint8 socket, uint8 *remip, uint16 remport, uint8 *buf, uint16 len) {
	CUDPData udp(remip, remport, buf, len);
	snmp.GetSnmpDataInOut()->ReceiverData(&udp);
	return 0;
}

void Init_SNMP(void) {
	snmp.InitialClassObject();

}
