/*
 * PriPacket.h
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#ifndef PRIPACKET_H_
#define PRIPACKET_H_

#include "Layer2Tag.h"
#include <string>
#include "SoftSwitch_define.h"
#include "EthMemory.h"
//#include <Net_Config.h>

typedef enum {
	unicast, broadcast, multicast, error_type = -1

} packet_type;

class PriPacket {
	PriPacket();
public:
	const static uint8 multicastAddress[6];
	const static uint8 broadcastAddress[6];
	PriPacket(uint8 swport, LAYER2FRAME* f);
	PriPacket(Layer2Tag&, uint8 swport, LAYER2FRAME* f);
	virtual ~PriPacket();

	int packetType(void);

	Layer2Tag& getPrivateTag(void) {
		return priTag;
	}
	;

	int getPriLen(void) {
		return stdDataLen + 4;
	}
	;

	int getStdLen(void) {
		return stdDataLen;
	}
	;

//	std::string& getStdStream(void) {
//		return streamPacket;
//	};

	uint8* getStdStream(uint16* len) {
		*len = stdDataLen;
		return stdData;
	}
	;

	uint8 getSourcePort(void) {
		return srcPort;
	}
	;

	uint8* getSrcMAC(void) {
		return priTag.srcMAC;
	}
	;
	uint8* getDesMAC(void) {
		return priTag.decMAC;
	}
	;
private:
	uint8 srcPort;
	Layer2Tag priTag;
//	std::string streamPacket; //标准二层数据包流
	uint8* stdData;
	uint16 stdDataLen;
	LAYER2FRAME* frame;
};

#endif /* PRIPACKET_H_ */
