/*********************************************************************************
**								Raycom company
**					ChuanXin Road 27# ,ChangPing Science Tech Park, Beijing
**
**						(c)Copyright 2008,Raycom,Changping,Beijing
** 								All Rights Reserved 
**________________________________________________________________________________
**
** FileName:RC6400.c
** Author: xuezj
** Description:RC6400 DRIVER source file
**
*********************************************************************************/


/*********************************************************************************
**  下面的头文件，用户应该根据自己的程序代码包含相应
**  的头文件，至少得包含stdio.h
**********************************************************************************/
#include "RC6400.h"
#include <string.h>


/*********************************************************************************
** 默认为"激活"和"去激活"'方式, 即#define ACTIVE_FUNCTION_ENABLE
**　如果要选择没有"激活"与"去激活"功能，去掉此宏定义即可
**********************************************************************************/
#define ACTIVE_FUNCTION_ENABLE 


/*********************************************************************************
** 以下４个数组是用于虚级联配置所需要的，如果用户不
**　采用本驱动提供的虚级联配置方式，也可以去掉这４
** 个数组
**********************************************************************************/

uint8 MarkTableNew[CURRENT_CARD_VCG_NUMBER][MAX_CARD_E1_NUMBER];   	/*1 == used*/
uint8 MarkTableOld[CURRENT_CARD_VCG_NUMBER][MAX_CARD_E1_NUMBER];
uint8 LcasFlagNew[CURRENT_CARD_VCG_NUMBER];								/*1 == LCAS*/
uint8 LcasFlagOld[CURRENT_CARD_VCG_NUMBER];


void write(uint16 addr , uint8 data)
{
	uint8 temp ;
	uint8 tempData;

	/* 相同不复写，写完读回校验，最多10次  */
	for(temp = 0 ; temp < 10; temp++) {
		tempData = RC6400_REGS_PTR[addr];
		if(tempData != data)
		{
			/* unprotect regs */
			RC6400_REGS_PTR[sGLOBAL_REGS_PROTECT] = (uint8)RC6400_REGS_FREE_CODE;

			/* write */
			RC6400_REGS_PTR[addr] = data;

			/* protect regs */
			RC6400_REGS_PTR[sGLOBAL_REGS_PROTECT] = (uint8)RC6400_REGS_PROTECT_CODE;
		}
		else {
			break;
		}
	}
	return;
}

uint8 read(uint16 addr)
{
	uint8 data = 0 ;
	data = RC6400_REGS_PTR[addr] ;
	return(data);
}

/**********************************************************************
** 
**   function : RC6400_Var_Init() 
**____________________________________________________________________
**
**  DESCRIPTION: Initialize the varibles or structs defined in this module. Called by 
**                         the Init function in others moduls.
**  Inputs:   none
**  Outputs: none
**  RETURN: none
**
**********************************************************************/
void RC6400_Var_Init(void)
{
	uint8 i;
	
	for(i=0;i<CURRENT_CARD_VCG_NUMBER;i++)
	{
		memset((uint8*)&MarkTableNew[i][0],0,MAX_CARD_E1_NUMBER);
		memset((uint8*)&MarkTableOld[i][0],0,MAX_CARD_E1_NUMBER);
	}
	memset((uint8*)LcasFlagNew,1,CURRENT_CARD_VCG_NUMBER);
	memset((uint8*)LcasFlagOld,1,CURRENT_CARD_VCG_NUMBER);
}

