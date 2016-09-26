/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CBaseSlot.h
 ** File path:			/EMUX300/Src/Main_Code/3G/SlotCard/CBaseSlot.h
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

#ifndef CBASESLOT_H_
#define CBASESLOT_H_

#include "EZlib.h"
#include "EZ_types.h"
//#ifdef DefDebug
//using namespace std;
//#endif

class CBaseCard;
class CCardOnlineChecker;
class CInterfaceCardCreatFactory;

/*
 *
 */
class CBaseSlot {
public:
	CBaseSlot(int sn, CInterfaceCardCreatFactory* factory);
	virtual ~CBaseSlot();

	std::string& GetName();
	virtual int GetCardTypeIDFromHardware() = 0;
	bool cardExist() {
		return (card==NULL) ? false : true;
	};
	int GetSn() {
		return iSn;
	};
	CBaseCard* GetCardObject(void) {
		return card;
	};

	int GetCardType(void);

	CBaseCard* InsertCard(int TypeID);
	void RemoveCard(void);

	int PlugInCard(CBaseCard* objCard);
	CCardOnlineChecker* getChecker(void) {
		return onlinech;
	};
//	int PullOutCard(void);
private:
	int iSn;
	CBaseCard* card;
	CCardOnlineChecker* onlinech;
	CInterfaceCardCreatFactory* iFactory;
};

#endif /* CBASESLOT_H_ */
