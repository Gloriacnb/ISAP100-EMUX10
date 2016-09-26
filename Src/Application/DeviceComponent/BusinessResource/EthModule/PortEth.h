/*
 * PortEth.h
 *
 *  Created on: 2014-4-4
 *      Author: Administrator
 */

#ifndef PORTETH_H_
#define PORTETH_H_

#include "RealPortBase.h"
#include <stdio.h>

typedef struct {
//    Alarm_property_T alarm_property[E1_type_size];
    uint8 enable;
    uint8 autoAN;
    uint8 speed;
    uint8 duplex;
    uint8 pause;

    uint8 desc[32];
    uint8 dlen;
    uint8 linkType;
    uint16 pvid;
    uint8 evidNumber;
    uint16 evid[15];

}UETH_Config_Data_T;

class CMSSave;
class EthBoard;

class PortEth :  public RealPortBase{
public:
	PortEth(uint32 uid, uint8 chipID, uint8 portsn, UETH_Config_Data_T* cfg, CMSSave* save, EthBoard* b);
	virtual ~PortEth();

	virtual int setLoop(const int type) {
		return -1;
	};
	virtual std::string& getName(void);
	virtual int getPortSpeed(void) {
		return 100;
	};

	uint8 getEnable(void) {
		return ConfigData->enable;
	};
	uint8 getSpeed(void) {
		return ConfigData->speed;
	};
	uint8 getDuplex(void) {
		return ConfigData->duplex;
	};
	uint8 getPause(void) {
		return ConfigData->pause;
	};
	uint8 getAuto(void) {
		return ConfigData->autoAN;
	};
	uint8* getDescription(uint32* len) {
		*len = ConfigData->dlen;
		return ConfigData->desc;
	};
	uint8 getLinktype(void) {
		return ConfigData->linkType;
	};
	uint16 getPVID(void) {
		return ConfigData->pvid;
	};
	uint8* getEVIDList(uint32* len) {
		*len = ConfigData->evidNumber * 2;
		static char buff[100] = {0};
		int pos = 0;
		for (int i = 0; i < ConfigData->evidNumber; ++i) {
			pos += sprintf(buff+pos, "%d,", ConfigData->evid[i]);
		}
		*len = pos;
		return (uint8*)buff;
	};

	bool setEnable(uint8 en, bool save = true);
	bool setSpeed(uint8 en, bool save = true);
	bool setDuplex(uint8 en, bool save = true);
	bool setPause(uint8 en, bool save = true);
	bool setAuto(uint8 en, bool save = true);
	bool setDescription(uint8* desc, uint32 len, bool save = true);
	bool setLinktype(uint8 type, bool save = true);
	bool setPVID(uint16 vid, bool save = true);
	bool addEVID(uint16 vid, bool save = true);
	bool removeEVID(uint16 vid, bool save = true);


	uint32 getTxCounter();
	uint32 getRxCounter();
	uint32 getRxDropCounter();
	uint32 getRxCRCerrCounter();

private:
	std::string name;
	UETH_Config_Data_T* ConfigData;
	uint8 chipID;
	uint8 portID;
	EthBoard* board;
	CMSSave* storer;
private:
    static std::map<uint32, PortEth*> group;
public:
    /* group option */
    static PortEth* getInstance(uint32 uid) {
        std::map<uint32, PortEth*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortEth* getFirstInstance(void) {
        std::map<uint32, PortEth*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortEth* getNextInstance(uint32 suid) {
        std::map<uint32, PortEth*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PORTETH_H_ */