/**********************************************************************
**
**  function: RC6400_Chip_Init()
**_____________________________________________________________________
**
** DESCRIPTION: Initialize the RC6400 Chip
**
** Inputs:  none
** Outputs:none
** RETURN: none
**
***********************************************************************/
void RC6400_Chip_Init(void)
{
#if 0
	uint8 i;
	for(i=0;i<MAX_CARD_E1_NUMBER;i++)
	{
		RC6400_TU12_V5_Config_Rx_Set(i, 0x05);/*0x0A --> 0x05*/
		RC6400_TU12_V5_Config_Tx_Set(i, 0x0A);
		RC6400_TU12_K4_Config_Rx_Set(i, 0x0D);
		RC6400_TU12_K4_Config_Tx_Set(i, 0x0D);
	}
#endif
	RC6400_Alarm_Clear_All_Init();
}
/**********************************************************************
**
** function:RC6400_LCAS_En_Rx_Set()
**_____________________________________________________________________
**
** DESCRIPTION:Enable/Disable LCAS of a VCG in recieve direction. 
** Inputs:
**           VCGNum:The VCG to be set. Should be 0, 1, 2 OR 3
**            flag       :The flag value to be set to the VCG. Should be 0 OR 1
** Outpus:none
** RETURN:none
**
***********************************************************************/
void RC6400_LCAS_En_Rx_Set(uint8 VCGNum,uint8 flag)
{
	uint8 tval;

	tval=read(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9));
	if(flag==LCAS_ENABLE)
	{
		tval|=cRLCAS;
	}
	else if(flag==LCAS_DISABLE)
	{
		tval&=~cRLCAS;
	}
	write(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9), tval);
}
/**********************************************************************
**
** function:RC6400_LCAS_En_Rx_Read()
**_____________________________________________________________________
**
** DESCRIPTION:Enable/Disable LCAS of a VCG in recieve direction. 
** Inputs:
**           VCGNum:The VCG to be set. Should be 0, 1, 2 OR 3
** Outpus:none
** RETURN:TRUE if the LCAS flag of a VCG maked by parameter VCGNum in 
**		is enabled in receive direction,  FALSE in otherwise
**
***********************************************************************/
BOOL RC6400_LCAS_En_Rx_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9));
	if(tval&cRLCAS)
		return TRUE;
	else
		return FALSE;	
}
/**********************************************************************
**
** function:RC6400_LCAS_En_Tx_Set()
**_____________________________________________________________________
**
** DESCRIPTION:Enable/Disable LCAS of a VCG in send direction. 
** Inputs:
**           VCGNum:The VCG to be set. Should be 0, 1, 2 OR 3
**            flag       :The flag value to be set to the VCG. Should be 0 OR 1
** Outpus:none
** RETURN:none
**
***********************************************************************/
void RC6400_LCAS_En_Tx_Set(uint8 VCGNum,uint8 flag)
{
	uint8 tval;
	
	tval=read(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9));
	if(flag==LCAS_ENABLE)
	{
		tval|=cTLCAS;
	}
	else if(flag==LCAS_DISABLE)
	{
		tval&=~cTLCAS;
	}
	write(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9),tval);
}
/**********************************************************************
**
** function:RC6400_LCAS_En_Tx_Read()
**_____________________________________________________________________
**
** DESCRIPTION:Read LCAS flag of a VCG in sned direction. 
** Inputs:
**           VCGNum:The VCG to be set. Should be 0, 1, 2 OR 3
** Outpus:none
** RETURN:TRUE if the LCAS flag of a VCG maked by parameter VCGNum in 
**		is enabled in receive direction,  FALSE in otherwise
**
***********************************************************************/
BOOL RC6400_LCAS_En_Tx_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9));
	if(tval&cTLCAS)
		return TRUE;
	else
		return FALSE;
}
/**************************************************************************
**
** function: RC6400_VCAT_En_Tx_Set()
**_________________________________________________________________________
**
** DESCRIPTION: Enable/Disable the send direction of a VCG.
**
** Inputs:
**          VCGNum: The number of VCG, can be 00,01,10,11 or 0~3
**           flag       : The LCAS flag to be set to the VCG send direction. Can be 1 or 0
**                           LCAS_ENABLE  :1 
**                           LCAS_DISABLE:0
** Outputs: none
** RETURN: none
**
***************************************************************************/
void RC6400_VCAT_En_Tx_Set(uint8 VCGNum, uint8 flag)
{
	uint8 tval;
	
	tval=read(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9));
	if(flag==VCAT_ENABLE)
	{
		tval|=cTVCAT;
	}
	else if(flag==VCAT_DISABLE)
	{
		tval&=~cTVCAT;
	}
	write(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9),tval);
}
/**************************************************************************
**
** function: RC6400_VCAT_En_Tx_Read()
**_________________________________________________________________________
**
** DESCRIPTION: Read the VCAT flag(Enabled/Disabled) in send direction of a VCG.
**
** Inputs:
**          VCGNum: The number of VCG, can be 00,01,10,11 or 0~3
** Outputs: none
** RETURN: TRUE if enabled, else FALSE for disabled.
**
***************************************************************************/
BOOL RC6400_VCAT_En_Tx_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9));
	if(tval&cTVCAT)
		return TRUE;
	else
		return FALSE;
}
/**************************************************************************
**
** function: RC6400_VCAT_En_Rx_Set()
**_________________________________________________________________________
**
** DESCRIPTION: Enable/Disable the recv direction of a VCG.
**
** Inputs:
**          VCGNum: The number of VCG, can be 0~3
**           flag       : The LCAS flag to be set to the VCG recv direction. Can be 1 or 0
**                           LCAS_ENABLE  :1 
**                           LCAS_DISABLE:0
** Outputs: none
** RETURN: none
**
***************************************************************************/
void RC6400_VCAT_En_Rx_Set(uint8 VCGNum,uint8 flag)
{
	uint8 tval;
	
	tval=read(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9));
	if(flag==VCAT_ENABLE)
	{
		tval|=cRVCT;
	}
	else if(flag==VCAT_DISABLE)
	{
		tval&=~cRVCT;
	}
	write(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9),tval);
}
/**************************************************************************
**
** function: RC6400_VCAT_En_Rx_Read()
**_________________________________________________________________________
**
** DESCRIPTION: Read the VCAT flag(Enabled/Disabled) in receive direction of a VCG.
**
** Inputs:
**          VCGNum: The number of VCG, can be 00,01,10,11 or 0~3
** Outputs: none
** RETURN: TRUE if enabled, else FALSE for disabled.
**
***************************************************************************/
BOOL RC6400_VCAT_En_Rx_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9));
	if(tval&cRVCT)
		return TRUE;
	else
		return FALSE;
}
/****************************************************************************
**
** function:RC6400_VC12_GRP_Sel_Rx_Set();
**___________________________________________________________________________
**
** DESCRIPTION:Select a VCG for a VC12 in receive direction.
**
** Inputs:
**          TsNum:   The VC12 to be set. Should be 0~62.
**          VCGNum: The VCG to be selected for the VC12. Should be 0~3.
** Outputs: none
** RETUTN: none
**
*****************************************************************************/
void RC6400_VC12_GRP_Sel_Rx_Set(uint8 TsNum,uint8 VCGNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6));
	if(VCGNum!=(tval&cVC12_RECV_LOVCG))
	{
		tval&=0xF8;
		tval|=VCGNum;
		write(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6),tval);
	}
}
/****************************************************************************
**
** function:RC6400_VC12_GRP_Sel_Rx_Read();
**___________________________________________________________________________
**
** DESCRIPTION:Get the  VCG for a VC12 in receive direction.
**
** Inputs:
**          TsNum:   The VC12 to be set. Should be 0~62.
** Outputs: none
** RETUTN:The VCG of  the VC12. Should be 0~3.
**
*****************************************************************************/
uint8 RC6400_VC12_GRP_Sel_Rx_Read(uint8 TsNum)
{
	uint8 tval;;

	tval=read(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6));
	tval&=cVC12_RECV_LOVCG;
	return tval;
}
/****************************************************************************
**
** function:VC12_GRP_Sel_Tx();
**___________________________________________________________________________
**
** DESCRIPTION:Select a VCG for a VC12 in send direction.
**
** Inputs:
**          TsNum:   The VC12 to be set. Should be 0~62.
**          VCGNum: The VCG to be selected for the VC12. Should be 0~3
** Outputs: none
** RETUTN: none
**
*****************************************************************************/
void RC6400_VC12_GRP_Sel_Tx_Set(uint8 TsNum, uint8 VCGNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6));
	if(VCGNum!=(tval&cVC12_SEND_LOVCG))
	{
		tval&=0xF8;
		tval|=VCGNum;
		write(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6),tval);
	}
}
/****************************************************************************
**
** function:RC6400_VC12_GRP_Sel_Tx_Read();
**___________________________________________________________________________
**
** DESCRIPTION:Get the  VCG for a VC12 in send direction.
**
** Inputs:
**          TsNum:   The VC12 to be set. Should be 0~62.
** Outputs: none
** RETUTN:The VCG of  the VC12. Should be 0~3.
**
*****************************************************************************/
uint8 RC6400_VC12_GRP_Sel_Tx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6));
	tval&=cVC12_SEND_LOVCG;
	return tval;
}
/*****************************************************************************
**
** function: RC6400_VC12_En_Rx_Set();
**____________________________________________________________________________
**
** DESCRIPTION:Enable/Disable a VC12 in VCAT layer in recieve direction.
**
** Inputs:
**          TsNum: The VC12(or called Ts) number to be set.  0~62
**		flag:      1:Enable     0: Disable
** Outputs:none.
** RETURN:
**
******************************************************************************/
void RC6400_VC12_En_Rx_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval= read(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6));
	if(flag==1)
	{
		tval|=cRLOUSE;
	}
	else if(flag==0)
	{
		tval&=~cRLOUSE;
	}
	write(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6),tval);
}
/*****************************************************************************
**
** function: RC6400_VC12_En_Tx_Set();
**____________________________________________________________________________
**
** DESCRIPTION:Read the ENABLED flag of a VC12 in send direction.
**
** Inputs:
**          TsNum: The VC12(or called Ts) number to be set.  0~62
** Outputs:none.
** RETURN:TRUE if enabled, FALSE for disabled.
**
******************************************************************************/
BOOL RC6400_VC12_En_Rx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6));
	if(tval&cRLOUSE)
		return TRUE;
	else
		return FALSE;
}
/*****************************************************************************
**
** function: RC6400_VC12_En_Tx_Set();
**____________________________________________________________________________
**
** DESCRIPTION:Enable/Disable a VC12 in VCAT layer in send direction.
**
** Inputs:
**          TsNum: The VC12(or called Ts) number to be set.  0~62
**		flag:      1:Enable     0: Disable
** Outputs:none.
** RETURN:
**
******************************************************************************/
void RC6400_VC12_En_Tx_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6));
	if(flag==1)
	{
		tval|=cTLOUSE;
	}
	else if(flag==0)
	{
		tval&=~cTLOUSE;
	}
	write(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6), tval);
}
/******************************************************************************
**
** function: RC6400_VC12_En_Tx_Read();
**_____________________________________________________________________________
**
** DESCRIPTION: Read the ENABLED flag of a VC12 in send direction.
** Inputs: 
**          TsNum: The VC12 to be read.
** Outputs:none
** RETURN: TRUE if enabled,FALSE for disabled.
**
******************************************************************************/
BOOL RC6400_VC12_En_Tx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6));
	if(tval&cTLOUSE)
		return TRUE;
	else
		return FALSE;
}
/*******************************************************************************
**
** function:RC6400_VC12_SQ_Rx_Set();
**______________________________________________________________________________
**
** DESCRIPTION:Set SQ value for a VC12 in receive direction.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Shoule be 0~62
**		SQNum: SQ for the VC12.Shoud be 0~62
** Outpus: none.
** RETURN:none.
**
********************************************************************************/
void RC6400_VC12_SQ_Rx_Set(uint8 TsNum, uint8 SQNum)
{
	write(VC12_BASE_ADDR+cVC12_RECV_LOSQ+(TsNum<<6), SQNum);
}
/*******************************************************************************
**
** function:RC6400_VC12_SQ_Rx_Read();
**______________________________________________________________________________
**
** DESCRIPTION:Read SQ value for a VC12 in receive direction.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Shoule be 0~62
** Outpus: none.
** RETURN:SQ for the VC12.Shoud be 0~62
**
********************************************************************************/
uint8 RC6400_VC12_SQ_Rx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_RECV_LOSQ+(TsNum<<6));
	tval&=0x3F;
	return tval;
}
/*******************************************************************************
**
** function:RC6400_VC12_SQ_Tx_Set();
**______________________________________________________________________________
**
** DESCRIPTION:Set SQ value for a VC12 in send direction.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Should be 0~62.
**		SQNum: SQ for the VC12. Should be 0~62.
** Outpus: none.
** RETURN:none.
**
********************************************************************************/
void RC6400_VC12_SQ_Tx_Set(uint8 TsNum, uint8 SQNum)
{
	write(VC12_BASE_ADDR+cVC12_SEND_LOSQ+(TsNum<<6), SQNum);
}
/*******************************************************************************
**
** function:RC6400_VC12_SQ_Tx_Read();
**______________________________________________________________________________
**
** DESCRIPTION:Read SQ value for a VC12 in send direction.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Shoule be 0~62
** Outpus: none.
** RETURN:SQ for the VC12.Shoud be 0~62
**
********************************************************************************/
uint8 RC6400_VC12_SQ_Tx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_SEND_LOSQ+(TsNum<<6));
	tval&=0x3F;
	return tval;
}
/*******************************************************************************
**
** function:RC6400_VC12_K4B2_En_Ts_Set();
**______________________________________________________________________________
**
** DESCRIPTION:Enable/Disable sending of K4B2 for a VC12.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Should be 0~62.
**		flag:     1: Enable.         0: Disable
** Outpus: none.
** RETURN:none.
**
********************************************************************************/
void RC6400_VC12_K4B2_En_Tx_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6));
	if(flag==1)
	{
		tval&=~cTLOK4VCEN;
	}
	else if(flag==0)
	{
		tval|=cTLOK4VCEN;
	}
	write(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6), tval);
}
/*******************************************************************************
**
** function:RC6400_VC12_K4B2_En_Ts_Read();
**______________________________________________________________________________
**
** DESCRIPTION:Read Enable/Disable flag in sending direction of K4B2 for a VC12.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Should be 0~62.
** Outpus: none.
** RETURN:
**		TRUE: Enable.         FALSE: Disable
**
********************************************************************************/
BOOL RC6400_VC12_K4B2_En_Tx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6));
	if(tval&cTLOK4VCEN)
		return FALSE;
	else
		return TRUE;
}
/*******************************************************************************
**
** function:RC6400_VC12_MST_En_Rx_Set()
**______________________________________________________________________________
**
** DESCRIPTION:Enable/Disable the MST for a selected VC12.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Should be 0~62.
**		flag:     1:Enable.       0:Disable.
** Outpus: none.
** RETURN:none.
**
********************************************************************************/
void RC6400_VC12_MST_En_Rx_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6));
	if(flag==1)
	{
		tval&=~cRMSTFAIL;
	}
	else if(flag==0)
	{
		tval|=cRMSTFAIL;
	}
	write(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6), tval);
}
/********************************************************************************
**
** function: RC6400_VC12_MST_En_Rx_Read();
**_______________________________________________________________________________
**
**DESCRIPTION: Read the setting of MST_OK flag of a VC12 in receive direction.
** Inputs: 
**          TsNum: The VC12 to be read.
** Outputs: none.
** RETURN:TRUE for sending MST_OK flag, FALSE for dissending MST_OK flag.
**
*********************************************************************************/
BOOL RC6400_VC12_MST_En_Rx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6));
	if(tval&cRMSTFAIL)
		return FALSE;
	else
		return TRUE;
}
/*******************************************************************************
**
** function:RC6400_TU12_En_Rx_Set()
**______________________________________________________________________________
**
** DESCRIPTION:Enable/Disable a TU12 in receive direction.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Should be 0~62.
**		flag:     1:Enable.       0:Disable.
** Outpus: none.
** RETURN:none.
**
********************************************************************************/
void RC6400_TU12_En_Rx_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	if(flag==1)
	{
		tval|=cTU12_RECV_DROPEN;
	}
	else if(flag==0)
	{
		tval&=~cTU12_RECV_DROPEN;
	}
	write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6),tval);
}
/*******************************************************************************
**
** function:RC6400_TU12_En_Rx_Read()
**______________________________________________________________________________
**
** DESCRIPTION:Read Enable/Disable flag of a TU12 in receive direction.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Should be 0~62
** Outpus: none.
** RETURN:TRUE for enabled, FLASE for disabled.
**
********************************************************************************/
BOOL RC6400_TU12_En_Rx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	if(tval&cTU12_RECV_DROPEN)
		return TRUE;
	else
		return FALSE;
}
/*******************************************************************************
**
** function:RC6400_TU12_En_Tx_Set()
**______________________________________________________________________________
**
** DESCRIPTION:Enable/Disable a TU12 in send direction.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Should be 0~62.
**		flag:     1:Enable.       0:Disable.
** Outpus: none.
** RETURN:none.
**
********************************************************************************/
void RC6400_TU12_En_Tx_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	if(flag==1)
	{
		tval|=cTU12_RECV_ADDEN;
	}
	else if(flag==0)
	{
		tval&=~cTU12_RECV_ADDEN;
	}
	write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6),tval);
}
/*******************************************************************************
**
** function:RC6400_TU12_En_Tx_Read()
**______________________________________________________________________________
**
** DESCRIPTION:Read Enable/Disable flag of a TU12 in send direction.
** 
** Inputs:
**   		TsNum: The VC12 to be set. Should be 0~62
** Outpus: none.
** RETURN:TRUE for enabled, FALSE for disabled.
**
********************************************************************************/
BOOL RC6400_TU12_En_Tx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	if(tval&cTU12_RECV_ADDEN)
		return TRUE;
	else
		return FALSE;
}
/******************************************************************************
**
** function: RC6400_TU12_V5_Config_Rx_Set();
**_____________________________________________________________________________
**
** DESCRIPTION: Set the V5 value for a TU12 in receive direction.
**
** Inputs:
**		TsNum:A TU12 to be set.Should be 0~62.
**		val:     The V5 value. Adviced value:0x0A.
** Outputs:none.
** RETURN:none.
**
*******************************************************************************/
void RC6400_TU12_V5_Config_Rx_Set(uint8 TsNum, uint8 val)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_TSL_EXP+(TsNum<<6));
	if(val!=tval)
		write(TU12_BASE_ADDR+cTU12_RECV_TSL_EXP+(TsNum<<6),val);
}
/******************************************************************************
**
** function: RC6400_TU12_V5_Config_Rx_Read();
**_____________________________________________________________________________
**
** DESCRIPTION: Read the V5 value of a TU12 in receive direction.
**
** Inputs:
**		TsNum:A TU12 to be set.Should be 0~62.
** Outputs:none.
** RETURN:The V5 value. Adviced value:0x0A.
**
*******************************************************************************/
uint8 RC6400_TU12_V5_Config_Rx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_TSL_EXP+(TsNum<<6));
	return tval;
}
/******************************************************************************
**
** function: RC6400_TU12_V5_Config_Tx_Set();
**_____________________________________________________________________________
**
** DESCRIPTION: Set the V5 value for a TU12 in send direction.
**
** Inputs:
**		TsNum:A TU12 to be set.Should be 0~62.
**		val:     The V5 value. Adviced value:0x0A.
** Outputs:none.
** RETURN:none.
**
*******************************************************************************/
void RC6400_TU12_V5_Config_Tx_Set(uint8 TsNum, uint8 val)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_V5_BYTE+(TsNum<<6));
	if(val!=tval)
		write(TU12_BASE_ADDR+cTU12_V5_BYTE+(TsNum<<6),val);
}
/******************************************************************************
**
** function: RC6400_TU12_V5_Config_Tx_Read();
**_____________________________________________________________________________
**
** DESCRIPTION: Read the V5 value of  a TU12 in send direction.
**
** Inputs:
**		TsNum:A TU12 to be set.Should be 0~62.
** Outputs:none.
** RETURN:The V5 value. Adviced value:0x0A.
**
*******************************************************************************/
uint8 RC6400_TU12_V5_Config_Tx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_V5_BYTE+(TsNum<<6));
	return tval;
}
/******************************************************************************
**
** function: RC6400_TU12_K4_Config_Rx_Set();
**_____________________________________________________________________________
**
** DESCRIPTION: Set the K4 value for a TU12 in receive direction.
**
** Inputs:
**		TsNum:A TU12 to be set.Should be 0~62.
**		val:     The K4 value. Adviced value:0x0D.
** Outputs:none.
** RETURN:none.
**
*******************************************************************************/
void RC6400_TU12_K4_Config_Rx_Set(uint8 TsNum, uint8 val)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_K4_B1_ESL_EXP+(TsNum<<6));
	if(val!=tval)
		write(TU12_BASE_ADDR+cTU12_RECV_K4_B1_ESL_EXP+(TsNum<<6), val);
}
/******************************************************************************
**
** function: RC6400_TU12_K4_Config_Rx_Read();
**_____________________________________________________________________________
**
** DESCRIPTION: Read  the K4 value of a TU12 in receive direction.
**
** Inputs:
**		TsNum:A TU12 to be set.Should be 0~62.
** Outputs:none.
** RETURN:The K4 value. Adviced value:0x0D.
**
*******************************************************************************/
uint8 RC6400_TU12_K4_Config_Rx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_K4_B1_ESL_EXP+(TsNum<<6));
	return tval;
}
/******************************************************************************
**
** function: RC6400_TU12_K4_Config_Tx_Set();
**_____________________________________________________________________________
**
** DESCRIPTION: Set the K4 value for a TU12 in send direction.
**
** Inputs:
**		TsNum:A TU12 to be set.Should be 0~62.
**		val:     The K4 value. Adviced value:0x0D.
** Outputs:none.
** RETURN:none.
**
*******************************************************************************/
void RC6400_TU12_K4_Config_Tx_Set(uint8 TsNum, uint8 val)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_SEND_K4_B1+(TsNum<<6));
	if(val!=tval)
	{
		write(TU12_BASE_ADDR+cTU12_SEND_K4_B1+(TsNum<<6), val);
	}
}
/******************************************************************************
**
** function: RC6400_TU12_K4_Config_Tx_Read();
**_____________________________________________________________________________
**
** DESCRIPTION: Read the K4 value of a TU12 in send direction.
**
** Inputs:
**		TsNum:A TU12 to be set.Should be 0~62.
** Outputs:none.
** RETURN:The K4 value. Adviced value:0x0D.
**
*******************************************************************************/
uint8 RC6400_TU12_K4_Config_Tx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_SEND_K4_B1+(TsNum<<6));
	return tval;
}
/******************************************************************************
**
** function: RC6400_TU12_Bus_Sel_Mode_Rx_Set();
**_____________________________________________________________________________
**
** DESCRIPTION: Set the mode of a TU12 in receive direction.
**
** Inputs: 
**          TsNum:The TU12 to be set.
**   		flag:The mode flag. Should be 00,01,10,11 or 0~3
** Outputs:none.
** RETURN:none.
**
******************************************************************************/
void RC6400_TU12_Bus_Sel_Mode_Rx_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	flag=(flag&3)<<3;
	if(flag!=(tval&cTU12_RECV_SEL_MOD)) {
		flag |= (tval & ~(3<<3));
		write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6),flag);
	}
}
/******************************************************************************
**
** function: RC6400_TU12_Bus_Sel_Mode_Rx_Read();
**_____________________________________________________________________________
**
** DESCRIPTION: Read the mode of a TU12 in receive direction.
**
** Inputs: 
**          TsNum:The TU12 to be set.
** Outputs:none.
** RETURN:The mode flag. Should be 00,01,10,11 or 0~3
**
******************************************************************************/
uint8 RC6400_TU12_Bus_Sel_Mode_Rx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	tval=(tval&cTU12_RECV_SEL_MOD)>>3;
	return tval;
	
}
/****************************************************************************
**
** function:RC6400_TU12_Bus_Sel_Force_Rx_Set();
**___________________________________________________________________________
**
** DESCRIPTION: Enable/Disable the bus select  FORCE bit.
**
** Inputs:
**           TsNum: The TU12 to be set.
**		 flag:  Enable or Disable flag.   1: Enable.    0: Disable.
** Outputs:none.
** Return:none.
**
*****************************************************************************/
void RC6400_TU12_Bus_Sel_Force_Rx_En_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	if(flag==1)
	{
		tval|=cTU12_RECV_SEL_FORCE;
	}
	else if(flag==0)
	{
		tval&=~cTU12_RECV_SEL_FORCE;
	}
	write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6), tval);
}
/****************************************************************************
**
** function:RC6400_TU12_Bus_Sel_Force_Rx_Read();
**___________________________________________________________________________
**
** DESCRIPTION: Read  FORCE bit of a VC12 maked by TsNum para.
**
** Inputs:
**           TsNum: The TU12 to be set.
** Outputs:none.
** Return:TRUE: Enable.    FALSE: Disable.
**
*****************************************************************************/
BOOL RC6400_TU12_Bus_Sel_Force_Rx_En_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	if(tval&cTU12_RECV_SEL_FORCE)
		return TRUE;
	else
		return FALSE;
}
/****************************************************************************
**
** function:RC6400_TU12_Bus_Sel_Exp_Sel_Rx_Set();
**___________________________________________________________________________
**
** DESCRIPTION: Config the expected bus for a TU12.
**
** Inputs:
**           TsNum: The TU12 to be set.
**		 flag: The bus flag. 0: A Bus       1: B Bus
** Outputs:none.
** Return:none.
**
*****************************************************************************/
void RC6400_TU12_Bus_Exp_Sel_Rx_Set(uint8 TsNum, uint8 flag)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	if(flag==0)		/*A bus*/
	{
		tval&=~cTU12_RECV_SEL_CONFIG;
	}
	else if(flag==1)	/*B Bus*/
	{
		tval|=cTU12_RECV_SEL_CONFIG;
	}
	write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6),tval);
}

