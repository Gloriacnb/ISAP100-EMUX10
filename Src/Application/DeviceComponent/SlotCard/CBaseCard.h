#include "EZ_types.h"
/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CBaseCard.h
 ** File path:			/EMUX300/Src/Main_Code/3G/CBaseCard.h
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

#ifndef CBASECARD_H_
#define CBASECARD_H_

#include "EZlib.h"

// #ifdef DefDebug
// using namespace std;
// #endif
/*
 *
 */

class CBaseCard {
	CBaseCard();
public:
	CBaseCard(std::string& name, uint8 slot) : itsName(name) {
		itsSlotNumber = slot;
	};
	virtual ~CBaseCard();

	std::string& GetName() {
		return itsName;
	};
	virtual int GetCartTypeID() = 0;
//	virtual void destroy() {
//		itsName = "";
//		itsCardDescr = "";
//	};

	std::string& GetCardDescr() {
		return itsCardDescr;
	};
	void SetCardDescr(std::string& s) {
		itsCardDescr = s;
	};
	uint8 getSn(void) {
		return itsSlotNumber;
	};
	virtual int getNextVersionIndex(uint8 sn) = 0;
	virtual int getVersion(uint8 id, STVersion&) = 0;
private:
	uint8 itsSlotNumber;
	std::string itsCardDescr;
	std::string itsName;
};

#endif /* CBASECARD_H_ */
