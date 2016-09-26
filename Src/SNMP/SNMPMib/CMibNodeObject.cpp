/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibNodeObject.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-8-5
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CMibNodeObject.h"
#include "CErrorValueDefine.h"
#include "CSnmpCell.h"
#include "CSnmpCommand.h"
/**********************************************************************************************************************
** Function name:			CMibNodeObject
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibNodeObject::CMibNodeObject()
{
	objpNodeListBegin = 0 ;							//下联节点链表头
	objpNodeListEnd = 0 ;							//下联节点链表尾
	uiListNumber = 0;										//下联节点链表中包含节点的数量
	objpNextNode = 0 ;								//同级链表中的下一个节点
	objpPrevNode = 0 ;								//同级链表中的前一个节点
	uiNodeValid = false;												//该节点有效标志
	objpUpLinkNode = 0;
}
/**********************************************************************************************************************
** Function name:			~CMibNodeObject
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibNodeObject::~CMibNodeObject()
{
	if( objpNodeListBegin != 0 ){
		CMibNodeObject* objpNode = objpNodeListBegin;
		CMibNodeObject* objpTemp = 0;
		while(objpNode != 0){
			objpTemp = objpNode;
			objpNode = objpNode->objpNextNode;
			delete objpTemp;
		}
	}
}


/**********************************************************************************************************************
** Function name:			InitialNode
** Descriptions:			初始化节点
** input parameters:		objpOID：			节点初始化对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::InitialNode(CSnmpVariable* objpOID)
{
	if( objpOID == 0 ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}

	if( objpOID->GetSyntax() != CSnmpConstDefine::ucConstOID  ){
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	if( objpNodeVariable.Clone(objpOID) == CErrorValueDefine::uiConstReturnSuccess ){
		uiNodeValid = true;
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;

}

/**********************************************************************************************************************
** Function name:			InsertDownLinkNode
** Descriptions:			插入下联节点
** input parameters:		objpNode：			下联节点对象指针，以OID大小排序
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::InsertDownLinkNode(CMibNodeObject* objpNode)
{
	if( objpNode == 0 ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	if( objpNode->GetNodeValid() == false ){
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	if( objpNodeListBegin == 0 ){//下联为空
		objpNodeListBegin = objpNode;
		objpNodeListEnd = objpNode;
		objpNodeListBegin->SetNextNode(0);
		objpNodeListBegin->SetPrevNode(0);
		objpNode->SetUpLinkNode(this);
		uiListNumber = 1;
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	else{
		CSnmpVariable* objpInOID = objpNode->GetNodeOIDVariable();
		CSnmpVariable* objpTempOID = objpNodeListEnd->GetNodeOIDVariable();
		if( objpInOID->CompareTo( objpTempOID) > 0 ){//比链表最后一个大，插入链表尾
			objpNodeListEnd->SetNextNode( objpNode );
			objpNode->SetPrevNode( objpNodeListEnd );
			objpNode->SetNextNode(0);
			objpNode->SetUpLinkNode(this);
			objpNodeListEnd = objpNode;
			uiListNumber++;
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		else{
			CMibNodeObject* objpTempNode = objpNodeListBegin;
			while( objpTempNode != 0){
				objpTempOID = objpTempNode->GetNodeOIDVariable();
				if( objpInOID->CompareTo( objpTempOID ) < 0 ){//比链表当前节点小，插入该节点之前
					if( objpTempNode == objpNodeListBegin ){//需要插入链表头之前
						objpNode->SetNextNode(objpNodeListBegin);
						objpNode->SetPrevNode(0);
						objpNodeListBegin->SetPrevNode(objpNode);
						objpNodeListBegin = objpNode;
						objpNode->SetUpLinkNode(this);
						uiListNumber++;
						return CErrorValueDefine::uiConstReturnSuccess;
					}
					else{
						objpNode->SetNextNode( objpTempNode );
						objpNode->SetPrevNode( objpTempNode->GetPrevNode() );
						objpTempNode->GetPrevNode()->SetNextNode(objpNode);
						objpTempNode->SetPrevNode( objpNode );
						objpNode->SetUpLinkNode(this);
						uiListNumber++;
						return CErrorValueDefine::uiConstReturnSuccess;
					}
				}
				objpTempNode = objpTempNode->GetNextNode();
			}
		}
	}
	return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
** Function name:			RemoveDownLinkNode
** Descriptions:			移除下联节点
** input parameters:		objpNode：			移除的下联节点对象指针
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::RemoveDownLinkNode(CMibNodeObject* objpNode)
{
	if( objpNode == 0 ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	if( objpNode == objpNodeListBegin && objpNode == objpNodeListEnd){
		objpNodeListBegin = 0;
		objpNodeListEnd = 0;
		uiListNumber = 0;
		delete objpNode;
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	else if( objpNode == objpNodeListBegin ){
		objpNodeListBegin = objpNodeListBegin->GetNextNode();
		objpNodeListBegin->SetPrevNode(0);
		uiListNumber--;
		delete objpNode;
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	else if( objpNode == objpNodeListEnd ){
		objpNodeListEnd = objpNodeListEnd->GetPrevNode();
		objpNodeListEnd->SetNextNode(0);
		uiListNumber--;
		delete objpNode;
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	else{
		CMibNodeObject* objpTempNode = objpNodeListBegin;
		while( objpTempNode != 0){
			if( objpTempNode == objpNode ){
				objpNode->GetPrevNode()->SetNextNode( objpNode->GetNextNode());
				objpNode->GetNextNode()->SetPrevNode( objpNode->GetPrevNode());
				uiListNumber--;
				delete objpNode;
				return CErrorValueDefine::uiConstReturnSuccess;
			}
			objpTempNode = objpTempNode->GetNextNode();
		}
	}
	return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
** Function name:			GetDownLinkBeginNode
** Descriptions:			获得下联第一个节点
** input parameters:		None
** output parameters:		None
** Returned value:			下联第一个节点
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibNodeObject* CMibNodeObject::GetDownLinkBeginNode()
{
	return objpNodeListBegin;
}

/**********************************************************************************************************************
** Function name:			GetDownLinkNextNode
** Descriptions:			获得下一个节点，与GetDownLinkBeginNode构成迭代
** input parameters:		objpNode:		传入的节点对象，返回的是该节点的下一个节点
** output parameters:		None
** Returned value:			下一个节点
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibNodeObject* CMibNodeObject::GetDownLinkNextNode(CMibNodeObject* objpNode)
{
	if( objpNode == 0 ){
		return 0;
	}
	return objpNode->GetNextNode();
}

/**********************************************************************************************************************
** Function name:			GetDownLinkEndNode
** Descriptions:			获得下联最后一个节点
** input parameters:		None
** output parameters:		None
** Returned value:			下联最后一个节点
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibNodeObject* CMibNodeObject::GetDownLinkEndNode()
{
	return objpNodeListEnd;
}

/**********************************************************************************************************************
** Function name:			GetDownLinkPrevNode
** Descriptions:			获得前一个节点，与GetDownLinkPrevNode构成迭代
** input parameters:		objpNode:		传入的节点对象，返回的是该节点的前一个节点
** output parameters:		None
** Returned value:			前一个节点
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibNodeObject* CMibNodeObject::GetDownLinkPrevNode(CMibNodeObject* objpNode)
{
	if( objpNode == 0 ){
		return 0;
	}
	return objpNode->GetPrevNode();
}

/**********************************************************************************************************************
** Function name:			GetDownLinkPrevNode
** Descriptions:			获得下联链表节点数量
** input parameters:		None
** output parameters:		None
** Returned value:			下联链表节点数量
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::GetDownLinkNodeNumber()
{
	return uiListNumber;
}


/**********************************************************************************************************************
** Function name:			GetNextNode
** Descriptions:			获得该节点的下一个节点
** input parameters:		None
** output parameters:		None
** Returned value:			该节点的下一个节点
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibNodeObject* CMibNodeObject::GetNextNode()
{
	return objpNextNode;
}

/**********************************************************************************************************************
** Function name:			GetPrevNode
** Descriptions:			获得该节点的前一个节点
** input parameters:		None
** output parameters:		None
** Returned value:			该节点的前一个节点
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibNodeObject* CMibNodeObject::GetPrevNode()
{
	return objpPrevNode;
}

/**********************************************************************************************************************
** Function name:			SetNextNode
** Descriptions:			设置该节点的下一个节点
** input parameters:		objpNode:	下一个节点的对象指针
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::SetNextNode(CMibNodeObject* objpNode)
{
	objpNextNode = objpNode;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			SetNextNode
** Descriptions:			设置该节点的前一个节点
** input parameters:		objpNode:	前一个节点的对象指针
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::SetPrevNode(CMibNodeObject* objpNode)
{
	objpPrevNode = objpNode;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetNodeValid
** Descriptions:			获得该节点有效标志
** input parameters:		None
** output parameters:		None
** Returned value:			该节点有效标志
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::GetNodeValid()
{
	return uiNodeValid;
}

/**********************************************************************************************************************
** Function name:			GetNodeOIDVariable
** Descriptions:			获得该节点的OID参数对象
** input parameters:		None
** output parameters:		None
** Returned value:			该节点的OID参数对象
** Created by:				WangChangRong
** Created date:			2011-08-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CSnmpVariable* CMibNodeObject::GetNodeOIDVariable()
{
	return &objpNodeVariable;
}



/**********************************************************************************************************************
** Function name:			GetUpLinkNode
** Descriptions:			获得上一级对象
** input parameters:		None
** output parameters:		None
** Returned value:			上一级对象
** Created by:				WangChangRong
** Created date:			2011-09-23
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibNodeObject* CMibNodeObject::GetUpLinkNode()
{
	return objpUpLinkNode;
}

/**********************************************************************************************************************
** Function name:			SetUpLinkNode
** Descriptions:			设置上一级对象
** input parameters:		objpNode:	上一级对象
** output parameters:		None
* Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-09-23
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::SetUpLinkNode(CMibNodeObject* objpNode)
{
	objpUpLinkNode = objpNode;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetSetMibSearch
** Descriptions:			Get/Set的MIB检索方法
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::GetSetMibSearch(CSnmpCell* objpCell)
{
	if( objpCell == 0 ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	CSnmpVariable* objpVariable = objpCell->GetCurrentVariable();
	if( objpNodeListBegin == 0 ){//没有下联节点
		if( objpVariable->StartWith(&objpNodeVariable) ){//以该节点开始
			CSnmpCommand* objpCommand = objpCell->GetSnmpCommand();
			if( objpCommand->GetCurrentRequestType() == CSnmpConstDefine::ucConstGet ){//get
				return GetResponse(objpCell);
			}
			else if( objpCommand->GetCurrentRequestType() == CSnmpConstDefine::ucConstSet ){//set
				return SetResponse(objpCell);
			}
		}
		else{
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	else{//有下联节点
		if( objpVariable->StartWith(&objpNodeVariable) ){//以该节点开始
			CMibNodeObject* objpTemp = objpNodeListBegin;
			uint32 uiRet = CErrorValueDefine::uiConstReturnFailed;
			while( objpTemp != 0 ){//遍历
				uiRet = objpTemp->GetSetMibSearch(objpCell);
				if( uiRet == CErrorValueDefine::uiConstReturnSuccess
				 || uiRet == CErrorValueDefine::uiConstReturnProcessing){
					return uiRet;
				}
				objpTemp = objpTemp->GetNextNode();
			}
		}
		else{
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
** Function name:			GetResponse
** Descriptions:			Get的响应方法
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CMibNodeObject::GetResponse(CSnmpCell* objpCell)
//{
//	return CErrorValueDefine::uiConstReturnFailed;
//}


/**********************************************************************************************************************
** Function name:			SetResponse
** Descriptions:			Set的响应方法
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CMibNodeObject::SetResponse(CSnmpCell* objpCell)
//{
//	return CErrorValueDefine::uiConstReturnFailed;
//}

/**********************************************************************************************************************
** Function name:			GetNextMibSearch
** Descriptions:			GetNext的MIB检索方法
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::GetNextMibSearch(CSnmpCell* objpCell)
{
	if( objpCell == 0 ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	CSnmpVariable* objpVariable = objpCell->GetCurrentVariable();
	if( objpNodeListBegin == 0 ){//没有下联节点
		if( (objpVariable->CompareTo( &objpNodeVariable ) <= 0) //查询对象小于等于节点OID
		 || (objpVariable->StartWith(&objpNodeVariable)) ){//以该节点开始
			return GetNextResponse(objpCell);
		}
		else{
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	else{//有下联节点
		if( (objpVariable->CompareTo( &objpNodeVariable ) <= 0) //查询对象小于等于节点OID
		 || (objpVariable->StartWith(&objpNodeVariable)) ){//以该节点开始
			CMibNodeObject* objpTemp = objpNodeListBegin;
			uint32 uiRet = CErrorValueDefine::uiConstReturnFailed;
			while( objpTemp != 0 ){//遍历
				uiRet = objpTemp->GetNextMibSearch(objpCell);
				if( uiRet == CErrorValueDefine::uiConstReturnSuccess
				 || uiRet == CErrorValueDefine::uiConstReturnProcessing){
					return uiRet;
				}
				objpTemp = objpTemp->GetNextNode();
			}
		}
		else{
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	return CErrorValueDefine::uiConstReturnFailed;
}
/**********************************************************************************************************************
** Function name:			GetNextResponse
** Descriptions:			GetNext的响应方法
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-10
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::GetNextResponse(CSnmpCell* objpCell)
{
	if( objpCell == 0 ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpVariable = objpCell->GetCurrentVariable();
	if( objpVariable->CompareTo( &objpNodeVariable ) <= 0 ){//查询对象小于等于节点OID
		uint32 uiRet = GetFirstValidOID( objpCell );
		if( uiRet == CErrorValueDefine::uiConstReturnSuccess){//获得第一个有效的OID
			return GetResponse(objpCell);
		}
		else if( uiRet == CErrorValueDefine::uiConstReturnProcessing){
			return uiRet;
		}
	}
	else if( objpVariable->StartWith(&objpNodeVariable) ){//以该节点开始
		uint32 uiRet = GetNextValidOID( objpCell );
		if( uiRet == CErrorValueDefine::uiConstReturnSuccess){//获得下一个有效的OID
			return GetResponse(objpCell);
		}
		else if( uiRet == CErrorValueDefine::uiConstReturnProcessing){
			return uiRet;
		}
	}
	return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
** Function name:			GetFirstValidOID
** Descriptions:			GetNext调用方法1：获得第一个对象的OID
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-10
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CMibNodeObject::GetFirstValidOID(CSnmpCell* objpCell)
//{
//	return CErrorValueDefine::uiConstReturnFailed;
//}
/**********************************************************************************************************************
** Function name:			GetNextValidOID
** Descriptions:			GetNext调用方法2：获得下一个对象的OID
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-10
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CMibNodeObject::GetNextValidOID(CSnmpCell* objpCell)
//{
//	return CErrorValueDefine::uiConstReturnFailed;
//}

/**********************************************************************************************************************
** Function name:			ContinueGetNextMibSearch
** Descriptions:			继续进行GetNext操作
** input parameters:		objpCell：		SNMP命令对象
** 							objpNode:		当前已经处理过的节点对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-09-21
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibNodeObject::ContinueGetNextMibSearch(CSnmpCell* objpCell,CMibNodeObject* objpNode)
{
	if( objpCell == 0 ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CMibNodeObject* objpUp = GetUpLinkNode();
	if( objpNodeListBegin == 0 ){//没有下联节点
		if( objpUp == 0 ){//没有上联节点
			CSnmpVariable objEndMib;
			objEndMib.SetSyntax(CSnmpConstDefine::ucConstEndofMibView);
			objpCell->SetResponse(objpCell->GetRequestVB()->GetOIDObject(),&objEndMib);
			return CErrorValueDefine::uiConstReturnFailed;
		}
		return objpUp->ContinueGetNextMibSearch(objpCell,this);
	}
	else{
		CMibNodeObject* objpTemp = objpNodeListBegin;
		uint32 uiFlag = false;
		while( objpTemp != 0 ){//遍历
			//如果下联节点没有搜索，进行搜索
			if( uiFlag == true ){
				uint32 uiRet = objpTemp->GetNextMibSearch(objpCell);
				if( uiRet == CErrorValueDefine::uiConstReturnSuccess
					 || uiRet == CErrorValueDefine::uiConstReturnProcessing){
					//搜索完成或正在进行中，返回
					return uiRet;
				}

			}
			if(objpNode == objpTemp){
				uiFlag = true;
			}
			objpTemp = objpTemp->GetNextNode();
		}
		//该节点下联节点已经搜索完成，返回上一级继续搜索
		if( objpUp == 0 ){//没有上联节点
			CSnmpVariable objEndMib;
			objEndMib.SetSyntax(CSnmpConstDefine::ucConstEndofMibView);
			objpCell->SetResponse(objpCell->GetRequestVB()->GetOIDObject(),&objEndMib);
			return CErrorValueDefine::uiConstReturnFailed;
		}
		return objpUp->ContinueGetNextMibSearch(objpCell,this);

	}

}