/****************************************************************************
**
** function:RC6400_TU12_Bus_Sel_Exp_Sel_Rx_Read();
**___________________________________________________________________________
**
** DESCRIPTION: Config the expected bus for a TU12.
**
** Inputs:
**           TsNum: The TU12 to be set.
** Outputs:none.
** Return:The bus flag. 0: A Bus       1: B Bus
**
*****************************************************************************/
uint8 RC6400_TU12_Bus_Exp_Sel_Rx_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	if(tval&cTU12_RECV_SEL_CONFIG)
		return 1;
	else 
		return 0;
}
/****************************************************************************
**
** function:RC6400_TU12_Bus_Actual_Sel_Rx_Read();
**___________________________________________________________________________
**
** DESCRIPTION: Read the acutal bus of a TU12.
**
** Inputs:
**           TsNum: The TU12 to be read.
** Outputs:
**            flag: The bus flag. 0: A Bus       1: B Bus
** Return:none.
**
*****************************************************************************/
void RC6400_TU12_Bus_Actual_Sel_Rx_Read(uint8 TsNum, uint8* flag)
{
	*flag=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
	*flag=(*flag)&sTU12_RECV_SEL_ACTUAL;		/*0: A bus; 1: B Bus*/
}
/****************************************************************************
**
** func: RC6400_LCAS_Single_Ts_Remove_Tx();
**___________________________________________________________________________
**
**Description: Close the switch of a E1 in send direction in LCAS model.
** Inputs: 
**		TsNum: The E1 number, should be 0,1,2 ....3E.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_LCAS_Single_Ts_Remove_Tx(uint8 TsNum)
{
	#ifndef ACTIVE_FUNCTION_ENABLE
	RC6400_VC12_En_Tx_Set(TsNum,0);
	#endif
	
	RC6400_TU12_En_Tx_Set(TsNum,0);
}
/****************************************************************************
**
** func: RC6400_LCAS_Single_Ts_Remove_Rx();
**___________________________________________________________________________
**
**Description: Close the  switch of a E1 in receice direction in LCAS model.
** Inputs: 
**		TsNum: The E1 number, should be 0,1,2 ....3E.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_LCAS_Single_Ts_Remove_Rx(uint8 TsNum)
{
	RC6400_VC12_En_Rx_Set(TsNum, 0);
	RC6400_TU12_En_Rx_Set(TsNum, 0);
}
/****************************************************************************
**
** func: RC6400_NLCAS_Single_Ts_Remove_Tx();
**___________________________________________________________________________
**
**Description: Close the switch of a E1 in send direction in NON LCAS model.
** Inputs: 
**		TsNum: The E1 number, should be 0,1,2 ....3E.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_NLCAS_Single_Ts_Remove_Tx(uint8 TsNum)
{
	#ifndef ACTIVE_FUNCTION_ENABLE
	RC6400_VC12_En_Tx_Set(TsNum, 0);
	#endif
	
	RC6400_TU12_En_Tx_Set(TsNum, 0);
	RC6400_VC12_SQ_Tx_Set(TsNum, 0x3F);
}
/****************************************************************************
**
** func: RC6400_NLCAS_Single_Ts_Remove_Rx();
**___________________________________________________________________________
**
**Description: Close the  switch of a E1 in receice direction in NON LCAS model.
** Inputs: 
**		TsNum: The E1 number, should be 0,1,2 ....3E.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_NLCAS_Single_Ts_Remove_Rx(uint8 TsNum)
{
	RC6400_VC12_En_Rx_Set(TsNum, 0);
	RC6400_TU12_En_Rx_Set(TsNum, 0);
	RC6400_VC12_SQ_Rx_Set(TsNum, 0x3F);
}
/****************************************************************************
**
** func: RC6400_LCAS_Single_Ts_Add_Tx();
**___________________________________________________________________________
**
**Description: Add a E1 to a VCG group in send direction in LCAS model.
** Inputs: 
**		TsNum: The E1 number, should be 0,1,2 ....3E.
**		VCGNum: The VCG number the E1 is going add to.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_LCAS_Single_Ts_Add_Tx(uint8 TsNum,uint8 VCGNum)
{
	RC6400_VC12_GRP_Sel_Tx_Set(TsNum,VCGNum);
	RC6400_TU12_En_Tx_Set(TsNum, 1);
	
	#ifndef ACTIVE_FUNCTION_ENABLE
	RC6400_VC12_En_Tx_Set(TsNum, 1);
	#endif
}
/****************************************************************************
**
** func: RC6400_LCAS_Single_Ts_Add_Rx();
**___________________________________________________________________________
**
**Description: Add a E1 to a VCG group in receive  direction in LCAS model.
** Inputs: 
**		TsNum: The E1 number, should be 0,1,2 ....3E.
**		VCGNum: The VCG number the E1 is going add to.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_LCAS_Single_Ts_Add_Rx(uint8 TsNum,uint8 VCGNum)
{
	RC6400_VC12_GRP_Sel_Rx_Set(TsNum, VCGNum);
	RC6400_VC12_En_Rx_Set(TsNum, 1);
	RC6400_TU12_En_Rx_Set(TsNum, 1);
}
/****************************************************************************
**
** func: RC6400_NLCAS_Single_Ts_Add_Rx();
**___________________________________________________________________________
**
**Description: Add a E1 to a VCG group in receive  direction in NON LCAS model.
** Inputs: 
**		TsNum: The E1 number, should be 0,1,2 ....3E.
**		VCGNum: The VCG number the E1 is going add to.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_NLCAS_Single_Ts_Add_Rx(uint8 TsNum,uint8 VCGNum)
{
	RC6400_VC12_GRP_Sel_Rx_Set(TsNum, VCGNum);
	RC6400_VC12_En_Rx_Set(TsNum, 1);
	RC6400_TU12_En_Rx_Set(TsNum, 1);
}
/****************************************************************************
**
** func: RC6400_NLCAS_Single_Ts_Add_Tx();
**___________________________________________________________________________
**
**Description: Add a E1 to a VCG group in send direction in NON LCAS model.
** Inputs: 
**		TsNum: The E1 number, should be 0,1,2 ....3E.
**		VCGNum: The VCG number the E1 is going add to.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_NLCAS_Single_Ts_Add_Tx(uint8 TsNum,uint8 VCGNum)
{
	RC6400_VC12_GRP_Sel_Tx_Set(TsNum,VCGNum);
	RC6400_TU12_En_Tx_Set(TsNum, 1);
	
	#ifndef ACTIVE_FUNCTION_ENABLE
	RC6400_VC12_En_Tx_Set(TsNum, 1);
	#endif
}
/****************************************************************************
**
** func: RC6400_LCAS_VCAT_GRP_Remove();
**___________________________________________________________________________
**
**Description: Remove E1s in a VCG group that are not used anymore in bio-directions 
**			in LCAS model.
** Inputs: 
**		VCGNum: The VCG number in which the E1s are  going  to remove.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_LCAS_VCAT_GRP_Remove(uint8 VCGNum)
{
	uint8 i;
	uint8 valNew;
	uint8 valOld;

	for(i=0;i<MAX_CARD_E1_NUMBER;i++)
	{
		valNew=MarkTableNew[VCGNum][i];
		valOld=MarkTableOld[VCGNum][i];
		if(valNew<valOld)
		{
			RC6400_LCAS_Single_Ts_Remove_Rx(i);
			RC6400_LCAS_Single_Ts_Remove_Tx(i);
		}
	}
}
/****************************************************************************
**
** func: RC6400_LCAS_VCAT_GRP_Add();
**___________________________________________________________________________
**
**Description: Add E1s in a VCG group that are going to be used  in bio-directions 
**			in LCAS model.
** Inputs: 
**		VCGNum: The VCG number in which the E1s are  going  to add.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_LCAS_VCAT_GRP_Add(uint8 VCGNum)
{
	uint8 i;
	uint8 valNew;
	uint8 valOld;

	for(i=0;i<MAX_CARD_E1_NUMBER;i++)
	{
		valNew=MarkTableNew[VCGNum][i];
		valOld=MarkTableOld[VCGNum][i];
		if(valNew>valOld)
		{
			RC6400_LCAS_Single_Ts_Add_Rx(i,VCGNum);
			RC6400_LCAS_Single_Ts_Add_Tx(i,VCGNum);
		}
	}
}
/****************************************************************************
**
** func: RC6400_NLCAS_VCAT_GRP_Remove();
**___________________________________________________________________________
**
**Description: Remove E1s in a VCG group that are not used anymore in bio-directions 
**			in NON LCAS model.
** Inputs: 
**		VCGNum: The VCG number in which the E1s are  going  to remove.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_NLCAS_VCAT_GRP_Remove(uint8 VCGNum)
{
	uint8 i;
	uint8 valNew;
	uint8 valOld;

	for(i=0;i<MAX_CARD_E1_NUMBER;i++)
	{
		valNew=MarkTableNew[VCGNum][i];
		valOld=MarkTableOld[VCGNum][i];
		if(valNew<valOld)
		{
			RC6400_NLCAS_Single_Ts_Remove_Rx(i);
			RC6400_NLCAS_Single_Ts_Remove_Tx(i);
		}
	}
}
/****************************************************************************
**
** func: RC6400_NLCAS_VCAT_GRP_Add();
**___________________________________________________________________________
**
**Description: Add E1s in a VCG group that are going to be used  in bio-directions 
**			in NON LCAS model.
** Inputs: 
**		VCGNum: The VCG number in which the E1s are  going  to add.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_NLCAS_VCAT_GRP_Add(uint8 VCGNum)
{
	uint8 i;
	uint8 valNew;
	uint8 valOld;

	for(i=0;i<MAX_CARD_E1_NUMBER;i++)
	{
		valNew=MarkTableNew[VCGNum][i];
		valOld=MarkTableOld[VCGNum][i];
		if(valNew>valOld)
		{
			RC6400_NLCAS_Single_Ts_Add_Rx(i,VCGNum);
			RC6400_NLCAS_Single_Ts_Add_Tx(i,VCGNum);
		}
	}
}

void Delay32ms(void)
{
	uint16 i;

	for(i=0;i<20000;i++);
}
/****************************************************************************
**
** func: RC6400_SQ_Realing();
**___________________________________________________________________________
**
**Description: In NON LCAS model, the SQ will not be aligned automatically. The manager should
**			realign the SQ continually for the communition parts. 
**			in NON LCAS model.
** Inputs: 
**		VCGNum: The VCG which SQ is realigned by MCU from 0 to max.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_SQ_Realing(uint8 VCGNum)
{
	uint8 i;
	uint8 tval;
	uint8 j=0;

	for(i=0;i<MAX_CARD_E1_NUMBER;i++)
	{
		tval=MarkTableNew[VCGNum][i];
		if(tval)
		{
			RC6400_VC12_SQ_Tx_Set(i,j);
			j++;
		}
	}
}
#if 0
void VCG_Config_One(uint8 VCGNum)
{
	uint8 lcasNew;
	uint8 lcasOld;
	
	lcasNew=LcasFlagNew[VCGNum];
	lcasOld=LcasFlagOld[VCGNum];	
	
	//VCAT_Config_Valid_Rx(0);
	//VCAT_Config_Valid_Tx(0);

	if(lcasOld)
	{
		LCAS_VCAT_GRP_Remove(VCGNum);
	}
	else 
	{
		NLCAS_VCAT_GRP_Remove(VCGNum);
	}

	Dog_Food=1;
	if(lcasNew)
	{
		LCAS_En_Rx(VCGNum,LCAS_ENABLE);
		LCAS_En_Tx(VCGNum,LCAS_ENABLE);
		LCAS_VCAT_GRP_Add(VCGNum);
	}
	else
	{
		LCAS_En_Rx(VCGNum, LCAS_DISABLE);
		LCAS_En_Tx(VCGNum, LCAS_DISABLE);
		NLCAS_VCAT_GRP_Add(VCGNum);
		SQ_Realing(VCGNum);
	}
	Dog_Food=1;


	//VCAT_Config_Valid_Tx(1);
	//VCAT_Config_Valid_Rx(1);

	Delay32ms();
	
}
#endif
/****************************************************************************
**
** func: RC6400_VCG_Config_One_Remove();
**___________________________________________________________________________
**
**Description: This function has done the E1s removing in a VCG group maked by
**			VCGNum paras, both in LCAS and NON-LCAS models.
** Inputs: 
**		VCGNum: The VCG whose E1s are  removing .
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_VCG_Config_One_Remove(uint8 VCGNum)
{
	uint8 lcasOld;

	lcasOld=LcasFlagOld[VCGNum];
	if(lcasOld)
	{
		RC6400_LCAS_VCAT_GRP_Remove(VCGNum);
	}
	else 
	{
		RC6400_NLCAS_VCAT_GRP_Remove(VCGNum);
	}
	Delay32ms();
}
/****************************************************************************
**
** func: RC6400_VCG_Config_One_Add();
**___________________________________________________________________________
**
**Description: This function has done the E1s adding in a VCG group maked by
**			VCGNum paras, both in LCAS and NON-LCAS models.
** Inputs: 
**		VCGNum: The VCG whose E1s are  adding.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void RC6400_VCG_Config_One_Add(uint8 VCGNum)
{
	uint8 lcasNew;

	lcasNew=LcasFlagNew[VCGNum];

	if(lcasNew)
	{
		RC6400_LCAS_En_Rx_Set(VCGNum,LCAS_ENABLE);
		RC6400_LCAS_En_Tx_Set(VCGNum,LCAS_ENABLE);
		RC6400_LCAS_VCAT_GRP_Add(VCGNum);		
	}
	else
	{
		RC6400_LCAS_En_Rx_Set(VCGNum, LCAS_DISABLE);
		RC6400_LCAS_En_Tx_Set(VCGNum, LCAS_DISABLE);
		RC6400_NLCAS_VCAT_GRP_Add(VCGNum);
		RC6400_SQ_Realing(VCGNum);		
	}
	Delay32ms();
}
/****************************************************************************
**
** func: Update_MarkTable_New_One();
**___________________________________________________________________________
**
**Description: This function updates the marks that denote that which E1 is used or not, "1" means
**			 a E1 is being esed and "0" means a E1 is not being used. This function should be 
**			called before other config function are called.
** Inputs: 
**		pTsArr:The array of E1s that are being used.
**		VCGNum: The VCG whose E1s are  updating.
**		TsLen: The number of E1s or the length of the array pointed by pointer pTsArr.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void Update_MarkTable_New_One(uint8 VCGNum, uint8 * pTsArr, uint8 TsLen)
{
	uint8 i;
	uint8 tval;

	for(i=0;i<TsLen;i++)
	{
		tval=pTsArr[i];
		MarkTableNew[VCGNum][tval]=0x01;
	}
}
/****************************************************************************
**
** func: Update_MarkTable_Old_One();
**___________________________________________________________________________
**
**Description: This function copy the used E1 marks to the table MarkTableOld.
** Inputs: 
**		VCGNum: The VCG whose E1 makes are copyed.
** Outputs:none.
** Return: none.
**
*****************************************************************************/
void Update_MarkTable_Old_One(uint8 VCGNum)
{
	memcpy((uint8*)&MarkTableOld[VCGNum][0],(uint8*)&MarkTableNew[VCGNum][0],MAX_CARD_E1_NUMBER);
}

