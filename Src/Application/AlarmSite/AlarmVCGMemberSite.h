/*
 * AlarmVCGMemberSite.h
 *
 *  Created on: 2013-5-14
 *      Author: Administrator
 */

#ifndef ALARMVCGMEMBERSITE_H_
#define ALARMVCGMEMBERSITE_H_

#include "AlarmElement.h"
#include "CVCG_define.h"



class CVCGMember;
class AlarmVCGMemberSite : public AlarmElement {
public:
	AlarmVCGMemberSite(Alarm_property_T*, CVCGMember*, Member_alarm_type_E);
	virtual ~AlarmVCGMemberSite();

private:
	virtual uint32 SourceID(void);
	virtual Alarm_status_E ReadCurrentStatus(void);
	virtual void DisplayExtend(Alarm_event_E);
	CVCGMember* state;	//��ȡ�澯״̬����
	Member_alarm_type_E AlarmSn;	//ö��vcg member�澯���
};

#endif /* ALARMVCGMEMBERSITE_H_ */
