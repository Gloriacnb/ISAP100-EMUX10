/*
 * CVC12.h
 *
 *  Created on: 2013-2-26
 *      Author: Administrator
 */

#ifndef CVC12_H_
#define CVC12_H_

#include <map>
#include <string>
#include "EZ_types.h"
#include "CVC12_define.h"
#include "CifVC12AlarmStatus.h"

class AlarmElement;
class CVC12 : public CifVC12AlarmStatus {
	CVC12();
	int itsHid;
	int iSrcUID;	//0ÎªÎÞÐ§
	std::string name;
public:
	CVC12(uint32 , VC12_config_data*);
	virtual ~CVC12();
	int GetHid(void) {
		return itsHid;
	};

	bool ifOccupied(void) {
		return iSrcUID != 0;
	};

	void occupyIt(uint32 sid) {
		iSrcUID = sid;
	};

	uint32 GetMappingPartner(void) {
		return iSrcUID;
	};

	std::string& getName(void) {
		return name;
	};

	void setName(std::string& newname) {
		name = newname;
	};

	bool setAlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl);

	virtual bool ifTUAlarm(TU_Alarm_type_E sn);
	virtual bool ifLPAlarm(LP_Alarm_type_E sn);
	virtual uint32 getUID(void) {
		return uid;
	};

	uint32 getPartnerUID(void);
private:
	uint32 uid;
	VC12_config_data* configData;
	std::map<uint32, AlarmElement*> mapAlarm;
};

#endif /* CVC12_H_ */
