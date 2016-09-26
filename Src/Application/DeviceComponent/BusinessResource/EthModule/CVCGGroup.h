/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **								
 **										ISAP100_Realese
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CVCGGroup.h
 ** File path:			/ISAP100_Realese/Src/Application/DeviceComponent/BusinessResource/EthModule/CVCGGroup.h
 ** Created by:          Shqp
 ** Created date:        2013-3-19
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
 * CVCGGroup.h
 *
 *  Created on: 2013-3-19
 *      Author: Shqp
 */

#ifndef CVCGGROUP_H_
#define CVCGGROUP_H_

#include <map>
#include "EZ_types.h"
#include "CVCG.h"
#include "CMSSave.h"

// typedef struct {
// 	uint8 band;
// 	uint32 vc12[63];
// }vcg_config_T;


typedef struct {
	vcg_config_T vcg[4];
	uint32 crc;
}vcg_all_T;

class CVCGGroup {
	std::map<uint32, CVCG*> mapVCG;
	std::map<uint32, CVCG*>::iterator it;
	CVCGGroup() {};
public:
	CVCGGroup(int n);
	virtual ~CVCGGroup();

	CVCG* GetObjectByUID(uint32 uid);
	void RestoreDefauleConfig(void);

	uint32 getFirstVCGUID(void);
	uint32 getNextVCGUID(uint32 suid);
	void processAlarm(void);
private:
	CMSSave FlashDriver;
	EZ_FLASH_DATA_T storeInfo;
	vcg_all_T storeData;
	void RestoreDataVCG(int n, int vc12begin, int vc12num);

};

#endif /* CVCGGROUP_H_ */
