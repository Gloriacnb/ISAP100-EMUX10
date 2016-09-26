/*
 * CExtCard8Data.h
 *
 *  Created on: 2013-5-24
 *      Author: Administrator
 */

#ifndef CEXTCARD8DATA_H_
#define CEXTCARD8DATA_H_

#include "CBaseCard.h"
#include <string>
#include "CExtCard8Data_define.h"
#include "CMSSave.h"

class CDataPort;
class CExtCard8Data : public CBaseCard {
	static const int itsTypeID = TYPE_8Data;
	static const uint8 portNumber = 8;
	CExtCard8Data();
public:
	CExtCard8Data(uint8 slot, std::string& name);
	virtual ~CExtCard8Data();

	virtual int GetCartTypeID();
	virtual int getNextVersionIndex(uint8 sn);
	virtual int getVersion(uint8 id, STVersion&);
private:
	CMSSave FlashDriver;
	Card_8Data_Config_T configData;
	void RestoreDefaultConfig(void);
	CDataPort* dp[portNumber];
};

#endif /* CEXTCARD8DATA_H_ */
