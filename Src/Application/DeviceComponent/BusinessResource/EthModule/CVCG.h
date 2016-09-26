/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **								
 **										ISAP100_Realese
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CVCG.h
 ** File path:			/ISAP100_Realese/Src/Application/DeviceComponent/BusinessResource/EthModule/CVCG.h
 ** Created by:          Shqp
 ** Created date:        2013-3-19
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/
/*
 * CVCG.h
 *
 *  Created on: 2013-3-19
 *      Author: Shqp
 */

#ifndef CVCG_H_
#define CVCG_H_

#include <string>
#include <string.h>
#include "EZ_types.h"
#include <map>

#include "CVCG_define.h"
#include "CifVCGAlarmStatus.h"

class CVC12;
class CVCGMember;
class CMSSave;
class AlarmElement;
class CVCG : public CifVCGAlarmStatus {
	bool BandMember(uint32 uid, uint32 sn);
	bool delMember(uint32 uid);
	bool realSNCP(uint32 uid, uint32 en);
public:
	CVCG(int sn, uint32 uid, vcg_config_T* data, CMSSave* store);
	virtual ~CVCG();

	bool addMember(uint32 uid);
	bool removeMember(uint32 uid);
	bool clrMember(void);

	std::string& GetName(void) {
		return name;
	};
	uint8* GetDesc(uint32* len) {
		*len = itsConfig->descLen;
		return itsConfig->desc;
	};

	void SetDesc( uint8* desc, uint8 len );

	uint8 getEnable(void) {
		return itsConfig->enable;
	};
	void setEnable(uint8 en);

	uint8 memberNumber(void) {
		return mapMember.size();
	};

	uint32 getFirstMemberUID(void) {
		it = mapMember.begin();
		if( it != mapMember.end() ) {
			return it->first;
		}
		return 0;
	};

	uint32 getNextMemberUID(uint32 suid) {
		it = mapMember.find(suid);
		if( it != mapMember.end() ) {
			++it;
			if( it != mapMember.end() )
				return it->first;
		}
		return 0;
	};

	CVCGMember* getMemberObjectByUID(uint32 muid) {
		it = mapMember.find(muid);
		if( it != mapMember.end() ) {
			return it->second;
		}
		return 0;
	};
	uint8 getLcas(void) {
		return itsConfig->lcas;
	};
	bool setLcas(uint8 lcas);

	uint8 getSNCP(uint32 msn);

	bool setSNCP(uint32 msn, uint8 en);

	void processAlarm(void);
	virtual bool ifVCGAlarm(VCG_alarm_type_E sn);
	virtual uint32 getUID(void) {
		return itsUid;
	};


private:
	std::map<uint32, CVCGMember*> mapMember;
	std::map<uint32, CVCGMember*>::iterator it;
	int itsHardId;
	uint32 itsUid;
	vcg_config_T* itsConfig;
	std::string name;
	CMSSave* storer;
	std::map<uint32, AlarmElement*> mapAlarm;
//	std::string desc;
};

#endif /* CVCG_H_ */
