/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **								
 **										ISAP100_Realese
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CMainBoard.h
 ** File path:			/ISAP100_Realese/Src/Application/DeviceComponent/CMainBoard.h
 ** Created by:          Shqp
 ** Created date:        2013-3-4
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/
/*
 * CMainBoard.h
 *
 *  Created on: 2013-3-4
 *      Author: Shqp
 */

#ifndef CMAINBOARD_H_
#define CMAINBOARD_H_

#include "EZ_types.h"
#include "CNME1Port_define.h"
#include "CMSSave.h"
#include "CUpE1Port_define.h"

typedef struct {
	UFE1_Config_Data_T fe1[2];
	UPE1_Config_Data_T upe1[2];
	uint32 crc;
}MB_Config_T;

class CNME1Port;
class CUpE1Port;

class CMainBoard {
public:
	CMainBoard(uint32 slot, int subType);
	virtual ~CMainBoard();

	void processAlarm(void);
	CNME1Port* getNmPort(uint8 sn) {
		if( sn > 1 ) {
			return 0;
		}
		return nmport[sn];
	};
private:
	CNME1Port* nmport[2];
	CUpE1Port* upe1[2];
	CMSSave FlashDriver;
	MB_Config_T configData;
	void defaultFE1Config(void);
};

#endif /* CMAINBOARD_H_ */