void Update_LCASTable_New_One(uint8 VCGNum, uint8 LcasFlag)
{
	LcasFlagNew[VCGNum]=LcasFlag;
}

void Update_LCASTable_Old_One(uint8 VCGNum)
{
	LcasFlagOld[VCGNum]=LcasFlagNew[VCGNum];
}
#if 0
/****************************************************************************
**
** function: RC6400_PTI_PFI_EXI_Set()
**___________________________________________________________________________
**
** DESCRIPTION: Set the PTI,PFI and EXI values of a GFP.
** Inputs: 
**		VCGNum: The VCG to be set.
**		SetValue: The GFP byte to be set to this value.
**                       bit7:5 : PTI
**                       bit4    : PFI
**                       bit3:0 : EXI
** Output:none
** RETURN: none
**
****************************************************************************/
void RC6400_PTI_PFI_EXI_Set(uint8 VCGNum, uint8 SetValue)
{
	uint8 tval;
	
	tval=read(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9));
	tval|=SetValue;
	write(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9),tval);
}
#endif
/*************************************************************************
**
** func: RC6400_PTI_Set();
**________________________________________________________________________
**
** DESCRIPTION: Set the PTI value.
** Inputs: 
**          VCGNum: The VCG to be set. Should be 0,1,2,3.
**          SetValue: The PTI value to set.
** Outputs: none.
** RETURN: none.
**
**************************************************************************/
void RC6400_PTI_Set(uint8 VCGNum, uint8 SetValue)
{
	uint8 tval;

	tval=read(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9));
	if((tval>>5)!=SetValue)
	{	
		tval&=0x1F;
		SetValue=SetValue<<5;
		tval|=SetValue;
		write(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9), tval);
	}
}
/*************************************************************************
**
** func: RC6400_PTI_Read();
**________________________________________________________________________
**
** DESCRIPTION: Read the PTI value of a VCG maked by the value VCGNum.
** Inputs: 
**          VCGNum: The VCG to be read. Should be 0,1,2,3.
** Outputs: none.
** RETURN: The PTI value of the VCG.
**
**************************************************************************/
uint8 RC6400_PTI_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9));
	tval=tval>>5;
	return tval;
}
/*************************************************************************
**
** func: RC6400_PFI_Set();
**________________________________________________________________________
**
** DESCRIPTION: Set the PFI value of a VCG maked by the value VCGNum.
** Inputs: 
**          VCGNum: The VCG to be set. Should be 0,1,2,3.
**          SetValue: The PFI value to set. 1 for FCS enabled and 0 for FCS disabled.
**				Dont fill it with other values except 0 and 1.
** Outputs: none.
** RETURN: none.
**
**************************************************************************/
void RC6400_PFI_Set(uint8 VCGNum, uint8 SetValue)
{
	uint8 tval;

	tval=read(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9));
	if(((tval&0x10)>>4)!=SetValue)
	{
		SetValue=SetValue<<4;
		tval&=0xEF;
		tval|=SetValue;
		write(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9), tval);
	}
}
/*************************************************************************
**
** func: RC6400_PFI_Read();
**________________________________________________________________________
**
** DESCRIPTION: Read the PFI value of a VCG maked by the value VCGNum.
** Inputs: 
**          VCGNum: The VCG to be read. Should be 0,1,2,3.
** Outputs: none.
** RETURN: The PFI value returned.  1 for FCS enabled.
**
**************************************************************************/
uint8 RC6400_PFI_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9));
	tval=(tval&0x10)>>4;
	return tval;
}
/*************************************************************************
**
** func: RC6400_EXI_Set();
**________________________________________________________________________
**
** DESCRIPTION: Set the EXI value of a VCG maked by the value of VCGNum.
** Inputs: 
**          VCGNum: The VCG to be set. Should be 0,1,2,3.
**          SetValue: The EXI value to set. 0 for NULL header frame and 1 for liner header frame.
** Outputs: none.
** RETURN: none.
**
**************************************************************************/
void RC6400_EXI_Set(uint8 VCGNum, uint8 SetValue)
{
	uint8 tval;

	tval=read(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9));
	if((tval&0x0F)!=SetValue)
	{
		tval&=0xF0;
		tval|=SetValue;
		write(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9), tval);
	}
}
/*************************************************************************
**
** func: RC6400_EXI_Read();
**________________________________________________________________________
**
** DESCRIPTION: Read the EXI value of a VCG maked by the value VCGNum.
** Inputs: 
**          VCGNum: The VCG to be read. Should be 0,1,2,3.
** Outputs: none.
** RETURN: The EXI value returned. 0 for NULL header frame and 1 for liner header frame.
**
**************************************************************************/
uint8 RC6400_EXI_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(cGROUP_GFP_SEND_CONFIG+(VCGNum<<9));
	tval&=0x0F;
	return tval;
}
/**************************************************************************
**
** function: RC6400_Check_FPGA_Ready();
**_________________________________________________________________________
**
** DESCRIPTION: Check if the FPGA programe is downloaded successfully. If success then
**                        user can access the registers defined in the RC6400.
** Inputs:none.
** Outputs:none.
** RETURN: 
**            BOOL : TRUE:ready;         FALSE: not ready.
**
***************************************************************************/
BOOL RC6400_Check_FPGA_Ready(void)
{
	uint8 result=FALSE;

	result = read(sGLOBAL_ID_PARTNUMBERH);
	if(result == 0x64)
		return TRUE;
	else
		return FALSE;
	
}
/**************************************************************************
**
** function: RC6400_Reset();
**_________________________________________________________________________
**
** DESCRIPTION: Reset the RC6400 chip.
** Inputs:  none.
** Outputs:none.
** RETURN: none.
**
**************************************************************************/
void RC6400_Reset(void)
{
	write(cGLOBAL_RESET,1);
}
/*************************************************************************
**
** func: RC6400_38MClk_Los_Checj()
**________________________________________________________________________
**
** Description: This function should be rewrite by yourself in order to realize what you 
**			want to do if you have detected the Loss-Recover of the 38MClk. The code
**			in here is the process of the MSTP Card :ES010
** Input: None
** Output: none
** return: none
**
**************************************************************************/
void RC6400_38MClk_Los_Check(void)
{
/*
	uint8 idata tval = 0;
	uint8 idata i;
	//DMU 有插拔行为，则软复位
   	tval=read(laGLOBAL_38MCLK_BYTE);

	if(((tval&0x40)==0x40)&&(Loss==1))
	{
		Recover=1;
	}

	if((tval&0x80)==0x80)
	{
		Loss=1;
		softReset=0;
	}

	if((softReset==1)&&(Recover==1))
	{	
		Delay32ms();
		Dog_Food=1;
		RC6400_Reset();
		Dog_Food=1;
		Delay32ms();
		GLOBAL_STATUS.SettingEnable=1;
		Recover=0;
		Loss=0;
		Dog_Food=1;
		for(i=0;i<CURRENT_CARD_VCG_NUMBER;i++)
		{
			memset(&MarkTableOld[i][0],0,CURRENT_CARD_E1_NUMBER);

		}
		memset(LcasFlagOld,0,CURRENT_CARD_VCG_NUMBER);
		Old_Card_Config.K4_B1=0x00;
		Old_Card_Config.V5=0x00;
	}
	else
	{
		if(Recover==1)
		{
			if(timeOutFlag==1)
			{
				Delay32ms();
				Dog_Food=1;
				RC6400_Reset();
				Dog_Food=1;
				GLOBAL_STATUS.SettingEnable=1;
				Dog_Food=1;
				for(i=0;i<CURRENT_CARD_VCG_NUMBER;i++)
				{
					memset(&MarkTableOld[i][0],0,CURRENT_CARD_E1_NUMBER);

				}
				memset(LcasFlagOld,0,CURRENT_CARD_VCG_NUMBER);
				Old_Card_Config.K4_B1=0x00;
				Old_Card_Config.V5=0x00;
				timeOutFlag=0;
				Recover=0;
				Loss=0;
			}
		}
		else
		{
			timeOutCnt=0;
		}
	}
*/
}

