/*
 * SlotLogicLX9.h
 *
 *  Created on: 2013-3-16
 *      Author: Administrator
 */

#ifndef SLOTLOGICLX9_H_
#define SLOTLOGICLX9_H_

#include "CMSSave.h"
//#include <fstream>

class SlotLogic_LX9 {
	EZ_FLASH_DATA_T saveinfo;
	CMSSave savefile;
	uint8 fileName[20];
//	std::ifstream loadfile;
public:
	SlotLogic_LX9(uint8*, uint8);
	SlotLogic_LX9();
	virtual ~SlotLogic_LX9();
	void OpenSlotLogic(void);
	bool UpDataLx9(uint8*, uint8);
	bool UpDataLx9(void);
};

#endif /* SLOTLOGICLX9_H_ */
