/*
 * CExtCard4E1.h
 *
 *  Created on: 2012-12-26
 *      Author: Administrator
 */

#ifndef CEXTCARD4E1_H_
#define CEXTCARD4E1_H_

#include "CBaseCard.h"
//#include <rtl.h>
#include "CMSSave.h"

#include "CExtCard4E1_define.h"

class CUnframeE1;
class CExtCard4E1 : public CBaseCard {
	static const int itsTypeID = TYPE_4E1;
	static const int itsE1Number = 4;
	static const int HardBaseSn = 0;
//	uint8 slotNumber;
	CExtCard4E1();

public:
	CExtCard4E1(uint8 slot, std::string& name);

	virtual ~CExtCard4E1();

	virtual int GetCartTypeID();
	void RestoreDefaultConfig(void);
	virtual int getNextVersionIndex(uint8 sn);
	virtual int getVersion(uint8 id, STVersion&);
private:
	CUnframeE1* e1s[itsE1Number];
	void destroy();
	CMSSave FlashDriver;
	Card_4E1_Config_T configData;
	void defaultE1Config(int sn);
};

#endif /* CEXTCARD4E1_H_ */
