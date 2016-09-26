/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CCardOnlineChecker.h
 ** File path:			/EMUX300/Src/Main_Code/3G/SlotCard/CCardOnlineChecker.h
 ** Created by:          Shqp
 ** Created date:        2012-3-30
 ** Version:             V0.1
 ** Descriptions:        负责实现卡在线监测任务，监测到新插卡，需要创建卡对象。监测到拔卡，需要删除卡对象。
 ** 					 创建卡对象后，将卡对象交给槽位持有。
 **						 删除卡对象也需要委托给槽位完成
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#ifndef CCARDONLINECHECKER_H_
#define CCARDONLINECHECKER_H_

enum CheckStatus {
	NoCard = 0,
	Waitinit,
	Working,
	WaitDelete
};
/*
 *
 */

class CBaseSlot;
class CCardOnlineChecker{
//	static int GapSeconds;
	CheckStatus state;
	CCardOnlineChecker();
public:
	CCardOnlineChecker(CBaseSlot*);
	virtual ~CCardOnlineChecker();

	void TaskRun(void);
private:
	CBaseSlot* itsSlot;
};

#endif /* CCARDONLINECHECKER_H_ */
