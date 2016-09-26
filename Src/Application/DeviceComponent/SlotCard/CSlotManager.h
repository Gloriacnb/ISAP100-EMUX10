/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CSlotManager.h
 ** File path:			/EMUX300/Src/Main_Code/3G/CSlotManager.h
 ** Created by:          Shqp
 ** Created date:        2012-3-27
 ** Version:             V0.1
 ** Descriptions:       槽位管理器，负责根据设备类型构建并持有槽位对象，
 ** 					提供槽位UID到Sn的映射方法
 **						提供槽位对象的访问方法。
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#ifndef CSLOTMANAGER_H_
#define CSLOTMANAGER_H_

#include "EZlib.h"

class CBaseSlot;

typedef std::vector<CBaseSlot*> EZVector;

/*
 *
 */
class CInterfaceCardCreatFactory;
class CBaseCard;

class CSlotManager {
//	static const int SlotUIDBase = 0;
public:
	CSlotManager(int Number, CInterfaceCardCreatFactory* factory);
	virtual ~CSlotManager();
	CBaseSlot* GetSlotBySn(int sn);
	CBaseCard* getFirstCard(void);
	CBaseCard* getNextCard(unsigned char);

private:
	int iSlotNumber;
	CInterfaceCardCreatFactory* iFactory;
	EZVector vecSlotObject;
	
};

#endif /* CSLOTMANAGER_H_ */
