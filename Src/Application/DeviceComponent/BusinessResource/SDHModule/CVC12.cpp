/*
 * CVC12.cpp
 *
 *  Created on: 2013-2-26
 *      Author: Administrator
 */

#include <sstream>
#include "CVC12.h"
#include "AlarmTUSite.h"
#include "AlarmLPSite.h"
#include "rc7880RegDriverfuncLib.h"
#include "UID.h"

CVC12::CVC12(uint32 vc12uid, VC12_config_data* cfgData) {
	uid = vc12uid;
	itsHid = UID::breakUID(uid).vc12.lp;
	iSrcUID = 0;

	std::ostringstream s;
	s << "VC12-" << itsHid + 1;
	name = s.str();

	for (int i = TU12_LOP; i < TU_type_size; i++) {
		cfgData->alarm_Property[i].typeID = TU_type_base + i;
		AlarmElement* ap = new AlarmTUSite(&cfgData->alarm_Property[i], this,
				(TU_Alarm_type_E) i);
		mapAlarm.insert(std::pair<uint32, AlarmElement*>(TU_type_base + i, ap));
	}
	for (int i = VC12_AIS; i < LP_type_size; i++) {
		cfgData->alarm_Property[i + TU_type_size].typeID = LP_type_base + i;
		AlarmElement* ap = new AlarmLPSite(
				&cfgData->alarm_Property[i + TU_type_size], this,
				(LP_Alarm_type_E) i);
		mapAlarm.insert(std::pair<uint32, AlarmElement*>(LP_type_base + i, ap));
	}

	configData = cfgData;
}

CVC12::~CVC12() {
	// TODO Auto-generated destructor stub
}

bool CVC12::ifTUAlarm(TU_Alarm_type_E sn) {
//	RC7880DrvTU12UnitAlarmRead();
	return false;
}
bool CVC12::ifLPAlarm(LP_Alarm_type_E sn) {
	return false;
}

/*
 * 设置VC12告警属性
 * 	typeID  告警类型ID 统一编码
 * 	opt		属性设置选项   1 告警等级； 2 是否trap； 3 是否屏蔽
 * 	newVl	设置的新属性值， 	opt = 1，  等级0 ~ 3
 * 						opt = 2  1表示发送trap 0 不发送
 * 						opt = 3  1表示屏蔽此告警，0 不屏蔽
 */
bool CVC12::setAlarmProperty(uint32 typeID, Alarm_Property_Option opt,
		uint32 newVl) {
	std::map<uint32, AlarmElement*>::iterator it;
	it = mapAlarm.find(typeID);
	bool rtn;
	if (it != mapAlarm.end()) {
		switch (opt) {
		case opt_level:
			rtn = (*it).second->ChangePropertyLevel((Alarm_level_E) newVl);
			break;
		case opt_trap:
			rtn = (*it).second->ChangePropertyTrap(newVl);
			break;
		case opt_mask:
			rtn = (*it).second->ChangePropertyMask(newVl);
			break;
		default:
			return false;
		}
	}
	if (rtn) {
		//send evnt to Task alarm storer;
	}
	return rtn;
}

uint32 CVC12::getPartnerUID(void) {
	UN_Info info = UID::breakUID(uid);
	ST_SDH_VC12 info2;
	info2.slot = info.vc12.slot;
	info2.hp = info.vc12.hp;
	info2.lp = info.vc12.lp;
	if (info.vc12.stm == 0) {
		info2.stm = 1;
	} else {
		info2.stm = 0;
	}
	return UID::makeUID(&info2);
}
