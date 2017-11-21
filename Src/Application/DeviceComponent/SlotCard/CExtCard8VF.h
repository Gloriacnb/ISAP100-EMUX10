/*
 * CExtCard8VF.h
 *
 *  Created on: 2012-12-26
 *      Author: Administrator
 */

#ifndef CEXTCARD8VF_H_
#define CEXTCARD8VF_H_

#include "EZ_types.h"
#include "CBaseCard.h"
#include <string>
#include "CMSSave.h"
#include "CExtCard8VF_define.h"
#include <rtl.h>

class CVFPort;
class CExtCard8VF: public CBaseCard {
//	uint8 slotNumber;
protected:
	static const uint8 portNumber = 8;
public:
	CExtCard8VF();
	virtual ~CExtCard8VF();
	CExtCard8VF(uint8 slot, std::string& name);

	virtual int GetCartTypeID() = 0;
	virtual int getNextVersionIndex(uint8 sn);
	virtual int getVersion(uint8 id, STVersion&);

protected:
	friend __task void T_MT_Wave(void* card );
	Card_8VF_Config_T configData;
	CMSSave stroer;
	CVFPort* vf[portNumber];
	void RestoreDefaultConfig(void);
	OS_TID TaskMtWave;

};

#endif /* CEXTCARD8VF_H_ */
