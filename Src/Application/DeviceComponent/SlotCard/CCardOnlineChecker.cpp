/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CCardOnlineChecker.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/SlotCard/CCardOnlineChecker.cpp
 ** Created by:          Shqp
 ** Created date:        2012-3-30
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

#include "CCardOnlineChecker.h"
#include "CBaseSlot.h"
//#include "CBaseCard.h"
#include "DeviceLocal.h"

CCardOnlineChecker::CCardOnlineChecker(CBaseSlot* slot) {
	itsSlot = slot;
    state = NoCard;
}

CCardOnlineChecker::~CCardOnlineChecker() {
//	os_tsk_delete(t_oc);

}

void CCardOnlineChecker::TaskRun(void) {
	int cid;
	switch( state ) {
	case NoCard:
		cid = itsSlot->GetCardTypeIDFromHardware();
		if( itsSlot->InsertCard(cid) != 0 ) {
			state = Working;
		}
		break;
	case Working:
		cid = itsSlot->GetCardTypeIDFromHardware();
		if( cid != itsSlot->GetCardType() ) {
			state = WaitDelete;
		}
		break;
	case WaitDelete:
		cid = itsSlot->GetCardTypeIDFromHardware();
		if( cid != itsSlot->GetCardType() ) {
			itsSlot->RemoveCard();
			state = NoCard;
		}
		break;
	default:
		state = NoCard;
		break;
	}
//	if( cmd.ifOver() )
//	CClassPointer::GetHardWarePointer()->GetI2C()->TransmitInterCommand(&cmd);
//	return 0;
}

