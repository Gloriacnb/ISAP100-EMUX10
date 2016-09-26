/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CE1BufferDeepthChecker.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/E1Module/CE1BufferDeepthChecker.cpp
 ** Created by:          Shqp
 ** Created date:        2012-7-4
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#include "CE1BufferDeepthChecker.h"
//#include "CE1FPGAAppl.h"
//#include "CTaskScheduling.h"
//#include "CClassPointer.h"

CE1BufferDeepthChecker::CE1BufferDeepthChecker() {
	// TODO Auto-generated constructor stub

}

CE1BufferDeepthChecker::CE1BufferDeepthChecker(int Sn) {
	iSn = Sn;
//	SetTaskType(CTaskScheduling::uiTaskTypeTimeSlice);		//  ×¢²áÈÎÎñ
//    CClassPointer::GetTaskSchedulingPointer()->RegisterTask(this, Task_E1_BuffDeepth_Check1);
//    CClassPointer::GetTaskSchedulingPointer()->RegisterTask(this, Task_E1_BuffDeepth_Check2);
}



CE1BufferDeepthChecker::~CE1BufferDeepthChecker() {
	// TODO Auto-generated destructor stub
}

uint32 CE1BufferDeepthChecker::TaskRun(uint32 ) {
//	CE1FPGAAppl fpga;
//	return fpga.CheckE1BufferDeepth(iSn);
	return 0;
}

