/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibNodeObject.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-5
 ** Version:				1.0
 ** Descriptions:			MIB库节点对象实现类，用于组建MIB库实现
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CMIBNODEOBJECT_H_
#define CMIBNODEOBJECT_H_
#include "CSnmpVariable.h"

class CSnmpCell;
class CMibNodeObject
{
private:
	CMibNodeObject* objpNodeListBegin;							//下联节点链表头
	CMibNodeObject* objpNodeListEnd;							//下联节点链表尾
	uint32 uiListNumber;										//下联节点链表中包含节点的数量
	CMibNodeObject* objpNextNode;								//同级链表中的下一个节点
	CMibNodeObject* objpPrevNode;								//同级链表中的前一个节点
	CSnmpVariable objpNodeVariable;								//节点的OID定义
	uint32 uiNodeValid;											//该节点有效标志
	CMibNodeObject* objpUpLinkNode;								//上一级节点
public:
	CMibNodeObject();
	virtual ~CMibNodeObject();
	//初始化节点
	uint32 InitialNode(CSnmpVariable* objpOID);

	CSnmpVariable& getVariable(void) {
		return objpNodeVariable;
	};
	//插入下联节点
	uint32 InsertDownLinkNode(CMibNodeObject* objpNode);
	//移除下联节点
	uint32 RemoveDownLinkNode(CMibNodeObject* objpNode);
	//获得下联第一个节点
	CMibNodeObject* GetDownLinkBeginNode();
	//获得下一个节点，与GetDownLinkBeginNode构成迭代
	static CMibNodeObject* GetDownLinkNextNode(CMibNodeObject* objpNode);
	//获得下联最后一个节点
	CMibNodeObject* GetDownLinkEndNode();
	//获得前一个节点，与GetDownLinkPrevNode构成迭代
	static CMibNodeObject* GetDownLinkPrevNode(CMibNodeObject* objpNode);
	//获得下联链表节点数量
	uint32 GetDownLinkNodeNumber();
	//获得上一级对象
	CMibNodeObject* GetUpLinkNode();
	//设置上一级对象
	uint32 SetUpLinkNode(CMibNodeObject* objpNode);

	//获得该节点的下一个节点
	CMibNodeObject* GetNextNode();
	//获得该节点的前一个节点
	CMibNodeObject* GetPrevNode();
	//设置该节点的下一个节点
	uint32 SetNextNode(CMibNodeObject* objpNode);
	//设置该节点的前一个节点
	uint32 SetPrevNode(CMibNodeObject* objpNode);
	//获得该节点有效标志
	uint32 GetNodeValid();
	//获得该节点的OID参数
	CSnmpVariable* GetNodeOIDVariable();

	//Get/Set的MIB检索方法
	uint32 GetSetMibSearch(CSnmpCell* objpCell);
	//Get的响应方法
	virtual uint32 GetResponse(CSnmpCell* objpCell) = 0;
	//Set的响应方法
	virtual uint32 SetResponse(CSnmpCell* objpCell) = 0;
	//GetNext的MIB检索方法
	uint32 GetNextMibSearch(CSnmpCell* objpCell);
	//GetNext的响应方法
	uint32 GetNextResponse(CSnmpCell* objpCell);
	//GetNext调用方法1：获得第一个对象的OID
	virtual uint32 GetFirstValidOID(CSnmpCell* objpCell) = 0;
	//GetNext调用方法2：获得下一个对象的OID
	virtual uint32 GetNextValidOID(CSnmpCell* objpCell) = 0;

	//继续进行GetNext操作
	uint32 ContinueGetNextMibSearch(CSnmpCell* objpCell,CMibNodeObject* objpNode);


};

#endif /* CMIBNODEOBJECT_H_ */
