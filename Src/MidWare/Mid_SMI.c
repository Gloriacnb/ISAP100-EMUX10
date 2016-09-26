/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_SMI.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_SMI.c
** Created by:          Administrator
** Created date:        2012-12-17
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

#include "Mid_SMI.h"
#include "ChipGluLogic.h"


uint32 SMIReadByte(uint8 phyAddr, uint8 RegAddr, uint16* newData) {
	uint8 tempH = 0;
	uint8 tempL = 0;
	if( glulogic == NULL ) {
		return FALSE;
	}
	glulogic->SMI_REGAD = RegAddr;
	glulogic->SMI_PHYAD = phyAddr | SMI_CMD_READ;//(((phyAddr | SMI_PHY_PRE) + 1)&0x1f) | SMI_CMD_READ;
	while( !(glulogic->SMI_PHYAD & 0x80) );
	tempH = glulogic->SMI_DH;
	tempL = glulogic->SMI_DL;
	*newData = (tempH<< 8) | tempL;
	return TRUE;
}

uint32 SMIWriteByte(uint8 phyAddr, uint8 RegAddr, uint16 newData) {

	if( glulogic == NULL ) {
		return FALSE;
	}
	glulogic->SMI_DH = (uint8)(newData >> 8);
	glulogic->SMI_DL = (uint8)(newData >> 0);
	glulogic->SMI_REGAD = RegAddr;
	glulogic->SMI_PHYAD = phyAddr | SMI_CMD_WRITE;//(((phyAddr | SMI_PHY_PRE) + 1)&0x1f) | SMI_CMD_WRITE;
	while( !(glulogic->SMI_PHYAD & 0x80) );
	return TRUE;

}

uint32 EthnetPHYRead(uint8 chipID, uint8 phyAddr, uint8 RegAddr, uint16* newData) {
	glulogic->I2C_SEL = chipID;
	SMIReadByte(phyAddr, RegAddr, newData);
	glulogic->I2C_SEL = 4;
	return TRUE;
}


uint32 EthnetPHYWrite(uint8 chipID, uint8 phyAddr, uint8 RegAddr, uint16 newData) {
	glulogic->I2C_SEL = chipID;
	SMIWriteByte(phyAddr, RegAddr, newData);
	glulogic->I2C_SEL = 4;
	return TRUE;
}

/*********************************************************************************************************
** Function name:   	RTL8306EPHYWrite
** Descriptions:        дRTL8306E�ļĴ���
** input parameters:    phyad       PHY ID 
                       	REGAddr     �Ĵ�����ַ
						PHYData     PHY�Ĵ����е�����
** output parameters:   NONE
** Returned value:      �ɹ���ʧ��                                
** Created by:			Wang ying                                           
** Created Date:		2010-12-16                                            
**--------------------------------------------------------------------------------------------------------
** Modified by:			                                            
** Modified date:			                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 RTL8306EPHYWrite( uint32 PHYID, uint32 REGAddr, uint16 PHYData )
{
	if ( REGAddr > 0x1fff || PHYID > 6 ){
		return FALSE;
	}
	return SMIWriteByte( PHYID, REGAddr, PHYData );
}

/*********************************************************************************************************
** Function name:   	RTL8306EPHYRead
** Descriptions:        ��RTL8306E�ļĴ���
** input parameters:    phyad       PHY ID 
                       	REGAddr     �Ĵ�����ַ						
** output parameters:   PHYData     PHY�Ĵ����е�����
** Returned value:      �ɹ���ʧ��                                
** Created by:			Wang ying                                           
** Created Date:		2010-12-16                                            
**--------------------------------------------------------------------------------------------------------
** Modified by:			                                            
** Modified date:			                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 RTL8306EPHYRead( uint32 PHYID, uint32 REGAddr, uint16* PHYData )
{
	uint16 PHYDataValue = 0;
	if( REGAddr > 0x1fff || PHYID > 24 || PHYData == NULL){
		return FALSE;
	}	
	SMIReadByte( PHYID, REGAddr, &PHYDataValue );
	*PHYData = PHYDataValue;
	return TRUE; 
}

/*********************************************************************************************************
** Function name:   	RTL8306EPHYWriteBit
** Descriptions:        дRTL8306E�ļĴ����е�һ��BIT
** input parameters:    PHY_ID       PHY ID 
                       	register_address     �Ĵ�����ַ	
						bit_position         �Ĵ����е�һλ
						value       д���1bit����					
** output parameters:   NONE
** Returned value:      �ɹ���ʧ��                                
** Created by:			Wang ying                                           
** Created Date:		2010-12-16                                            
**--------------------------------------------------------------------------------------------------------
** Modified by:			                                            
** Modified date:			                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 RTL8306EPHYWriteBit( uint32 PHY_ID, uint32 register_address, uint32 bit_position, uint32 value )
{
	uint16 temp = 0;
	if( PHY_ID > 31 || bit_position >15 || value > 1 ){
		return FALSE;
	}
	SMIReadByte(PHY_ID,register_address, &temp);
	temp &= ~(1<<bit_position);
	temp |= (value<<bit_position);
	return SMIWriteByte( PHY_ID, register_address,temp );
}

/*********************************************************************************************************
** Function name:   	RTL8306EPHYReadBit
** Descriptions:        ��RTL8306E�ļĴ����е�һ��BIT
** input parameters:    PHY_ID       PHY ID 
                       	register_address     �Ĵ�����ַ	
						bit_position         �Ĵ����е�һλ											
** output parameters:   value       д���1bit����
** Returned value:      �ɹ���ʧ��                                
** Created by:			Wang ying                                           
** Created Date:		2010-12-16                                            
**--------------------------------------------------------------------------------------------------------
** Modified by:			                                            
** Modified date:			                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 RTL8306EPHYReadBit( uint32 PHY_ID, uint32 register_address, uint32 bit_position, uint32 *value )
{
	uint16 ReadValue = 0;
	if( PHY_ID > 31 || bit_position >15 || value == NULL){
		return FALSE;
	}		
	SMIReadByte( PHY_ID, register_address, &ReadValue );
	*value = (ReadValue >> bit_position) & 1;
	return TRUE;
}

