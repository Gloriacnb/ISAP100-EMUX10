/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ebbnetwork.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** FileName:				CSnmpConstDefine.h
** Created by:				WangChangRong
** Created date:			2011-8-3
** Version:				1.0
** Descriptions:			
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**********************************************************************************************************************/


#ifndef CSNMPCONSTDEFINE_H_
#define CSNMPCONSTDEFINE_H_
class CSnmpConstDefine
{
public:
	/*  帧类型  */
	static const uint8 ucConstGet       = 0xA0;
	static const uint8 ucConstSet       = 0xA3;
	static const uint8 ucConstGetNext   = 0xA1;
	static const uint8 ucConstResponse  = 0xA2;
	static const uint8 ucConstTrap      = 0xA7;

    /*  数据类型  */
    static const uint8 ucConstInteger32 = 0x02;
    static const uint8 ucConstOctetString = 0x04;
    static const uint8 ucConstNull = 0x05;
    static const uint8 ucConstOID = 0x06;
    static const uint8 ucConstIPAddress = 0x40;
    static const uint8 ucConstCounter32 = 0x41;
    static const uint8 ucConstGauge32 = 0x42;
    static const uint8 ucConstTimeTicks = 0x43;
    static const uint8 ucConstOpaque = 0x44;
    static const uint8 ucConstCounter64 = 0x46;
    static const uint8 ucConstNoSuchObject = 0x80;
    static const uint8 ucConstNoSuchInstance = 0x81;
    static const uint8 ucConstEndofMibView = 0x82;

	//版本
	static const uint8 ucConstVersion1 = 0;
	static const uint8 ucConstVersion2c = 1;

	//差错状态
	static const uint8 ucConstSnmpErrorSuccess                 	= 0;
	static const uint8 ucConstSnmpErrorTooBig	                = 1;
    static const uint8 ucConstSnmpErrorNoSuchName            	= 2;//no use
    static const uint8 ucConstSnmpErrorBadValue               	= 3;//no use
    static const uint8 ucConstSnmpErrorReadOnly               	= 4;//no use
    static const uint8 ucConstSnmpErrorGeneralError           	= 5;
    static const uint8 ucConstSnmpErrorNoAccsee               	= 6;
    static const uint8 ucConstSnmpErrorWrongType              	= 7;
    static const uint8 ucConstSnmpErrorWrongLength            	= 8;
    static const uint8 ucConstSnmpErrorWrongEncoding          	= 9;
    static const uint8 ucConstSnmpErrorWrongValue             	=10;
    static const uint8 ucConstSnmpErrorNoCreation            	=11;
    static const uint8 ucConstSnmpErrorInconsistentValue      	=12;
    static const uint8 ucConstSnmpErrorResourceUnavalible    	=13;
    static const uint8 ucConstSnmpErrorCommitFailed           	=14;
    static const uint8 ucConstSnmpErrorUndoFailed             	=15;
    static const uint8 ucConstSnmpErrorAuthorizationError     	=16;
    static const uint8 ucConstSnmpErrorNotWriteable           	=17;
    static const uint8 ucConstSnmpErrorInconsistentName       	=18;

    //SNMP解析常量定义
    static const uint32 uiConstOidMaxSize				= 32;
    static const uint32 uiConstStringMaxSize			= 96;
};

#endif /* CSNMPCONSTDEFINE_H_ */