/*****************************************************************************
**
** func: RC6400_TU12_LockAlarmR_Read_Multi();
**____________________________________________________________________________
**
** DESCRIPTION: Read the LOCKALARM of TU12 in receive direction.
**
** Inputs: 
**  		busSel:  1: A        2:B
**		TsNums: The number of TU12s to be read.
**		pTsIndex: The array of TU12 to be read.
** 		pTsAlarms: The return alarms array of TU12.
**                            bit7:TU_AIS        bit6:TU_LOP          bit5:Uneq             bit4:VC_AIS
**                            bit3:PLM             bit2:RDI                bit1:K4_B1_LOM   bit0:K4_B1_PLM
** Outputs:none.
** RETURN: none
**
******************************************************************************/
void RC6400_TU12_LockAlarmR_Read_Multi(uint8 busSel, uint8 TsNums, uint8* pTsIndex, uint8 * pTsAlarms)
{
	uint8 i;
	uint8 ts;
	
	if(busSel==BUS_A)
	{
		for(i=0;i<TsNums;i++)
		{
			ts=pTsIndex[i];
			pTsAlarms[i]=read(TU12_BASE_ADDR+laTU12_RECV_A_ALARM+(ts<<6));
		}
	}
	else if(busSel==BUS_B)
	{
		for(i=0;i<TsNums;i++)
		{
			ts=pTsIndex[i];
			pTsAlarms[i]=read(TU12_BASE_ADDR+laTU12_RECV_B_ALARM+(ts<<6));
		}
	}
}
/*****************************************************************************
**
** func: RC6400_TU12_LockAlarmR_Read_Single();
**____________________________________________________________________________
**
** DESCRIPTION: Read the LOCKALARM of TU12 in receive direction.
**
** Inputs: 
**  		busSel:  1: A        2:B
**		TsNum: The TU12 to be read.
** Outputs:none.
** RETURN: The alarm value returned. 
**                            bit7:TU_AIS        bit6:TU_LOP          bit5:Uneq             bit4:VC_AIS
**                            bit3:PLM             bit2:RDI                bit1:K4_B1_LOM   bit0:K4_B1_PLM
**
******************************************************************************/
uint8 RC6400_TU12_LockAlarmR_Read_Single(uint8 busSel, uint8 TsNum)
{
	uint8 tval=0;

	if(busSel==BUS_A)
	{
		tval=read(TU12_BASE_ADDR+laTU12_RECV_A_ALARM+(TsNum<<6));
	}
	else if(busSel==BUS_B)
	{
		tval=read(TU12_BASE_ADDR+laTU12_RECV_B_ALARM+(TsNum<<6));
	}
	return tval;
}
/*****************************************************************************
**
** func: RC6400_VC12_AlarmR_Read_Multi();
**____________________________________________________________________________
**
** DESCRIPTION: Read the ALARM of VC12 in receive direction.
**
** Inputs: 
**		TsNums: The number of VC12s to be read.
**		pTsIndex: The array of VC12 to be read.
** 		
** Outputs:
**             pTsAlarms: The return alarm array of VC12. Each byte indicates as below:
**					bit0: SQ 不匹配告警锁存
**					bit1: LCAS CRC 错告警锁存
**					bit2: LCAS ADD 成功告警锁存
**					bit3: LCAS FAIL 告警锁存
**					bit4: LCAS REMOVE 告警锁存
**					bit5: K4B1 失步
** 					bit6: MFI累加违例
**					bit7: 支路通道总告警(包括通道AIS ,K4Bit1 LOF) 
** RETURN: none
**
******************************************************************************/
void RC6400_VC12_AlarmR_Read_Multi(uint8 TsNums, uint8 * pTsIndex, uint8 * pTsAlarms)
{
	uint8 i;
	uint8 ts;

	for(i=0;i<TsNums;i++)
	{
		ts=pTsIndex[i];
		pTsAlarms[i]=read(VC12_BASE_ADDR+laVC12_RECV_ALARM+(ts<<6));
	}
}

