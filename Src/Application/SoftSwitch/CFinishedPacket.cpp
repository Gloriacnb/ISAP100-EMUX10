/*
 * CFinishedPacket.cpp
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#include "CFinishedPacket.h"
#include "PriPacket.h"

#include <rtl.h>

static OS_MUT mut_finishedpkt;

CFinishedPacket::CFinishedPacket() {
	// TODO Auto-generated constructor stub
	os_mut_init(mut_finishedpkt);
}

CFinishedPacket::~CFinishedPacket() {
	// TODO Auto-generated destructor stub
}

/*
 * �ж��Ƿ��Ѿ������� pkt
 * ���� true ��ʾ�ð��Ѿ�������
 * ���� false ��ʾ�ð�δ������
 *
 */
bool CFinishedPacket::finished(PriPacket& pkt) {
	os_mut_wait(mut_finishedpkt, 0xffff);
	std::map<Layer2Tag, int>::iterator it = finishedTag.find(pkt.getPrivateTag());
	os_mut_release(mut_finishedpkt);
	if( it != finishedTag.end() ) {
		return true;
	}
	return false;
}
void CFinishedPacket::finishThePacket(PriPacket& pkt) {
	os_mut_wait(mut_finishedpkt, 0xffff);
	std::map<Layer2Tag, int>::iterator it = finishedTag.find(pkt.getPrivateTag());
	if( it != finishedTag.end() ) {
		it->second = agingsec;
	}
	else {
		finishedTag.insert( std::pair<Layer2Tag, int>(pkt.getPrivateTag(), agingsec) );
	}
	os_mut_release(mut_finishedpkt);
}


void CFinishedPacket::aging() {
	os_mut_wait(mut_finishedpkt, 0xffff);
	std::map<Layer2Tag, int>::iterator it = finishedTag.begin();
	while( it != finishedTag.end() ) {
		if( it->second == 0 ) {
			finishedTag.erase(it++);
		}
		else {
			--(it->second);
			++it;
		}
	}
	os_mut_release(mut_finishedpkt);
}