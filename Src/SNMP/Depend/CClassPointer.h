/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **
 **                                 http://www.ezwell-tech.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** Created by:				Liu Weifeng
 ** Created date:			2011-07-06
 ** Version:				    1.0
 ** Descriptions:			该类的作用就是为了获取CMain等对象指针
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Version:
 ** Descriptions:
 **
 **********************************************************************************************************************/
#ifndef CClassPointer_H
#define CClassPointer_H

//#include "CMain.h"
//#include "CHardWare.h"

//class CMain;
//class CTaskScheduling;
//class CDateTime;
//class CLocalDevice;
//class CHardWare;
class CMibImpl;
//class CCommunication;

class CClassPointer
{
private:
//	static CMain* objpMain; //  CMain对象指针


public:

	CClassPointer();
	~CClassPointer();
//	static void SetMainPointer(CMain* objpInMain); 				//  设置CMain对象指针
//	static CMain* GetMainPointer(void); 					//  获取CMain对象指针
//	static CTaskScheduling* GetTaskSchedulingPointer(void); //  获取CTaskScheduling对象指针
//	static CDateTime* GetDataTimePointer(void); 			//  获取CDataTime对象指针
//	static CHardWare* GetHardWarePointer(void); 			//  获取CHardWare对象指针
//	static CLocalDevice* GetLocalDevicePointer(); 			//  获取CLocalDevicce对象指针
	static CMibImpl* GetMibImplPointer(); 					//  获取CMibImpl对象指针
//	static CCommunication* GetCommunicationPointer();		//	获得Communication对象指针
};

#endif