uint8 RC6400_VC12_AlarmR_Read_Single(uint8 TsNum)
{
	uint8 tval=0;

	tval=read(VC12_BASE_ADDR+laVC12_RECV_ALARM+(TsNum<<6));
	return tval;
}
/*****************************************************************************
**
** func: RC6400_VC12_AlarmT_Read_Multi();
**____________________________________________________________________________
**
** DESCRIPTION: Read the ALARM of VC12 in send direction.
**
** Inputs: 
**		TsNums: The number of VC12s to be read.
**		pTsIndex: The array of VC12 to be read.
**
** Outputs:
**            pTsAlarms: The return alarm array of VC12. Each byte indicates as below:
**                              1: DNU alarm.          0: No alarm.
** RETURN: none
**
******************************************************************************/
void RC6400_VC12_AlarmT_Read_Multi(uint8 TsNums, uint8 * pTsIndex, uint8 * pTsAlarms)
{
	uint8 i;
	uint8 ts;

	for(i=0;i<TsNums;i++)
	{
		ts=pTsIndex[i];
		pTsAlarms[i]=read(VC12_BASE_ADDR+laVC12_SEND_LCAS_DNU+(ts<<6));
	}
}

uint8 RC6400_VC12_AlarmT_Read_Single(uint8 TsNum)
{
	uint8 tval=0;

	tval=read(VC12_BASE_ADDR+laVC12_SEND_LCAS_DNU+(TsNum<<6));
	return tval;
}
/*******************************************************************************************
**
** func: RC6400_VCAT_AlarmT_Read();
**__________________________________________________________________________________________
**
** DESCRIPTION: Read the VCAT group alarm in send direction.
**
** Inputs: 
**           VCGNum: The VCG's alarm to be read.
** Outputs: 
**            pAlarmByte:    1: DNU alarm.               0: NO ALARM
** RETURN: none.
**
********************************************************************************************/
void RC6400_VCAT_AlarmT_Read(uint8 VCGNum, uint8 * pVCGAlarm)
{
	if( VCGNum > 3 )
		return;
	*pVCGAlarm = read(laGROUP_VCAT_SEND_TLOPRD2+(VCGNum<<9));
}
/*******************************************************************************************
**
** func: RC6400_VCAT_AlarmT_Read_v2();
**__________________________________________________________________________________________
**
** DESCRIPTION: Read the VCAT group alarm in send direction.
**
** Inputs: 
**           VCGNum: The VCG's alarm to be read.
** Outputs:none
** RETURN: Returned alarm
**            pAlarmByte:    1: DNU alarm.               0: NO ALARM
**
********************************************************************************************/
uint8 RC6400_VCAT_AlarmT_Read_V2(uint8 VCGNum)
{
	 uint8 tval=0;

	 tval=read(laGROUP_VCAT_SEND_TLOPRD2+(VCGNum<<9));
	 return tval;
}
/*******************************************************************************************
**
** func: RC6400_VCAT_AlarmR_Read();
**__________________________________________________________________________________________
**
** DESCRIPTION: Read the VCAT group alarm in receive direction.
** Inputs: 
**           VCGNum: The VCG's alarm to be read. Should be 0,1,2,3.
** Outputs:
**           pVCGAlarm:  bit0: 组成员丢失告警
**                               bit1: 组对准丢失告警锁存
**                               bit2: GID 不匹配锁存告警
**                               bit3: RX SDRAM FIFO 溢出告警锁存
** RETURN: none.
**
********************************************************************************************/
void RC6400_VCAT_AlarmR_Read(uint8 VCGNum, uint8 * pVCGAlarm)
{
	if( VCGNum > 3 )
		return;
	*pVCGAlarm = read(laGROUP_VCAT_RECV_ALARM+(VCGNum<<9));
}
/*******************************************************************************************
**
** func: RC6400_38MClk_Alarm_Read();
**__________________________________________________________________________________________
**
** Description: Read the 38M clock alarm.
** Inputs: none.
** Outputs: 
**             pAlarmByte: 0x80:38M clock loss alarm or bit7 denotes 1.      
**                                0x40: 38M clock recover alarm or bit6 denotes 1.
** RETURN: none
**
********************************************************************************************/
 void RC6400_38MClk_Alarm_Read(uint8 * pAlarmByte)
{
	*pAlarmByte = read(laGLOBAL_38MCLK_BYTE);
}

