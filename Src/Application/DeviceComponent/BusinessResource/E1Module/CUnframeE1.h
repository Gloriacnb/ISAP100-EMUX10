/*
 * CUnframeE1.h
 *
 *  Created on: 2013-2-23
 *      Author: Administrator
 */

#ifndef CUNFRAMEE1_H_
#define CUNFRAMEE1_H_

#include <string>
#include <map>
#include "CUnframeE1_define.h"

#include "RealPortBase.h"


class CMSSave;
class CE1Channel;
class AlarmElement;

class CUnframeE1 : public RealPortBase {
	static std::map<uint32, CUnframeE1*> UE1_group;
	static std::map<uint32, CUnframeE1*>::iterator it;
	CUnframeE1();
public:
//	CUnframeE1(int gid, int sn);
	CUnframeE1(int gid, int sn, uint32 uid, UE1_Config_Data_T*, CMSSave*);
	virtual ~CUnframeE1();

	virtual int setLoop(const int type);

	virtual std::string& getName(void) {
		return name;
	};

	virtual int getPortSpeed(void) {
		return 2;
	};

	int getPortSn(void) {
		return logicID % 4 + 1;
	};

	int getPortSlot(void) {
		return logicID / 4 + 1;
	};

	uint8 getEnable(void) {
		return configData->enable;
	};

	char* getDescription(uint32* len) {
		*len = configData->dlen;
		return configData->desc;
	};

	int setEnable(uint8 en);
	int setDescription(char*, uint8 len);


	static CUnframeE1* getE1(uint32 n) {
		it = UE1_group.find(n);
		if( it != UE1_group.end() ) {
			return (*it).second;
		}
		return 0;
	};


	static uint32 getFirstAlarmType(void) {
		return E1_type_base;
	};
	static uint32 getNextAlarmType(uint32 sid) {
		if( sid < E1_type_base ) {
			return E1_type_base;
		}
		uint32 nid = sid+1;
		if( sid - E1_type_base < E1_type_size ) {
			return nid;
		}
		return 0;
	};
	static uint32 GetFirstE1Uid(void) {
		if( UE1_group.empty() ) {
			return 0;
		}
		return UE1_group.begin()->first;
	};
	static uint32 GetNextUid(uint32 suid) {
		it = UE1_group.find(suid);
		if( it != UE1_group.end() ) {
			++it;
			if( it != UE1_group.end() ) {
				return (*it).first;
			}
		}
		return 0;

	};

	AlarmElement* getAlarmObject(uint32 almType);
	bool setAlarmProperty(uint32 typeID, uint8* newVl);
	int getAlarmName(uint32 almType, char* name);
	void processAlarm(void);


	bool ifE1Alarm(UE1_alarm_type_E sn);
//	uint32 getUID(void) {
//		return uid;
//	};
private:
//	uint32 uid;
	int logicID;
	UE1_Config_Data_T* configData;
	CMSSave* storer;
	std::string name;
	std::map<uint32, AlarmElement*> mapAlarm;
	CE1Channel* linkChannel;
};

#endif /* CUNFRAMEE1_H_ */
