/*
 * TopoManager.cpp
 *
 *  Created on: 2013-7-12
 *      Author: Administrator
 */

#include "TopoManager.h"
#include "DCCChannelSnd.h"
#include "PriPacket.h"
#include "DeviceLocal.h"
#include "DCCChannelRcv.h"
#include <string.h>
#include "SwitchPort.h"
#include "SwitchPortInner.h"
#include <rtl.h>
#include "Task_define.h"


uint8 TopoPkt::strPkt[28] = {0};
//uint8 TopoManager::Topoing = 0;
enum {TopoTimeOut = 10};

__task void taskTopoAging(void);

TopoPkt::TopoPkt() {
	strPkt[0] = strPkt[1] = strPkt[2] = strPkt[3] = 0;

}
TopoPkt::~TopoPkt() {

}

void TopoPkt::initial() {
	memcpy( &strPkt[4], PriPacket::multicastAddress, 6);
	memcpy( &strPkt[10], DeviceLocal::instance().GetDeviceAttributeObject().ReadMACAddress(), 6);
	memcpy( &strPkt[20], DeviceLocal::instance().GetDeviceAttributeObject().ReadExternalIP(), 4);
	memcpy( &strPkt[24], DeviceLocal::instance().GetDeviceAttributeObject().ReadExternalMask(), 4);
}

uint8* TopoPkt::getPkt(uint32* len) {
	*len = 28;
	return strPkt;
}

TopoPkt TopoManager::pkt;

TopoManager::TopoManager() {
	// TODO Auto-generated constructor stub
}

TopoManager::~TopoManager() {
	// TODO Auto-generated destructor stub
}

void TopoManager::sendTopoPkt() {
	DCCChannelSnd* ch = DCCChannelSnd::getFirstSndDcc();
//	pkt.initial();
	uint32 head = 0x80000000;
	while( ch ) {
		pkt.setSndPort(ch->getPortUID());
		pkt.setPriHead(head++);
		uint32 len = 0;
		uint8* d = pkt.getPkt(&len);
		ch->sendData(d, len);
		ch = DCCChannelSnd::getNextSndDcc(ch->getUID());
	}

}


void TopoManager::startTopoSearch() {
//    if( Topoing ) {
//    }
//    else {
//        Topoing = 10;
	pkt.initial();
		DCCChannelRcv* rch = DCCChannelRcv::getFirstRcvDcc();
		uint8 data[4] = {0};
		while( rch ) {
			rch->setUpStreamIP(data);
			rch->setUpStreamIpMask(data);
			rch->setUpStreamPortUid(0);
			rch = DCCChannelRcv::getNextRcvDcc(rch->getUID());
		}
//		sendTopoPkt();
        os_tsk_create(taskTopoAging, P_Agint_MAC);
//    }
}


void TopoManager::proccessTopoSearch(PriPacket& p) {
    if( ifMyPacket(p) ) {
        return;
    }
//    if( Topoing == 0 ) {
//        startTopoSearch();
//    }
	uint16 len = 0;
	uint8* data = p.getStdStream(&len);
	if( data == 0 || len != 24 ) {
		return;
	}
	/* ����������Ϣ */
	SwitchPortInner* port = (SwitchPortInner*)SwitchPort::getSwitchPort(p.getSourcePort());
	if( port ) {
		DCCChannelRcv* ch = port->currentRcvCh;
		if( ch ) {
			uint32 uid = (data[12] << 24) | (data[13] << 16) | (data[14] << 8) | (data[15] << 0);
			ch->setUpStreamPortUid(uid);
			ch->setUpStreamIP(&data[16]);
			ch->setUpStreamIpMask(&data[20]);
			ch->resetAgingCounter(); //接收到拓扑包后，重置老化计数
		}
	}
}

bool TopoManager::ifMyPacket(PriPacket& pkt) {
    uint8* myMAC = DeviceLocal::instance().GetDeviceAttributeObject().GetMACAddress();
    uint8* mac = pkt.getSrcMAC();
    for (int i = 0; i < 6; ++i) {
        if( myMAC[i] != mac[i] ) {
            return false;
        }
    }
    return true;
}

//__task void taskTopoAging() {
//
//    while( 1 ) {
//        os_dly_wait(100);
//        if( --TopoManager::Topoing == 0 ) {
//
//            os_tsk_delete_self();
//        }
//    }
//}

/*
 * 维护拓扑的心跳发送，并处理结果的老化
 * 以10s为周期定时发送拓扑包。
 * 以1s为周期维护老化计数，当计数为0时，重置该拓扑结果
 */
__task void taskTopoAging() {
    uint8 counter = 0;
    uint8 data[4] = {0};
    while( 1 ) {
        os_dly_wait(100);
        counter++;
        if( (counter % 10) == 0 ) {
            //发送拓扑包/10s
            TopoManager::sendTopoPkt();
        }

        //老化拓扑计数
        DCCChannelRcv* nm = DCCChannelRcv::getFirstRcvDcc();
        while( nm ) {
            if( nm->AgingTopo() ) {
                nm->setUpStreamIP(data);
                nm->setUpStreamIpMask(data);
                nm->setUpStreamPortUid(0);
            }
            nm = DCCChannelRcv::getNextRcvDcc(nm->getUID());
       }
     }
}


