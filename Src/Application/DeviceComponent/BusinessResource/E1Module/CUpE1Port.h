/*
 * CUpE1Port.h
 *
 *  Created on: 2014-4-10
 *      Author: Administrator
 */

#ifndef CUPE1PORT_H_
#define CUPE1PORT_H_

#include "RealPortBase.h"
#include "CUpE1Port_define.h"
#include "UpE1DCNChannelSnd.h"
#include "UpE1DCNChannelRcv.h"
#include "UpE1SabitChannelSnd.h"
#include "UpE1SabitChannelRcv.h"

class AlarmElement;
class CMSSave;

class CUpE1Port: public RealPortBase {
	CUpE1Port();
public:
	CUpE1Port(uint32 uid, uint8 hid, UPE1_Config_Data_T* cfg, CMSSave* save);
	virtual ~CUpE1Port();

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
	bool ifE1Alarm(UPE1_alarm_type_E sn);

    /* data IO */
    bool receivData(void);
    void sendData(uint8* d, uint32 len);

    /* config */
    uint8 getEnable(void);
    bool setEnable(uint8 en, bool save = true);
    uint8 getType(void);
    bool setType(uint8 ntype, bool save = true);
    uint32 getTopoDirection(void);
    bool setTopoDirection(uint32 dir, bool save = true);
    std::string getTsInfo(void);
    bool addNMTs(uint32 tsuid, bool save = true);
    bool deleteNMTs(uint32 tsuid, bool save = true);
    uint8* getPortDescription(uint8* len);
    bool setPortDescription(uint8* d, uint8 len, bool save = true);
    uint32 getTsMap(void);
    bool setTsMap(uint32 map, bool save = true);

    uint8* getTopoInfo(void) {
    	if( DcnWorking ) {
    		return dcnrcv->getUpStreamIP();
    	}
        return dccrcv->getUpStreamIP();
    };

    /* for Topo */
    uint32 getUpStreamPortUid(void) {
    	if( DcnWorking ) {
    		return dcnrcv->getUpStreamPortUid();
    	}
        return dccrcv->getUpStreamPortUid();
    };

    uint8* getUpStreamIP(void) {
    	if( DcnWorking ) {
    		return dcnrcv->getUpStreamIP();
    	}
        return dccrcv->getUpStreamIP();
    };

    uint8* getUpStreamIpMask(void) {
    	if( DcnWorking ) {
    		return dcnrcv->getUpStreamIpMask();
    	}
        return dccrcv->getUpStreamIpMask();
    };

private:
	uint8 hid;
	std::string name;
	CMSSave* storer;
	UPE1_Config_Data_T* ConfigData;
	UpE1DCNChannelSnd* dcnsnd;
	UpE1DCNChannelRcv* dcnrcv;
	UpE1SabitChannelSnd* dccsnd;
	UpE1SabitChannelRcv* dccrcv;

	std::map<uint32, AlarmElement*> mapAlarm;
	bool DcnWorking;
    /* for group operation */
    static std::map<uint32, CUpE1Port*> NMPortMap;
public:
    static CUpE1Port* getInstance(uint32 uid) {
        std::map<uint32, CUpE1Port*>::iterator it = NMPortMap.find(uid);
        if( it != NMPortMap.end() ) {
            return it->second;
        }
        return 0;
    };

    static CUpE1Port* getFirstInstance(void) {
        std::map<uint32, CUpE1Port*>::iterator it = NMPortMap.begin();
        if( it != NMPortMap.end() ) {
            return it->second;
        }
        return 0;
    };

    static CUpE1Port* getNextInstance(uint32 suid) {
        std::map<uint32, CUpE1Port*>::iterator it = NMPortMap.find(suid);
        if( it != NMPortMap.end() ) {
            it++;
            if( it != NMPortMap.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* CUPE1PORT_H_ */
