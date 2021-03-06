/*
 * CVFPortG.h
 *
 *  Created on: 2017年11月17日
 *      Author: Administrator
 */

#ifndef SRC_APPLICATION_DEVICECOMPONENT_BUSINESSRESOURCE_TSMODULE_CVFPORTG_H_
#define SRC_APPLICATION_DEVICECOMPONENT_BUSINESSRESOURCE_TSMODULE_CVFPORTG_H_

#include "CVFPort.h"

class CVFPortG : public CVFPort {
public:
	CVFPortG(uint32 userIndex, uint8 portSn, VF_Port_Config_T*, VF_Group_Config_T*, CMSSave* driver);
	virtual ~CVFPortG();


	virtual uint8 getRcvGain(void);
	virtual uint8 getSndGain(void);
	virtual int setRcvGain(uint8 vl, bool save = true);

	virtual int setSndGain(uint8 vl, bool save = true);

};

#endif /* SRC_APPLICATION_DEVICECOMPONENT_BUSINESSRESOURCE_TSMODULE_CVFPORTG_H_ */
