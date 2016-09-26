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
 ** Descriptions:       ��λ����������������豸���͹��������в�λ����
 ** 					�ṩ��λUID��Sn��ӳ�䷽��
 **						�ṩ��λ����ķ��ʷ�����
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
