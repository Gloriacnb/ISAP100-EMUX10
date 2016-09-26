/*
 * CNME1Port.h
 *
 *  Created on: 2015Äê12ÔÂ24ÈÕ
 *      Author: Administrator
 */

#ifndef CNME1PORT_H_
#define CNME1PORT_H_

#include "RealPortBase.h"
#include "DCNXe1Rcv.h"
#include "DCNXe1Snd.h"
#include "CNME1Port_define.h"
#include <map>

class AlarmElement;
class CMSSave;

class CNME1Port : public RealPortBase {
public:
	CNME1Port(uint32 uid, UFE1_Config_Data_T*, CMSSave*);
	virtual ~CNME1Port();

	virtual int setLoop(const int type);
	virtual std::string& getName(void) {
		return name;
	};
	virtual int getPortSpeed(void) {
		return 2;
	};

	AlarmElement* getAlarmObject(uint32 almType);
	bool setAlarmProperty(uint32 typeID, uint8* newVl);
	int getAlarmName(uint32 almType, char* name);
	void processAlarm(void);
	bool ifE1Alarm(UFE1_alarm_type_E sn);

	static uint32 getFirstAlarmType(void) {
		return FE1_type_base;
	};
	static uint32 getNextAlarmType(uint32 sid) {
		if( sid < FE1_type_base ) {
			return FE1_type_base;
		}
		uint32 nid = sid+1;
		if( sid - FE1_type_base < FE1_type_size ) {
			return nid;
		}
		return 0;
	};

	/*config opration*/
	uint8 getEnable(void);
	bool setEnable(uint8 en, bool save = true);
	uint8 getMode(void);
	bool setMode(uint8 m, bool save = true);
	uint8* getDesc(uint32* len);
	bool setDesc(uint8* desc, uint8 len);

private:
	uint8 e1sn;
	uint8 nmPortSn;
	std::string name;
	DCNXe1Rcv* dcnr;
	DCNXe1Snd* dcns;
	UFE1_Config_Data_T* configData;
	std::map<uint32, AlarmElement*> mapAlarm;
	CMSSave* storer;

private:
    static std::map<uint32, CNME1Port*> group;
public:
    /* group option */
    static CNME1Port* getInstance(uint32 uid) {
        std::map<uint32, CNME1Port*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CNME1Port* getFirstInstance(void) {
        std::map<uint32, CNME1Port*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CNME1Port* getNextInstance(uint32 suid) {
        std::map<uint32, CNME1Port*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* CNME1PORT_H_ */
