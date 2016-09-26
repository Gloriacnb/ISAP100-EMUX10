/****************************************Copyright (c)****************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ezwell-tech.com  
**
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			CErrorValueDefine.h
** File path:			/PjIsap600Mc/Main_Code/Define/CErrorValueDefine.h
** Created by:          Shqp
** Created date:        2011-6-2
** Version:             V0.1
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         xss
** Modified date:       2011-11-29
** Version:				
** Descriptions:        用户错误常量定义
**
** Rechecked by:        
*********************************************************************************************************/


#ifndef CERRORVALUEDEFINE_H_
#define CERRORVALUEDEFINE_H_

#include "EZ_types.h"


class CErrorValueDefine {
public:
	/*		Base error	Base  =   0x00000000  */
	static const uint32 uiConstReturnSuccess 						= 0x5A;	//函数执行成功
	static const uint32 uiConstReturnSUCCESS                		= 0x5A; //函数执行成功
	static const uint32 uiConstReturnFailed 						= 0xEE;	//函数执行成功
	static const uint32 uiConstReturnFAILED 						= 0xEE;	//函数执行成功
	static const uint32 uiConstReturnNotSupported 					= 0x01; //不支持的函数实现
	static const uint32 uiConstReturnInputDataInvalid 				= 0x10; //输入参数数据错误
	static const uint32 uiConstReturnInputNULLPointer 				= 0x11; //输入参数空指针错误
	static const uint32 uiConstReturnSystemDataInvalid 				= 0x12; //系统参数数据错误
	static const uint32 uiConstReturnInputDataNotSupported 			= 0x13; //输入参数数据值不支持
	static const uint32 uiConstReturnBufferLackSpace 				= 0x14; //输入的Buffer空间不足
	static const uint32 uiConstReturnNoSuchObject					= 0x15; //没有符合的对象
	static const uint32 uiConstReturnDeviceBusy						= 0x17;	//设备忙
	static const uint32 uiConstReturnNoDataPkg              		= 0x18; //  没有数据包
	static const uint32 uiConstReturnDeviceReady            		= 0x19; //  设备已准备好

	static const uint32 uiConstReturnListModeUnSet					= 0x20;	//链表不能设置，通常表示链表已被使用
	static const uint32 uiConstReturnInsertNodeSortError			= 0x21;	//链表插入节点位置排序错误
	
	static const uint32 uiConstReturnUserInValidUserIDError			= 0x22;	//用户ID错误
	static const uint32 uiConstReturnUserExceedMaxUserLogError	    = 0x23;	// 最大用户信息条目数超限
	static const uint32 uiConstReturnUserLoginNameError             = 0x24;   //用户名错误
	static const uint32 uiConstReturnUserLoginPassWordError         = 0x25;   //密码错误
	static const uint32 uiConstReturnUserLoginStartTimeError        = 0x26;	//开始时间错误
	static const uint32 uiConstReturnUserLoginValidTimeError        = 0x27;   //有效时间错误
	
	static const uint32 uiConstReturnResourceBusy					= 0xc0; //资源状态忙无法操作
	static const uint32 uiConstReturnDestNoExit						= 0xc1;	//目标对象不存在
	static const uint32 uiConstReturnProcessing						= 0xc2;	//正在处理中
	
	
};



#endif /* CERRORVALUEDEFINE_H_ */
