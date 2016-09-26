/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CSlotManager.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/CSlotManager.cpp
 ** Created by:          Shqp
 ** Created date:        2012-3-27
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

#include "CSlotManager.h"
#include "CInterfaceCardCreatFactory.h"
#include "CBaseSlot.h"

CSlotManager::CSlotManager( int Number, CInterfaceCardCreatFactory* factory ) {
	iSlotNumber = Number;
	iFactory = factory;
	for( int i = 0; i < iSlotNumber; i++ ) {
		vecSlotObject.push_back(iFactory->makeSlot(i));
	}
}

CSlotManager::~CSlotManager() {
	for( int i = 0; i < iSlotNumber; i++ ) {
		if( vecSlotObject[i] )
			delete vecSlotObject[i];
	}
}

CBaseSlot* CSlotManager::GetSlotBySn(int sn) {
	if( sn < 0 || sn > iSlotNumber ) {
		return (CBaseSlot*)0;
	}
	return vecSlotObject[sn];
}

CBaseCard* CSlotManager::getFirstCard(void) {
	for( int i = 0; i < iSlotNumber; i++ ) {
		if( vecSlotObject[i]->cardExist() ) {
			return vecSlotObject[i]->GetCardObject();
		}
	}
	return 0;
}

/*
 * note: cardID(1~iSlotNumber)
 */
CBaseCard* CSlotManager::getNextCard(uint8 slotID) {
	if(slotID >= iSlotNumber) {
		return 0;
	}
	for( int i = slotID+1; i < iSlotNumber; i++ ) {
		if( vecSlotObject[i]->cardExist() ) {
			return vecSlotObject[i]->GetCardObject();
		}
	}
	return 0;

}
