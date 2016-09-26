/*
 * CTSChannel.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 *
 *      ����һ��ʱ϶�м������ԣ�
 *      1. �Ƿ�ռ�ã�������ý������Ӻ� ������Ϊ1��δ���佻��ʱ������Ϊ0
 *      2. �Ƿ񼤻���ж˿����ӵ���ʱ϶ʱ��������Ϊ1���޿�ʱ��������Ϊ0
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
