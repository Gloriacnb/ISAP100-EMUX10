/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CCrossConnection.h
 ** File path:			/EMUX300/Src/Main_Code/3G/CCrossConnection.h
 ** Created by:          Shqp
 ** Created date:        2012-3-29
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

#ifndef CCROSSCONNECTION_H_
#define CCROSSCONNECTION_H_

#include "EZlib.h"
/*
 *
 */
class CCrossConnection {
public:
	CCrossConnection(int sn, int west, int east);
	virtual ~CCrossConnection();

	int GetSn() {
		return itsSn;
	}
	;
	int GetTimeSlotWest();
	int GetTimeSlotEast();
	int GetTimeSlotPartner(int uiNode);
	int GetWestUID() {
		return itsWest;
	}
	;
	int GetEastUID() {
		return itsEast;
	}
	;
	MyString& GetName(void);
	MyString& GetDescription(void);

	void SetName(MyString& newName);
	void SetDescription(MyString& newDesc);

	int GetSNCP() {
		return itsSNCP;
	}
	;

	void setSncp(int s);
private:
	int itsWest;
	int itsEast;
	int itsSn;
	MyString itsName;
	MyString itsDescription;
	int itsSNCP;
};

#endif /* CCROSSCONNECTION_H_ */
