/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CThreadTask.h
 ** Created by:				WangChangRong
 ** Created date:			2012-3-8
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CTHREADTASK_H_
#define CTHREADTASK_H_
//#include "COneTask.h"
#include "EZ_types.h"

//CThreadTask
class CThreadTask {//: public COneTask{
private:
//	CTaskItem* objpTimeoutTaskItem;		//该任务所属的超时伪线程任务条目类对象指针，由任务管理赋值，使用时可以不关心初始化

	CThreadTask* objpDownLinkBegin;			//下联伪线程链表头
	CThreadTask* objpDownLinkEnd;			//下联伪线程链表尾
	CThreadTask* objpThreadTaskNext;				//下一个伪线程，用于构成双向链表
	CThreadTask* objpThreadTaskPrev;				//上一个伪线程，用于构成双向链表
	CThreadTask* objpUpLinkThreadTask;			//上联伪线程对象

	uint32 uiThreadTaskStatus;				//伪线程任务状态

public:
	CThreadTask();
	virtual ~CThreadTask();
	const static uint32 uiThreadTaskStatusProcess = 0;				//伪线程任务处理中，默认状态
	const static uint32 uiThreadTaskStatusSuccess = 1;				//伪线程处理完成，成功
	const static uint32 uiThreadTaskStatusFailed = 2;				//伪线程处理完成，失败
	const static uint32 uiThreadTaskStatusTimeout = 3;				//伪线程处理完成，超时

	//设置超时伪线程任务条目类对象指针
//	uint32 SetTimeoutTaskItem(CTaskItem* objpItem);
	//获得超时伪线程任务条目类对象指针
//	CTaskItem* GetTimeoutTaskItem( );

	//设置伪线程任务状态
	uint32 SetThreadTaskStatus(uint32 uiStatus);
	//获得伪线程任务状态
	uint32 GetThreadTaskStatus();

	//是否是最上级伪线程任务对象
	uint32 IsTopThreadTask();
	//是否是最下级伪线程任务对象
	uint32 IsBottomThreadTask();
	//获得下联伪线程任务的第一个
	CThreadTask* GetFirstDownLink();
	//获得下一个下联伪线程任务，与GetFirstDownLink方法构成迭代检索
	static CThreadTask* GetNextDownLink(CThreadTask* objpDownLink);
	//获得下联伪线程任务的最后一个
	CThreadTask* GetEndDownLink();
	//获得前一个下联伪线程任务，与GetEndDownLink方法构成迭代检索
	static CThreadTask* GetPrevDownLink(CThreadTask* objpDownLink);
	//设置上联伪线程任务对象虚方法
	virtual uint32 SetUpLinkThreadTask(CThreadTask* objpUpLink);
	//获得上联伪线程任务对象
	CThreadTask* GetUpLinkThreadTask();
	//插入下联伪线程任务对象虚方法
	virtual uint32 InsertDownLinkThreadTask(CThreadTask* objpDownLink);
	//移除下联伪线程任务对象虚方法
	virtual uint32 RemoveDownLinkThreadTask(CThreadTask* objpDownLink);
	//设置下一个伪线程任务
	uint32 SetThreadTaskNext(CThreadTask* objpTask);
	//设置上一个伪线程任务
	uint32 SetThreadTaskPrev(CThreadTask* objpTask);
	//获得下一个伪线程任务
	CThreadTask* GetThreadTaskNext();
	//获得上一个伪线程任务
	CThreadTask* GetThreadTaskPrev();

	//通知上级对象
	uint32 NotifyToUpThread(uint32 uiNotifyType);

	//任务挂起，将任务移到等待队列中。根据需要（超时参数）将任务移到超时队列中。只能在该类中调用
//	virtual uint32 Wait(uint32 uiTimeout);
	//任务唤醒,在其他类中调用
	virtual uint32 Notify(uint32 uiNotifyType,CThreadTask* objpSourceTask);
	//超时唤醒，只能由伪线程超时队列调用
//	virtual uint32 TimeoutNotify(uint32 uiTimeout);
	//伪线程任务销毁虚方法
	virtual uint32 ThreadTaskDestory();

	//伪线程任务撤销操作Undo虚方法
	virtual uint32 ThreadTaskUndo();
};

#endif /* CTHREADTASK_H_ */
