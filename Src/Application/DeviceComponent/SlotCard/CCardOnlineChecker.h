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
 ** Descriptions:        ����ʵ�ֿ����߼�����񣬼�⵽�²忨����Ҫ���������󡣼�⵽�ο�����Ҫɾ��������
 ** 					 ����������󣬽������󽻸���λ���С�
 **						 ɾ��������Ҳ��Ҫί�и���λ���
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
