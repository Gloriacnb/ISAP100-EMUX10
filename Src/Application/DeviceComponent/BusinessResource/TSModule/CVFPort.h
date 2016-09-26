/*
 * CVFPort.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#ifndef CVFPORT_H_
#define CVFPORT_H_

#include "CExtCard8VF_define.h"
#include <map>
#include <string>
#include "RealPortBase.h"
class CTSChannel;
class CMSSave;
class CVFPort : public RealPortBase {
	static std::map<uint32, CVFPort*> Group;
public:
	CVFPort(uint32 userIndex, uint8 portSn, VF_Port_Config_T*, VF_Group_Config_T*, CMSSave* driver);
	virtual ~CVFPort();

	static uint32 GetFirstE1Uid(void) {
		std::map<uint32, CVFPort*>::iterator it = Group.begin();
		if( it != Group.end() ) {
			return it->first;
		}
		return 0;
	};

	static uint32 GetNextE1Uid(uint32 suid) {
		std::map<uint32, CVFPort*>::iterator it = Group.find(suid);
		if( it != Group.end() ) {
			++it;
			if( it != Group.end() ) {
				return (*it).first;
			}
		}
		return 0;

	};

	static CVFPort* getVFPort(uint32 uid) {
		std::map<uint32, CVFPort*>::iterator it = Group.find(uid);
		if( it != Group.end() ) {
			return it->second;
		}
		return 0;
	};

	uint8 getEnable(void);
	int setEnable(uint8 en, bool save = true);

	uint8 getWorkMode(void);
	int setWorkMode(uint8 mode, bool save = true);

	uint8 getPolarTurn(void);
	int setPolarTurn(uint8 en, bool save = true);

	uint8 getRcvGain(void);
	int setRcvGain(uint8 vl, bool save = true);

	uint8 getSndGain(void);
	int setSndGain(uint8 vl, bool save = true);

	char* getDesc(uint32*);
	int setDesc(const char*, uint32);

	virtual std::string& getName(void) {
		return name;
	};

	uint8 getPortType(void);
	uint8 itsType(void) {
		return VFType;
	};
	virtual int setLoop(const int type);
	virtual int getPortSpeed(void) {
		return -64;
	};

	void process2100HZ(void);

private:
	uint32 uid;
	uint8 portSn;
	CTSChannel* LinkChannel;
	VF_Port_Config_T* configData;
	VF_Group_Config_T* groupConfigData;
	std::string name;
	CMSSave* cfgDriver;
	uint8 VFType;
	static void getHinfo(uint32 uid, uint8 portsn, uint8* chipID, uint8* ch);
};

#endif /* CVFPORT_H_ */