/*******************************************************************************************
**
** func: RC6400_VCAT_GLOBAL_AlarmR_Read();
**__________________________________________________________________________________________
**
** DESCRIPTION: Read the VCAT GLOBAL alarm in recieve direction.
** Inputs: none.
** Outpus: 
**            pAlarmByte1:     bit0: 成员SQ 不匹配总告警
**                                     bit1: 成员LCAS CRC 错总告警
**                                     bit2: 成员LCAS ADD 成功总告警
**                                     bit3: 成员LCAS FAIL 总告警
**                                     bit4: 成员LCAS REMOVE 成功总告警
**
**            pAlarmByte2:     bit0:  VCG 成员丢失总告警
**                                     bit1:  VCG 对准丢失总告警
**                                     bit2:  VCG GID 不匹配总告警
**                                     bit3:  RX  SDRAM FIFO 溢出总告警
**
**                                     1 有效
** RETURN: none.
**
********************************************************************************************/             
void RC6400_VCAT_GLOBAL_AlarmR_Read(uint8 * pAlarmByte1, uint8 * pAlarmByte2)
{
	*pAlarmByte1 = read(laGLOBAL_LaVCR_BYTE);
	*pAlarmByte2 = read(laGLOBAL_LaVCR_VCAT_BYTE);
}
/*******************************************************************************************
**
** func: RC6400_VCAT_GLOBAL_Alarm_Read();
**__________________________________________________________________________________________
**
** DESCRIPTION: Read the VCAT GLOBAL alarm in send direction.
**
** Inputs: none.
** Outputs: 
**            pAlarmByte:    1: DNU alarm.               0: NO ALARM
** RETURN: none.
**
********************************************************************************************/
void RC6400_VCAT_GLOBAL_AlarmT_Read(uint8 * pAlarmByte)
{
	*pAlarmByte = read(laGLOBAL_AVCT_DNU);
}

/*******************************************************************************************
**
** func: RC6400_DeFrame_Syn_Alarm_Read();
**__________________________________________________________________________________________
**
** DESCRIPTION: Read the GFP deframe synchronous alarm.
** Inputs: 
** 		VCGNum: The vcg to be read. Should be 0,1,2,3.
** Outputs:none.
** RETURN:TRUE for syn, FALSE for asyn.
**
*******************************************************************************************/
BOOL RC6400_DeFrame_Syn_Alarm_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(LaGR_Alarm_Byte+(VCGNum<<9));
	if(tval&0x02)
		return 1;
	else 
		return 0;
}
/******************************************************************************************
**
** func: RC6400_Alarm_Clear_All_Init();
**________________________________________________________________________________________
**
** Description: Clear all the alarm regs at the beginning.
** Inputs:none.
** Outputs:none.
** RETURN:none.
**
******************************************************************************************/
void RC6400_Alarm_Clear_All_Init(void)
{
	uint8 i;

	for(i=0;i<CURRENT_CARD_VCG_NUMBER;i++)
	{
		read(LaGR_Alarm_Byte+(i<<9));
	}

}
/*****************************************************************************************
** func: RC6400_VC12R_SQ_Status_Read();
**________________________________________________________________________________________
**
** Description: Get the SQ status value of a VC12 in receive direction.
** 
** Input: 
**		TsNum: The number of a VC12, could be 0~62
** Output: none
** Return:
**		uint8: The SQ status value returned. Should be 0~62
**
*****************************************************************************************/
uint8 RC6400_VC12R_SQ_Status_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+sVC12_RECV_LOSQ+(TsNum<<6));
	tval&=0x3F;
	return tval;
}
/*****************************************************************************************
** func: RC6400_VC12T_SQ_Status_Read();
**________________________________________________________________________________________
**
** Description: Get the SQ status value of a VC12 in send direction.
** Input:
**		TsNum: The number of a VC12, could be 0~62
** Output:none
** Return:
**		uint8: The SQ status value returned. Should be 0~62
**
*****************************************************************************************/
uint8 RC6400_VC12T_SQ_Status_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+sVC12_SEND_LOSQ+(TsNum<<6));
	tval&=0x3F;/*Bit5:Bit0*/
	return tval;
}
/*****************************************************************************************
** func: RC6400_VC12R_CTRL_Status_Read();
**________________________________________________________________________________________
**
** Description: Get the CTRL status value of a VC12 in receive direction.
** Input:
**		TsNum: The number of a VC12, could be 0~62
** Output:none
** Return:
**		uint8: The CTRL status value returned.
**			0000:  non-lcas
**			0001: add
**			0010: norm
**			0011: eos
**			0101: idle
**			1111: dnu
**
*****************************************************************************************/
uint8 RC6400_VC12R_CTRL_Status_Read(uint8 TsNum)
{
 	uint8 tval;

	tval=read(VC12_BASE_ADDR+sVC12_RECV_LOCTRL+(TsNum<<6));
	return tval;
}
/*****************************************************************************************
** func: RC6400_VC12T_CTRL_Status_Read();
**________________________________________________________________________________________
**
** Description: Get the CTRL status value of a VC12 in send direction.
** Input:
**		TsNum: The number of a VC12, could be 0~62
** Output:none
** Return:
**		uint8: The CTRL status value returned.
**			0000:  non-lcas
**			0001: add
**			0010: norm
**			0011: eos
**			0101: idle
**			1111: dnu
**
*****************************************************************************************/
uint8 RC6400_VC12T_CTRL_Status_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+sVC12_SEND_LOCTRL+(TsNum<<6));
	return tval;
}
/*****************************************************************************************
** func: RC6400_VC12R_UseInfos_Status_Read();
**________________________________________________________________________________________
**
** Description: Get some improtant status of a VC12 in receive direction, such as config infos, useing status etc. 
** Input:
**		TsNum: The number of a VC12, could be 0~62
** Output:none
** Return:
** 		uint8: The return status value, each bit denote a meaning as follow shows:
**			bit2-bit0: The group number of the VC12,could be 00, 01,10, 11
**			bit3:        The flag to config it in use or not. 1: use    0: not use
**			bit4:		This bit denotes that if the VC12 is now in configed group or not. 1: in group  0: not in
*****************************************************************************************/
uint8 RC6400_VC12R_UseInfos_Status_Read(uint8 TsNum)
{
	uint8 tval;

	tval=read(VC12_BASE_ADDR+sVC12_RECV_STATUS+(TsNum<<6));
	return tval;
}
/*****************************************************************************************
** func: RC6400_VC12T_UseInfos_Status_Read();
**________________________________________________________________________________________
**
** Description: Get some improtant status of a VC12 in send direction, such as config infos, useing status etc. 
** Input:
**		TsNum: The number of a VC12, could be 0~62
** Output:none
** Return:
** 		uint8: The return status value, each bit denote a meaning as follow shows:
**			bit2-bit0:The group number of the VC12,could be 00 ,01 ,10 ,11
**			bit3: 	 in use or not. 1: in use    0: not in use
**			bit4:		In selected group or not. 1: In group    0: not in group
**			bit5:		This bit denotes if this VC12's adding process has been over. 1: Over   0: adding
*****************************************************************************************/
uint8 RC6400_VC12T_UseInfos_Status_Read(uint8 TsNum)
{
 	uint8 tval;

	tval=read(VC12_BASE_ADDR+sVC12_SEND_STATUS+(TsNum<<6));
	return tval;
}
/*********************************************************************************************
**
** func: RC6400_GFP_DeFrame_Syn_Status_Read();
**____________________________________________________________________________________________
**
** DESCRIPTION: Read the status of GFP deframe 
** Inputs:
**		VCGNum: The VCG to be read.
** Outputs:none.
** Return:TRUE if syn.
**
*********************************************************************************************/
BOOL RC6400_GFP_DeFrame_Syn_Status_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(sGROUP_GFP_DEFRAME_SYN+(VCGNum<<9));
	tval&=0x01;
	if(tval)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	
