/*
 * CExtCard2BD.h
 *
 *  Created on: 2013-7-29
 *      Author: Administrator
 */

#ifndef CEXTCARD2BD_H_
#define CEXTCARD2BD_H_

#include "CBaseCard.h"
#include "CMSSave.h"
#include "CExtCard2BD_define.h"

class CUInterface;
class CExtCard2BD : public CBaseCard {
	const static int PortNumber = 2;
public:
	CExtCard2BD(uint8 slot, std::string& name);
	virtual ~CExtCard2BD();

	virtual int GetCartTypeID() {
		return TYPE_2BD;
	};
	virtual int getNextVersionIndex(uint8 sn);
	virtual int getVersion(uint8 id, STVersion&);

private:
	Card_2BD_Config_T configData;
	CMSSave stroer;
	void RestoreDefaultConfig();
	CUInterface* uif[PortNumber];
};

#endif /* CEXTCARD2BD_H_ */
