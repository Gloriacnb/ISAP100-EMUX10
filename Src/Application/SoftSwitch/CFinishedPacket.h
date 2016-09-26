/*
 * CFinishedPacket.h
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 *      �Ѵ������¼�������ų��ظ���
 */

#ifndef CFINISHEDPACKET_H_
#define CFINISHEDPACKET_H_

#include "EZ_types.h"
#include "SoftSwitch_define.h"
#include <map>
#include "Layer2Tag.h"


class PriPacket;
class CFinishedPacket {
	const static uint8 agingsec = 30;//�ϻ�ʱ�䣬����Ϊ��λ
public:
	CFinishedPacket();
	virtual ~CFinishedPacket();

	bool finished(PriPacket&);//�жϴ������ݰ��Ƿ��Ѵ����
	void finishThePacket(PriPacket&);
	void aging(); //�ϻ��Ѵ������¼
private:

	std::map<Layer2Tag, int> finishedTag;
};

#endif /* CFINISHEDPACKET_H_ */