/*********************************************************************************************
**
** func: RC6400_GFP_DeFrame_PTI_Status_Read();
**____________________________________________________________________________________________
**
** DESCRIPTION: Read the status of GFP PFI 
** Inputs:
**		VCGNum: The VCG to be read.
** Outputs:none.
** Return:  0: data frame           8: manage frame.
**
*********************************************************************************************/
uint8 RC6400_GFP_DeFrame_PTI_Status_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(sGROUP_GFP_DEFRAME_PTIPFIEXI+(VCGNum<<9));
	tval=(tval&0xE0)>>5;
	return tval;
}
/*********************************************************************************************
**
** func: RC6400_GFP_DeFrame_PFI_Status_Read();
**____________________________________________________________________________________________
**
** DESCRIPTION: Read the status of GFP PFI 
** Inputs:
**		VCGNum: The VCG to be read.
** Outputs:none.
** Return:1 to use FCS , 0 for no unsing FCS.
**
*********************************************************************************************/
uint8 RC6400_GFP_DeFrame_PFI_Status_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(sGROUP_GFP_DEFRAME_PTIPFIEXI+(VCGNum<<9));
	tval=(tval&0x10)>>4;
	return tval;
}
/*********************************************************************************************
**
** func: RC6400_GFP_DeFrame_EXI_Status_Read();
**____________________________________________________________________________________________
**
** DESCRIPTION: Read the status of GFP EXI 
** Inputs:
**		VCGNum: The VCG to be read.
** Outputs:none.
** Return:0 for null header,1 for liner header.
**
*********************************************************************************************/
uint8 RC6400_GFP_DeFrame_EXI_Status_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(sGROUP_GFP_DEFRAME_PTIPFIEXI+(VCGNum<<9));
	tval&=0x0F;
	return tval;
}
/*********************************************************************************************
**
** func: RC6400_TU12_BIP2_Perform_Read();
**____________________________________________________________________________________________
**
** DESCRIPTION: Read the BIP2 counter of a TU12 maked by para TsNum on the A bus if para BusSel is 1 and
**				B bus if the para BusSel is 2.
** Inputs:
**		BusSel: The 1+1 bus selection, 1 for Bus A and 2 for Bus B.
**		TsNum: The tu12 to be read.
** Outputs:none.
** Return:The counter of BIP2 , 2 bytes.
**
*********************************************************************************************/
uint16 RC6400_TU12_BIP2_Perform_Read(uint8 BusSel, uint8 TsNum)
{
	uint16 tval=0;

	if(BusSel==BUS_A)
	{
		tval=read(TU12_BASE_ADDR+rpcTU12_RECV_A_BIP2_CNTH+(TsNum<<6));
		tval=tval<<8;
		tval+=read(TU12_BASE_ADDR+rpcTU12_RECV_A_BIP2_CNTL+(TsNum<<6));
	}
	else if(BusSel==BUS_B)
	{
		tval=read(TU12_BASE_ADDR+rpcTU12_RECV_B_BIP2_CNTH+(TsNum<<6));
		tval=tval<<8;
		tval+=read(TU12_BASE_ADDR+rpcTU12_RECV_B_BIP2_CNTL+(TsNum<<6));
	}
	return tval;
}
/*****************************************************************************************
**
** function: RC6400_TU12_PJE_Perform_Read();
**________________________________________________________________________________________
**
** DESCRIPTION: Read the PJE perfrom counter of a TU12 maked by para TsNum and A or B bus maked 
**                        by para BusSel.
** Inputs:
**		BusSel: 1:A bus     2: B bus
**		TsNum: The TU12 to be read.
** Outputs:none.
** RETURN: The counter of PJE ,1 byte.
**
******************************************************************************************/
uint8 RC6400_TU12_PJE_Perform_Read(uint8 BusSel, uint8 TsNum)
{
	uint8 tval=0;

	if(BusSel==BUS_A)
	{
		tval=read(TU12_BASE_ADDR+rpcTU12_RECV_A_PJE_CNT+(TsNum<<6));
	}

	else if(BusSel==BUS_B)
	{
		tval=read(TU12_BASE_ADDR+rpcTU12_RECV_B_PJE_CNT+(TsNum<<6));
	}
	return tval;
}
/*****************************************************************************************
**
** function: RC6400_TU12_NJE_Perform_Read();
**________________________________________________________________________________________
**
** DESCRIPTION: Read the NJE perfrom counter of a TU12 maked by para TsNum and A or B bus maked 
**                        by para BusSel.
** Inputs:
**		BusSel: 1:A bus     2: B bus
**		TsNum: The TU12 to be read.
** Outputs:none.
** RETURN: The counter of NJE ,1 byte.
**
******************************************************************************************/
uint8 RC6400_TU12_NJE_Perform_Read(uint8 BusSel, uint8 TsNum)
{
	uint8 tval=0;

	if(BusSel==BUS_A)
	{
		tval=read(TU12_BASE_ADDR+rpcTU12_RECV_A_NJE_CNT+(TsNum<<6));
	}
	else if(BusSel==BUS_B)
	{
		tval=read(TU12_BASE_ADDR+rpcTU12_RECV_B_NJE_CNT+(TsNum<<6));
	}
	return tval;
}
/*****************************************************************************************
**
** function: RC6400_TU12_REI_Perform_Read();
**________________________________________________________________________________________
**
** DESCRIPTION: Read the REI perfrom counter of a TU12 maked by para TsNum and A or B bus maked 
**                        by para BusSel.
** Inputs:
**		BusSel: 1:A bus     2: B bus
**		TsNum: The TU12 to be read.
** Outputs:none.
** RETURN: The counter of REI ,2 bytes.
**
******************************************************************************************/
uint16 RC6400_TU12_REI_Perform_Read(uint8 BusSel, uint8 TsNum)
{
	uint16 tval=0;

	if(BusSel==BUS_A)
	{
		tval=read(TU12_BASE_ADDR+rpcTU12_RECV_A_REI_CNTH+(TsNum<<6));
		tval=tval<<8;
		tval+=read(TU12_BASE_ADDR+rpcTU12_RECV_A_REI_CNTL+(TsNum<<6));
	}
	else if(BusSel==BUS_B)
	{
		tval=read(TU12_BASE_ADDR+rpcTU12_RECV_B_REI_CNTH+(TsNum<<6));
		tval=tval<<8;
		tval+=read(TU12_BASE_ADDR+rpcTU12_RECV_B_REI_CNTL+(TsNum<<6));
	}
	return tval;
}
/*******************************************************************************
**
** func: RC6400_GFP_Frame_AllPkts_Perform_Read();
**______________________________________________________________________________
**
** Description: Read the GFP total Pkts in send direction
** Inputs:
**		VCGNum: The VCG group number.Should be 0,1,2 or 3.
** Outputs: None.
** Return: 16-bit return value.
********************************************************************************/
uint16 RC6400_GFP_Frame_AllPkts_Perform_Read(uint8 VCGNum)
{
	uint16 tval=0;

	tval=read(rpcGROUP_GFP_FRAME_ALLPktH+(VCGNum<<9));
	tval=tval<<8;
	tval+=read(rpcGROUP_GFP_FRAME_ALLPktL+(VCGNum<<9));
	return tval;
}
/*******************************************************************************
**
** func: RC6400_GFP_Frame_ErrPkts_Perform_Read();
**______________________________________________________________________________
**
** Description: Read the GFP error Pkts in send direction
** Inputs:
**		VCGNum: The VCG group number.Should be 0,1,2 or 3.
** Outputs: None.
** Return: 16-bit return value.
********************************************************************************/
uint8 RC6400_GFP_Frame_ErrPkts_Perform_Read(uint8 VCGNum)
{
	uint8 tval;

	tval=read(rpcGROUP_GFP_FRAME_ErrPkt+(VCGNum<<9));
	return tval;
}
/*******************************************************************************
**
** func: RC6400_GFP_Frame_AllBytes_Perform_Read();
**______________________________________________________________________________
**
** Description: Read the GFP total bytes in send direction
** Inputs:
**		VCGNum: The VCG group number.Should be 0,1,2 or 3.
** Outputs: None.
** Return: 32-bit return value.
********************************************************************************/
uint32 RC6400_GFP_Frame_AllBytes_Perform_Read(uint8 VCGNum)
{
	uint32 tval=0;

	tval=read(rpcGROUP_GFP_FRAME_ALLByteH+(VCGNum<<9));
	tval=tval<<8;
	tval+=read(rpcGROUP_GFP_FRAME_AllByteM+(VCGNum<<9));
	tval=tval<<8;
	tval+=read(rpcGROUP_GFP_FRAME_AllByteL+(VCGNum<<9));
	return tval;
}
/*******************************************************************************
**
** func: RC6400_GFP_DeFrame_AllPkts_Perform_Read();
**______________________________________________________________________________
**
** Description: Read the GFP total  pkts in receive direction
** Inputs:
**		VCGNum: The VCG group number.Should be 0,1,2 or 3.
** Outputs: None.
** Return: 16-bit return value.
********************************************************************************/
uint16 RC6400_GFP_DeFrame_AllPkts_Perform_Read(uint8 VCGNum)
{
	uint16 tval;

	tval=read(rpcGROUP_GFP_DEFRAME_ALLPktH+(VCGNum<<9));
	tval=tval<<8;
	tval+=read(rpcGROUP_GFP_DEFRAME_ALLPktL+(VCGNum<<9));
	return tval;
}
/*******************************************************************************
**
** func: RC6400_GFP_DeFrame_ErrPkts_Perform_Read();
**______________________________________________________________________________
**
** Description: Read the GFP error pkts in receive direction
** Inputs:
**		VCGNum: The VCG group number.Should be 0,1,2 or 3.
** Outputs: None.
** Return: 16-bit return value.
********************************************************************************/
uint16 RC6400_GFP_DeFrame_ErrPkts_Perform_Read(uint8 VCGNum)
{
	uint16 tval=0;

	tval=read(rpcGROUP_GFP_DEFRAME_ERRPktH+(VCGNum<<9));
	tval=tval<<8;
	tval+=read(rpcGROUP_GFP_DEFRAME_ERRPktL+(VCGNum<<9));
	return tval;
}
/*******************************************************************************
**
** func: RC6400_GFP_DeFrame_AllBytes_Perform_Read();
**______________________________________________________________________________
**
** Description: Read the GFP total bytes in receive direction, including all good Pkts.
** Inputs:
**		VCGNum: The VCG group number.Should be 0,1,2 or 3.
** Outputs: None.
** Return: 32-bit return value.
********************************************************************************/
uint32 RC6400_GFP_DeFrame_AllBytes_Perform_Read(uint8 VCGNum)
{
	uint32 tval=0;

	tval=read(rpcGROUP_GFP_DEFRAME_ALLBytesH+(VCGNum<<9));
	tval=tval<<8;
	tval+=read(rpcGROUP_GFP_DEFRAME_ALLBytesM+(VCGNum<<9));
	tval=tval<<8;
	tval+=read(rpcGROUP_GFP_DEFRAME_ALLBytesL+(VCGNum<<9));
	return tval;
}

/*******************************************************************************
**
** func: get_drv_pkt_info();
**______________________________________________________________________________
**
** Description: Read tht FPGA version
** Inputs: none
** Outputs: None.
** Return: Soft version of FPGA .
********************************************************************************/
uint8 get_drv_pkt_info(void)
{
	uint8 verSoft;

	verSoft=read(sGLOBAL_VERSION);
	return verSoft;
}
/*******************************************************************************
**
** func: get_IC_info();
**______________________________________________________________________________
**
** Description: Read tht IC type, should be 0x64
** Inputs: none
** Outputs: None.
** Return: 0x64 .
********************************************************************************/
uint8 get_IC_info(void)
{
	uint8 verIC;
	
	verIC=read(sGLOBAL_ID_PARTNUMBERH);
	return verIC;
}

void RC6400_Pause_Config(uint8 VCGNum,uint8 flag) {
	uint32 tval=0;

	tval=read(0x01+(VCGNum<<9));
	tval &= ~1;
	tval |= flag;
	write(0x01+(VCGNum<<9), tval);
}
