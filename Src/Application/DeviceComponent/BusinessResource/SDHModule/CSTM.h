/*
 * CSTM.h
 *
 *  Created on: 2013-2-26
 *      Author: Administrator
 */

#ifndef CSTM_H_
#define CSTM_H_

#include <map>
#include <string>
#include "EZ_types.h"
#include "CifSTMAlarmStatus.h"
#include "CSTM_define.h"
#include "RealPortBase.h"
#include "DCCSdhRcv.h"
#include "DCCSdhSnd.h"

extern const int VC12Number;

class CMSSave;
class CVC12;
class AlarmElement;
class CSTM : public CifSTMAlarmStatus,  public RealPortBase {
//	static const int VC12Number = 63;
	CSTM();
public:
	CSTM(uint32 uid, STM_config_data*, CMSSave*);
	virtual ~CSTM();

	static CVC12* GetVc12Object(uint32 uid);
	static uint32 GetFirstVC12Uid(void) {
		return mapVc12.begin()->first;
	};
	static uint32 GetNextVC12Uid(uint32 suid) {
		it = mapVc12.find(suid);
		if( it != mapVc12.end() ) {
			++it;
			if( it != mapVc12.end() ) {
				return it->first;
			}
		}
		return 0;
	};

	/* RealPortBase member function */
	virtual int setLoop(const int type);

	/*
	 * status
	 */
	virtual bool ifMSAlarm(MS_alarm_type_E sn);
	virtual bool ifAU4Alarm(AU_alarm_type_E sn);
	virtual bool ifVC4Alarm(VC_alarm_type_E sn);

	/*
	 * Alarm property
	 */
	bool setAlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl);
	bool setAlarmProperty(uint32 typeID, uint8* newVl);
	bool setVC12AlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl);

	uint32 getFirstAlarmType(void);
	uint32 getNextAlarmType(uint32 sid);

	AlarmElement* getAlarmObject(uint32 almType);
	int getAlarmName(uint32 almType, char* name);

	/*
	 * config function
	 */
	virtual std::string& getName(void) {
		return name;
	};
	uint8 getEnable(void) {
		return configData->enable;
	};
	uint8* getDescription(uint32* len) {
		*len = configData->descLen;
		return configData->desc;
	};

	uint8 getAlsEnable( void ) {
		return configData->als;
	};
	uint8* getJ0Transmit(uint32* len) {
		*len = configData->JTLen;
		return configData->J0Transmit;
	}
	uint8* getJ0Expected(uint32* len) {
		*len = configData->JELen;
		return configData->J0Expected;
	}
	uint8* getJ0Received(uint32* len);
	void setJ0Transmit(uint8* j0, uint8 len, bool save = true);
	void setJ0Expected(uint8* j0, uint8 len);
	void setDescription( uint8* desc, uint8 len);
	void setEnable(uint8 nvalue, bool save = true);
	void setAls(uint8);


	virtual uint32 getUID(void) {
		return RealPortBase::getUID();
	};

	virtual int getPortSpeed(void) {
		return 155;
	};

	void processAlarm(void);

private:
	static std::map<uint32,CVC12*> mapVc12;
	static std::map<uint32, CVC12*>::iterator it;
	int hardid;
//	uint32 uid;
	CMSSave* Store;
	STM_config_data* configData;
	std::map<uint32, AlarmElement*> mapAlarm;
	std::string name;

	DCCSdhRcv* dccr;
	DCCSdhSnd* dccs;

	int getSTMAlarmName(uint32 almType, char* name);
	int getVC4AlarmName(uint32 almType, char* name);
	int getAU4AlarmName(uint32 almType, char* name);

};

#endif /* CSTM_H_ */
