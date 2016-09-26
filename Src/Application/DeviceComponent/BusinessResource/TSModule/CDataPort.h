/*
 * CDataPort.h
 *
 *  Created on: 2013-6-14
 *      Author: Administrator
 */

#ifndef CDATAPORT_H_
#define CDATAPORT_H_

#include "CExtCard8Data_define.h"
#include <string>
#include <map>
#include "RealPortBase.h"

class CTSChannel;
class CMSSave;
class CDataPort : public RealPortBase {
	static std::map<uint32, CDataPort*> Group;

public:
	CDataPort(uint32 userIndex, uint8 psn, Data_Port_Config_T* cfg, CMSSave* driver);
	virtual ~CDataPort();

	static uint32 GetFirstDPUid(void) {
		std::map<uint32, CDataPort*>::iterator it = Group.begin();
		if( it != Group.end() ) {
			return it->first;
		}
		return 0;
	};

	static uint32 GetNextDPUid(uint32 suid) {
		std::map<uint32, CDataPort*>::iterator it = Group.find(suid);
		if( it != Group.end() ) {
			++it;
			if( it != Group.end() ) {
				return (*it).first;
			}
		}
		return 0;

	};

	static CDataPort* getDataPort(uint32 uid) {
		std::map<uint32, CDataPort*>::iterator it = Group.find(uid);
		if( it != Group.end() ) {
			return it->second;
		}
		return 0;
	};

	uint8 getEnable(void);
	int setEnable(uint8 en);
	char* getDesc(uint32*);
	int setDesc(const char*, uint32);

	virtual std::string& getName(void) {
		return name;
	};
	uint8 getPortType(void);

	virtual int setLoop(const int type);
	virtual int getPortSpeed(void) {
		return -64;
	};

private:
	uint32 uid;
	uint8 portSn;
	CTSChannel* LinkChannel;
	Data_Port_Config_T* configData;
	std::string name;
	CMSSave* cfgDriver;
//	uint8 portType;
};

#endif /* CDATAPORT_H_ */
