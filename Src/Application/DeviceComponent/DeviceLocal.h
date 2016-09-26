/*
 * DeviceLocal.h
 *
 *  Created on: 2013-2-21
 *      Author: Administrator
 */

#ifndef DEVICELOCAL_H_
#define DEVICELOCAL_H_

//#include "CAttributeFlash.h"
#include "CDeviceAttribute.h"

class CInterfaceCardCreatFactory;
class CSlotManager;
class CSTM;
class CVCGGroup;
class CVC12CrossConnectionMagager;
class CTSCrossConnectionManager;
class SDHGroup;
class CMainBoard;
class EthBoard;

class DeviceLocal {
	DeviceLocal();
	DeviceLocal(const DeviceLocal&);
	DeviceLocal& operator=(DeviceLocal&);
	virtual ~DeviceLocal();

	static DeviceLocal dev;
	CDeviceAttribute* DevAttr;
	CInterfaceCardCreatFactory* factory;
	CSlotManager* slots;
	CVCGGroup* vcgGroup;
	CVC12CrossConnectionMagager* MappingManager;
	CTSCrossConnectionManager* XcManager;
	SDHGroup* sdh;
	CMainBoard* mb;
	EthBoard* eth;
public:
	static DeviceLocal& instance(void) {
		return dev;
	}
	;
	void DeviceRun();
	void DeviceInit(void);
	CDeviceAttribute& GetDeviceAttributeObject(void) {
		return *DevAttr;
	}
	;
	CSlotManager& GetSlotManager(void) {
		return *slots;
	}
	;
	CVCGGroup& GetVcgGroupObject(void) {
		return *vcgGroup;
	}
	CVC12CrossConnectionMagager& GetMappingManager(void) {
		return *MappingManager;
	}
	;
	CTSCrossConnectionManager& GetXcManager(void) {
		return *XcManager;
	}
	;
	SDHGroup& GetSdhObject(void) {
		return *sdh;
	}
	;
	EthBoard* getEthBoard(void) {
		return eth;
	};
	CMainBoard* getMainBoard(void) {
		return mb;
	};
};

#endif /* DEVICELOCAL_H_ */
