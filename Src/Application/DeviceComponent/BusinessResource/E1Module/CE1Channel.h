/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **								
 **										ISAP100_Realese
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CE1Channel.h
 ** File path:			/ISAP100_Realese/Src/Application/DeviceComponent/BusinessResource/E1Module/CE1Channel.h
 ** Created by:          Shqp
 ** Created date:        2013-3-4
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
 * CE1Channel.h
 *
 *  Created on: 2013-3-4
 *      Author: Shqp
 */

#ifndef CE1CHANNEL_H_
#define CE1CHANNEL_H_

#include <map>
#include "EZ_types.h"
#include <string>

class CE1Channel {
	static std::map<uint32, CE1Channel*> E1_Channel_group;
	static std::map<uint32, CE1Channel*>::iterator it;
	CE1Channel();
public:
	CE1Channel(uint8 slot, uint8 hid, uint8 sn);
	virtual ~CE1Channel();
	static CE1Channel* getE1(uint32 n) {
		it = E1_Channel_group.find(n);
		if( it != E1_Channel_group.end() ) {
			return it->second;
		}
		return 0;
	};

	uint32 uid(void) {
		return iUID;
	};

	uint32 sn(void) {
		return iSn;
	};

	uint32 hid(void) {
		return Hid;
	};

	bool ifOccupied(void) {
		return mapingPartner != 0;
	}

	void occupyIt(uint32 sid) {
		mapingPartner = sid;
	}

	uint32 GetMapPartner(void) {
		return mapingPartner;
	};

	static uint32 GetFirstE1Uid(void) {
		it = E1_Channel_group.begin();
		if( it != E1_Channel_group.end() ) {
			return it->first;
		}
		return 0;
	};

	static uint32 GetNextE1Uid(uint32 suid) {
		it = E1_Channel_group.find(suid);
		if( it != E1_Channel_group.end() ) {
			it++;
			if( it != E1_Channel_group.end() ) {
				return it->first;
			}
		}
		return 0;
	};

	std::string& getName(void) {
		return name;
	}
	bool getActive(void) {
		return active;
	};
	void setActive(bool act) {
		active = act;
	};

private:
	int iSn;
	uint32 iUID;
	uint32 Hid;
	uint32 mapingPartner;
	bool active;
	std::string name;
};

#endif /* CE1CHANNEL_H_ */
