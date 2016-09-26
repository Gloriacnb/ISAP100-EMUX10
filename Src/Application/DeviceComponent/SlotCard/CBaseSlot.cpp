/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CBaseSlot.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/SlotCard/CBaseSlot.cpp
 ** Created by:          Shqp
 ** Created date:        2012-4-11
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

#include "CBaseSlot.h"
#include "CBaseCard.h"
#include "CCardOnlineChecker.h"
#include "CInterfaceCardCreatFactory.h"
#include "Mid_SPI.h"

//#include "Task_define.h"

CBaseSlot::CBaseSlot(int sn, CInterfaceCardCreatFactory* factory) {
	iSn = sn;
	card = NULL;
	iFactory = factory;
	onlinech = new CCardOnlineChecker(this);
//	os_mbx_send(MailPOC, &onlinech, 10);
}

CBaseSlot::~CBaseSlot() {
	delete onlinech;
}

std::string& CBaseSlot::GetName() {
	static std::string s = "";
	if( card == NULL ) {
		return s;
	}
	else {
		return card->GetName();
	}
}



CBaseCard* CBaseSlot::InsertCard(int TypeID) {
	return card = iFactory->make(TypeID,this);
}

void CBaseSlot::RemoveCard(void) {
	iFactory->destroy(card);
	card = 0;
}


int CBaseSlot::GetCardType(void) {
	if( card ) {
		return card->GetCartTypeID();
	}
	return 0;
}

//int CBaseSlot::PlugInCard(CBaseCard* objCard) {
//	if( card != 0 ) {
//		return -1;
//	}
//	card = objCard;
//	return 0;
//}
//int CBaseSlot::PullOutCard(void) {
//	if( card != 0 ) {
//		delete card;
//		card = 0;
//		return 0;
//	}
// 	return -1;
// }
