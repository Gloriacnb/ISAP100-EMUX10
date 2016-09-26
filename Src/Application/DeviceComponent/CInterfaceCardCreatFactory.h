/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CInterfaceCardCreatFactory.h
 ** File path:			/EMUX300/Src/Main_Code/3G/HardWareFactory/CInterfaceCardCreatFactory.h
 ** Created by:          Shqp
 ** Created date:        2012-3-31
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

#ifndef CINTERFACECARDCREATFACTORY_H_
#define CINTERFACECARDCREATFACTORY_H_

#include <string>
/*
 *
 */
class CBaseSlot;
class CBaseCard;
class CInterfaceCardCreatFactory {
public:
	CInterfaceCardCreatFactory();
	virtual ~CInterfaceCardCreatFactory();

	virtual CBaseCard* make(int iTypeID, CBaseSlot*) = 0;
	virtual int destroy(CBaseCard*) = 0;

	virtual CBaseSlot* makeSlot(int sn) = 0;

	virtual void initChips(void) = 0;

};

#endif /* CINTERFACECARDCREATFACTORY_H_ */
