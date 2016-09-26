/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CCrossConnection.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/CCrossConnection.cpp
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

#include "CCrossConnection.h"
#include <string.h>

CCrossConnection::CCrossConnection(int sn, int west, int east) {
	itsSn = sn;
	itsWest = west;
	itsEast = east;
	itsName = "";
	itsDescription = "";
	itsSNCP = 1;
}

CCrossConnection::~CCrossConnection() {
	// TODO Auto-generated destructor stub
}

int CCrossConnection::GetTimeSlotWest() {
	return itsWest;
}
int CCrossConnection::GetTimeSlotEast() {
	return itsEast;

}

int CCrossConnection::GetTimeSlotPartner(int uiNode)
{
	if(uiNode == itsWest){
		return itsEast;
	}
	else if(uiNode == itsEast){
		return itsWest;
	}
	return 0;
}

MyString& CCrossConnection::GetName(void) {
	return itsName;
}
MyString& CCrossConnection::GetDescription(void) {
	return itsDescription;
}

void CCrossConnection::SetName(MyString& newName) {
	itsName.assign(newName);
}
void CCrossConnection::SetDescription(MyString& newDesc) {
	itsDescription.assign(newDesc);
}

void CCrossConnection::setSncp(int s) {
	itsSNCP = s;
}

