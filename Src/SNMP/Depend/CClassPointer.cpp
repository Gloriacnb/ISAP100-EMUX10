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
#include "CClassPointer.h"
#include "EZ_types.h"
//#include "CMain.h"
//#include "CLocalDevice.h"
//CMain* CClassPointer::objpMain = NULL;
//#include "CMibImpl.h"
#include "CSnmpMib.h"
extern CSnmpMib snmp;

/**********************************************************************************************************************
** Function name:			CClassPointer
** Descriptions:			构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None                               
** Created by:				Liu Weifeng                                            
** Created Date:			2011-07-06 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
CClassPointer::CClassPointer()
{
	return;
}


/**********************************************************************************************************************
** Function name:			~CClassPointer
** Descriptions:			析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None                               
** Created by:				Liu Weifeng                                            
** Created Date:			2011-07-06 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
CClassPointer::~CClassPointer()
{
	return;
}

/**********************************************************************************************************************
** Function name:			SetMainPointer
** Descriptions:			设置CMain对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			None                             
** Created by:				Liu Weifeng                                            
** Created Date:			2011-07-06 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
// void CClassPointer::SetMainPointer(CMain* objpInMain)
// {
// 	if( objpInMain == NULL){
// 		return;
// 	}
//     objpMain = objpInMain;
// }



/**********************************************************************************************************************
** Function name:			GetMainPointer
** Descriptions:			获取CMain对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			Cmain对象指针                              
** Created by:				Liu Weifeng                                            
** Created Date:			2011-07-06 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
// CMain* CClassPointer::GetMainPointer(void)
// {
//     return objpMain;
// }

/**********************************************************************************************************************
** Function name:			GetTaskSchedulingPointer
** Descriptions:			获取CTaskScheduling对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			CTaskScheduling对象指针                              
** Created by:				Liu Weifeng                                            
** Created Date:			2011-07-06 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
// CTaskScheduling* CClassPointer::GetTaskSchedulingPointer(void)
// {
//     return objpMain->GetSystemObject()->GetTaskScheduling();
// }

/**********************************************************************************************************************
** Function name:			GetDataTimePointer
** Descriptions:			获取CDateTime对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			CDateTime对象指针
** Created by:				Liu Weifeng                                            
** Created Date:			2011-07-06 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
// CDateTime* CClassPointer::GetDataTimePointer(void)
// {
//     return objpMain->GetSystemObject()->GetDateTime();
// }
/*********************************************************************************************************************
** Function name:			GetLocalDevicePointer
** Descriptions:			  获取CLocalDevicce对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			CLocalDevicce对象指针
** Created by:				WangChangRong
** Created Date:			2011-07-26
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************************/
//CLocalDevice* CClassPointer::GetLocalDevicePointer()
//{
//	return objpMain->GetDeviceObject()->GetLocalDevice();
//}




/*********************************************************************************************************************
** Function name:			GetHardWarePointer
** Descriptions:			获取CHardWare对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			CHardWare对象指针
** Created by:				WangChangRong
** Created Date:			2011-07-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************************/
// CHardWare* CClassPointer::GetHardWarePointer(void)
// {
//     return objpMain->GetHardWareObject();
// }
/**********************************************************************************************************************
** Function name:			GetMibImplPointer
** Descriptions:			获取CMibImpl对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			CMibImpl对象指针
** Created by:				WangChangRong
** Created Date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************************/
CMibImpl* CClassPointer::GetMibImplPointer()
{
	return snmp.GetMibImpl();
}

/*********************************************************************************************************************
** Function name:			GetCommunicationPointer
** Descriptions:			获取CCommunication对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			CCommunication对象指针
** Created by:				WangChangRong
** Created Date:			2011-08-09
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************************/
// CCommunication* CClassPointer::GetCommunicationPointer()
// {
// 	return objpMain->GetCommunicationObject();
// }


