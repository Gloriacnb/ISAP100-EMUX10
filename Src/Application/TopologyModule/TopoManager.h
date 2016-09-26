/*
 * TopoManager.h
 *
 *  Created on: 2013-7-12
 *      Author: Administrator
 */

#ifndef TOPOMANAGER_H_
#define TOPOMANAGER_H_

#include "EZ_types.h"

class PriPacket;

class TopoPkt {
public:
	TopoPkt();
	~TopoPkt();
	void initial();
	void setSndPort(uint32 sndPort) {
		strPkt[16] = sndPort >> 24;
		strPkt[17] = sndPort >> 16;
		strPkt[18] = sndPort >> 8;
		strPkt[19] = sndPort >> 0;

	};
	void setPriHead(uint32 head) {
		strPkt[0] = head >> 24;
		strPkt[1] = head >> 16;
		strPkt[2] = head >> 8;
		strPkt[3] = head >> 0;
	};
	uint8* getPkt(uint32* len);
private:
	const static uint32 priTag = 0;
	static uint8 strPkt[];

};




class TopoManager {
public:
	TopoManager();
	virtual ~TopoManager();

	static void startTopoSearch();
	static void proccessTopoSearch(PriPacket& pkt);
//	static uint8 Topoing;
	static void sendTopoPkt(void);
private:
	static TopoPkt pkt;
	static bool ifMyPacket(PriPacket& pkt);
};

#endif /* TOPOMANAGER_H_ */
