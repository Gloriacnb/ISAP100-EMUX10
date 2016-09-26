/*
 * CVCGMember.h
 *
 *  Created on: 2013-5-14
 *      Author: Administrator
 */

#ifndef CVCGMEMBER_H_
#define CVCGMEMBER_H_

#include <map>
#include "AlarmElement.h"
#include "CVCG_define.h"

class AlarmElement;
class CVC12;
//class Alarm_property_T;
class CVCGMember {
public:
	CVCGMember(CVC12*, uint32, Alarm_property_T*);
	virtual ~CVCGMember();
	CVC12* getVC12(void) {
		return vc12;
	};
	void processAlarm(void);
	bool ifMemberAlarm(Member_alarm_type_E);
	uint32 getSn(void) {
		return itsSN;
	};
	void setSn( uint32 sn ) {
		itsSN = sn;
	};
private:
	CVC12* vc12;
	uint32 itsSN;
	std::map<uint32, AlarmElement*> mapAlarm;
};

#endif /* CVCGMEMBER_H_ */
