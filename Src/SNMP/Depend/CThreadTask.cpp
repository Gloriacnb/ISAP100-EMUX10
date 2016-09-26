/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CThreadTask.cpp
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

#include "CThreadTask.h"
//#include "CTaskScheduling.h"
#include "CErrorValueDefine.h"
#include "CClassPointer.h"
/**********************************************************************************************************************
** Function name:			CThreadTask
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2012-3-8
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask::CThreadTask() {
	objpDownLinkBegin = NULL;			//下联伪线程链表头
	objpDownLinkEnd = NULL;			//下联伪线程链表尾
	objpThreadTaskNext = NULL;				//下一个伪线程，用于构成双向链表
	objpThreadTaskPrev = NULL;				//上一个伪线程，用于构成双向链表
	objpUpLinkThreadTask = NULL;			//上联伪线程对象

//	objpTimeoutTaskItem = NULL;
//	SetTaskType( CTaskScheduling::uiTaskTypePseudoThread );				//任务类型

	uiThreadTaskStatus = uiThreadTaskStatusProcess;
}

/**********************************************************************************************************************
** Function name:			~CThreadTask
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2012-3-8
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask::~CThreadTask() {
}

/**********************************************************************************************************************
** Function name:			SetTimeoutTaskItem
** Descriptions:			设置超时伪线程任务条目类对象指针
** input parameters:		objpItem：	超时伪线程任务条目类对象指针
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-8
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CThreadTask::SetTimeoutTaskItem(CTaskItem* objpItem)
//{
//	objpTimeoutTaskItem = objpItem;
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
/**********************************************************************************************************************
** Function name:			GetTimeoutTaskItem
** Descriptions:			获得超时伪线程任务条目类对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			超时伪线程任务条目类对象指针
** Created by:				WangChangRong
** Created date:			2012-3-12
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//CTaskItem* CThreadTask::GetTimeoutTaskItem( )
//{
//	return objpTimeoutTaskItem;
//}

/**********************************************************************************************************************
** Function name:			SetThreadTaskStatus
** Descriptions:			设置伪线程任务状态
** input parameters:		uiStatus：	伪线程任务状态
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::SetThreadTaskStatus(uint32 uiStatus)
{
	uiThreadTaskStatus = uiStatus;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetThreadTaskStatus
** Descriptions:			获得伪线程任务状态
** input parameters:		None
** output parameters:		None
** Returned value:			伪线程任务状态
** Created by:				WangChangRong
** Created date:			2012-3-12
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::GetThreadTaskStatus()
{
	return uiThreadTaskStatus;
}

/**********************************************************************************************************************
** Function name:			Wait
** Descriptions:			任务挂起，将任务移到等待队列中。根据需要（超时参数）将任务移到超时队列中。
** 							只对伪线程任务有效，对定时任务、高优先级任务和低优先级任务无效
** input parameters:		uiTimeout:		超时时间，单位毫秒，1000表示1秒后进入超时处理
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-8
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CThreadTask::Wait(uint32 uiTimeout)
//{
//	CClassPointer::GetTaskSchedulingPointer()->UnRegisterThreadTask(this);//从伪线程队列中注销
//	if( uiTimeout == 0){//只挂起，不进行超时任务处理
//		//从超时队列中注销
//		CClassPointer::GetTaskSchedulingPointer()->UnRegisterTimeoutThreadTask(this);
//		//注册挂起队列
//		CClassPointer::GetTaskSchedulingPointer()->RegisterThreadWaitTask(this,0);
//	}
//	else{
//		uint32 uiPara = CClassPointer::GetTaskSchedulingPointer()->GetSystemTimeTicks()+uiTimeout;
//		//先注册超时任务队列
//		CClassPointer::GetTaskSchedulingPointer()->RegisterTimeoutThreadTask(this,uiPara);
//		//再注册挂起队列
//		CClassPointer::GetTaskSchedulingPointer()->RegisterThreadWaitTask(this,uiPara);
//	}
//	return CErrorValueDefine::uiConstReturnFailed;
//}
//

/**********************************************************************************************************************
** Function name:			Notify
** Descriptions:			任务唤醒
** 							只对伪线程任务有效，对定时任务、高优先级任务和低优先级任务无效
** input parameters:		uiNotifyType:	唤醒类型
** 							objpSourceTask:	唤醒的源伪线程任务对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-8
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::Notify(uint32 uiNotifyType,CThreadTask* objpSourceTask)
{
	//通知上级任务对象
	CThreadTask* objpUpTask = GetUpLinkThreadTask();
	if( objpUpTask != NULL ){
		objpUpTask->Notify(uiNotifyType,this);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			TimeoutNotify
** Descriptions:			超时唤醒
** 							只对伪线程任务有效，对定时任务、高优先级任务和低优先级任务无效
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-8
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CThreadTask::TimeoutNotify(uint32 uiTimeout)
//{
//	CClassPointer::GetTaskSchedulingPointer()->UnRegisterTimeoutThreadTask(this);
//	return CErrorValueDefine::uiConstReturnFailed;
//}

/**********************************************************************************************************************
** Function name:			IsTopThreadTask
** Descriptions:			是否是最上级伪线程任务对象
** input parameters:		None
** output parameters:		None
** Returned value:			返回是否是最上级伪线程任务标志，	取值true：表示是最上级伪线程任务
** 															取值false：表示不是最上级伪线程任务
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::IsTopThreadTask()
{
	if(objpUpLinkThreadTask == NULL){
		return true;
	}
	else{
		return false;
	}
}
/**********************************************************************************************************************
** Function name:			IsBottomThreadTask
** Descriptions:			是否是最下级伪线程任务对象
** input parameters:		None
** output parameters:		None
** Returned value:			返回是否是最下级伪线程任务标志，	取值true：表示是最下级伪线程任务
** 															取值false：表示不是最下级伪线程任务
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::IsBottomThreadTask()
{
	if(objpDownLinkBegin == NULL){
		return true;
	}
	else{
		return false;
	}
}

/**********************************************************************************************************************
** Function name:			GetFirstDownLink
** Descriptions:			获得下联伪线程任务的第一个
** input parameters:		None
** output parameters:		None
** Returned value:			返回第一个下联伪线程任务的对象指针，如果为NULL，表示没有下联伪线程任务
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask* CThreadTask::GetFirstDownLink()
{
	return objpDownLinkBegin;
}

/**********************************************************************************************************************
** Function name:			GetNextDownLink
** Descriptions:			获得下一个下联伪线程任务，与GetFirstDownLink方法构成迭代检索
** input parameters:		objpDownLink:		下联伪线程任务对象指针，返回的是下一个下联伪线程任务对象指针
** output parameters:		None
** Returned value:			返回下一个下联伪线程任务的对象指针，如果为NULL，表示没有下联伪线程任务或参数传入错误
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask* CThreadTask::GetNextDownLink(CThreadTask* objpDownLink)
{
	if(objpDownLink == NULL){
		return NULL;
	}
	return objpDownLink->objpThreadTaskNext;
}

/**********************************************************************************************************************
** Function name:			GetEndDownLink
** Descriptions:			获得下联伪线程任务的最后一个
** input parameters:		None
** output parameters:		None
** Returned value:			返回最后一个下联伪线程任务的对象指针，如果为NULL，表示没有下联伪线程任务
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask* CThreadTask::GetEndDownLink()
{
	return objpDownLinkEnd;
}

/**********************************************************************************************************************
** Function name:			GetPrevDownLink
** Descriptions:			获得前一个下联伪线程任务，与GetEndDownLink方法构成迭代检索
** input parameters:		objpDownLink:		下联伪线程任务对象指针，返回的是前一个下联伪线程任务对象指针
** output parameters:		None
** Returned value:			返回前一个下联伪线程任务的对象指针，如果为NULL，表示没有前一个下联伪线程任务或参数传入错误
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask* CThreadTask::GetPrevDownLink(CThreadTask* objpDownLink)
{
	if(objpDownLink == NULL){
		return NULL;
	}
	return objpDownLink->objpThreadTaskPrev;
}
/**********************************************************************************************************************
** Function name:			SetUpLinkThreadTask
** Descriptions:			设置上联伪线程任务对象
** input parameters:		objpUpLink：		上联伪线程任务对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::SetUpLinkThreadTask(CThreadTask* objpUpLink)
{
	this->objpUpLinkThreadTask = objpUpLink;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetUpLinkEvent
** Descriptions:			获得上联伪线程任务对象
** input parameters:		None
** output parameters:		None
** Returned value:			上联伪线程任务对象
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask* CThreadTask::GetUpLinkThreadTask()
{
	return objpUpLinkThreadTask;
}

/**********************************************************************************************************************
** Function name:			InsertDownLinkEvent
** Descriptions:			插入下联伪线程任务对象
** input parameters:		objpDownLink：		下联伪线程任务对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							传人参数为空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::InsertDownLinkThreadTask(CThreadTask* objpDownLink)
{
	if( objpDownLink == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}

	if( objpDownLinkBegin == NULL || objpDownLinkEnd == NULL){	//下联事件为空
		objpDownLinkBegin = objpDownLink;
		objpDownLinkEnd = objpDownLink;
		objpDownLink->SetThreadTaskNext(NULL);
		objpDownLink->SetThreadTaskPrev(NULL);
		objpDownLink->SetUpLinkThreadTask(this);
	}
	else{	//下联事件非空，构建链表
		objpDownLinkEnd->SetThreadTaskNext(objpDownLink);
		objpDownLink->SetThreadTaskNext(NULL);
		objpDownLink->SetThreadTaskPrev(objpDownLinkEnd);
		objpDownLinkEnd = objpDownLink;
		objpDownLink->SetUpLinkThreadTask(this);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			RemoveDownLinkThreadTask
** Descriptions:			移除下联伪线程任务对象
** input parameters:		objpDownLink：		移除伪线程任务对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							传人参数为空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::RemoveDownLinkThreadTask(CThreadTask* objpDownLink)
{
	if( objpDownLink == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}

	if( objpDownLinkBegin == objpDownLink && objpDownLinkEnd == objpDownLink){
		objpDownLinkBegin = NULL;
		objpDownLinkEnd = NULL;
		objpDownLink->SetThreadTaskNext(NULL);
		objpDownLink->SetThreadTaskPrev(NULL);
		objpDownLink->SetUpLinkThreadTask(NULL);
	}
	else if( objpDownLinkBegin == objpDownLink ){

		objpDownLinkBegin = objpDownLinkBegin->GetThreadTaskNext();
		objpDownLinkBegin->SetThreadTaskPrev(NULL);
		objpDownLink->SetThreadTaskNext(NULL);
		objpDownLink->SetThreadTaskPrev(NULL);
		objpDownLink->SetUpLinkThreadTask(NULL);
	}
	else if( objpDownLinkEnd == objpDownLink ){

		objpDownLinkEnd = objpDownLinkEnd->GetThreadTaskPrev();
		objpDownLinkEnd->SetThreadTaskNext(NULL);
		objpDownLink->SetThreadTaskNext(NULL);
		objpDownLink->SetThreadTaskPrev(NULL);
		objpDownLink->SetUpLinkThreadTask(NULL);
	}
	else{
		objpDownLink->GetThreadTaskNext()->SetThreadTaskPrev(objpDownLink->GetThreadTaskPrev());
		objpDownLink->GetThreadTaskPrev()->SetThreadTaskNext(objpDownLink->GetThreadTaskNext());
	
		objpDownLink->SetThreadTaskNext(NULL);
		objpDownLink->SetThreadTaskPrev(NULL);
		objpDownLink->SetUpLinkThreadTask(NULL);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			SetThreadTaskNext
** Descriptions:			设置下一个伪线程任务
** input parameters:		objpThreadTask：		伪线程任务对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::SetThreadTaskNext(CThreadTask* objpThreadTask)
{
	objpThreadTaskNext = objpThreadTask;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			SetThreadTaskNext
** Descriptions:			设置上一个伪线程任务
** input parameters:		objpThreadTask：		伪线程任务对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::SetThreadTaskPrev(CThreadTask* objpThreadTask)
{
	objpThreadTaskPrev = objpThreadTask;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetThreadTaskNext
** Descriptions:			获得下一个伪线程任务
** input parameters:		None
** output parameters:		None
** Returned value:			下一个伪线程任务
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask* CThreadTask::GetThreadTaskNext()
{
	return objpThreadTaskNext;
}
/**********************************************************************************************************************
** Function name:			GetThreadTaskPrev
** Descriptions:			获得上一个伪线程任务
** input parameters:		None
** output parameters:		None
** Returned value:			上一个伪线程任务
** Created by:				WangChangRong
** Created date:			2012-3-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CThreadTask* CThreadTask::GetThreadTaskPrev()
{
	return objpThreadTaskPrev;
}

/**********************************************************************************************************************
** Function name:			ThreadTaskDestory
** Descriptions:			伪线程任务销毁虚方法，大多数情况下不需要重载
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::ThreadTaskDestory()
{
	//销毁下联伪线程任务对象
	if( objpDownLinkBegin!=NULL ){
		CThreadTask* obipThreadTask = objpDownLinkBegin;
		CThreadTask* obipTmp = NULL;
		while( obipThreadTask != NULL ){
			obipTmp = obipThreadTask->GetThreadTaskNext();
			obipThreadTask->ThreadTaskDestory();
			obipThreadTask = obipTmp;
		}
	}
	//从任务队列中移除
//	CClassPointer::GetTaskSchedulingPointer()->UnRegisterThreadTask(this);
//	CClassPointer::GetTaskSchedulingPointer()->UnRegisterThreadWaitTask(this);
//	CClassPointer::GetTaskSchedulingPointer()->UnRegisterTimeoutThreadTask(this);
	//销毁自己
	delete this;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			NotifyToUpThread
** Descriptions:			通知上级对象
** input parameters:		uiNotifyType:	通知类型
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-16
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::NotifyToUpThread(uint32 uiNotifyType)
{
	CThreadTask* objpUpTask = GetUpLinkThreadTask();
	if( objpUpTask != NULL ){
		objpUpTask->Notify(uiNotifyType,this);
	}
	return CErrorValueDefine::uiConstReturnSuccess;

}

/**********************************************************************************************************************
** Function name:			ThreadTaskUndo
** Descriptions:			伪线程任务撤销操作Undo虚方法
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-16
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CThreadTask::ThreadTaskUndo()
{
	CThreadTask* objpDown = GetFirstDownLink();
	while(objpDown != NULL){
		objpDown->ThreadTaskUndo();
		objpDown = objpDown->GetNextDownLink(objpDown);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
