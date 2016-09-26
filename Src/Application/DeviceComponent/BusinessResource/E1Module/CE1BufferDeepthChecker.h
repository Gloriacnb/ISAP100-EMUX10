/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CE1BufferDeepthChecker.h
 ** File path:			/EMUX300/Src/Main_Code/3G/E1Module/CE1BufferDeepthChecker.h
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

#ifndef CE1BUFFERDEEPTHCHECKER_H_
#define CE1BUFFERDEEPTHCHECKER_H_

//#include "COneTask.h"
#include "EZ_types.h"
/*
 *
 */
class CE1BufferDeepthChecker{ //: public COneTask {
	int iSn;
	CE1BufferDeepthChecker();
public:
	CE1BufferDeepthChecker(int Sn);
	virtual ~CE1BufferDeepthChecker();

	virtual uint32 TaskRun(uint32 );
};

#endif /* CE1BUFFERDEEPTHCHECKER_H_ */
