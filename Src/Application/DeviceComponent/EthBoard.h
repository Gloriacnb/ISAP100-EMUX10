/*
 * EthBoard.h
 *
 *  Created on: 2014-4-8
 *      Author: Administrator
 */

#ifndef ETHBOARD_H_
#define ETHBOARD_H_

#include "CMSSave.h"
#include "PortEth.h"
#include "SwitchModule.h"

typedef struct {
	Switch_Base_cfg_T sw;
	UETH_Config_Data_T port[12];
	uint32 crc;
}eth_all_T;

class RTL8306ESwitch;
class CSwitchBaseImpl;
class EthBoard {
	EthBoard();
public:
	EthBoard(int portNum, bool ifsw);
	virtual ~EthBoard();

	CSwitchBaseImpl* getSwitch(int sn);
private:
	RTL8306ESwitch* ChipSwitch;
	PortEth* eport[8];
	CMSSave FlashDriver;
	EZ_FLASH_DATA_T storeInfo;
	eth_all_T storeData;
	void RestoreDefauleConfig(void);
};

#endif /* ETHBOARD_H_ */
