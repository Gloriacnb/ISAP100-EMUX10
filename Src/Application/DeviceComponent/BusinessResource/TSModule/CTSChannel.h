/*
 * CTSChannel.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 *
 *      对于一个时隙有几种属性：
 *      1. 是否占用，当分配好交叉连接后 该属性为1，未分配交叉时该属性为0
 *      2. 是否激活，当有端口连接到此时隙时，该属性为1，无卡时，该属性为0
 */

#ifndef CTSCHANNEL_H_
#define CTSCHANNEL_H_

#include <map>
#include <string>
#include "EZ_types.h"

class CTSChannel {
	static std::map<uint32, CTSChannel*> Group;
	CTSChannel();
public:
	CTSChannel(uint32 uid);
	virtual ~CTSChannel();

	/*
	 * group function
	 */
	static uint32 getFirstUid(void) {
		std::map<uint32, CTSChannel*>::iterator it = Group.begin();
		if( it != Group.end() ) {
			return (*it).first;
		}
		return 0;
	};
	static uint32 getNextUid(uint32 suid) {
		std::map<uint32, CTSChannel*>::iterator it = Group.find(suid);
		if( it != Group.end() ) {
			it++;
			if( it != Group.end() ) {
				return it->first;
			}
		}
		return 0;
	};
	static CTSChannel* getTSChannelByUid(uint32 uid) {
		std::map<uint32, CTSChannel*>::iterator it = Group.find(uid);
		if( it != Group.end() ) {
			return it->second;
		}
		return 0;
	};

	/*
	 * element function
	 */

	bool ifOcuppy(void) {
		return mapingPartner != 0;
	};

	bool ifActive(void) {
		return active != 0;
	};

	void setActive(uint8 act) {
		active = act;
	};

	uint32 getMapPartner(void) {
		return mapingPartner;
	};

	void setMapPartner(uint32 uid) {
		mapingPartner = uid;
	}

private:
	uint32 iUID;
//	uint32 Hid;
	uint32 mapingPartner;
	uint8 active;
	std::string name;
};

#endif /* CTSCHANNEL_H_ */
