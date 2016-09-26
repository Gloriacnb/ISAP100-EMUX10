/****************************************Copyright (c)****************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info---------------------------------------------------------------------------------
** Created by:          Wang ying
** Created date:        2010-12-17
** Version:             V1.0
** Descriptions:        RTL8306E Asic driver function
**                      
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:				
** Descriptions:        
** Rechecked by:        
*********************************************************************************************************/
#include <rtl8306e_asicdrv.h>
#include "Mid_SMI.h"
#ifndef RTK_X86_ASICDRV
#endif

#ifdef RTL8306_LUT_CACHE
RTL8306_LUT rtl8306_LutCache[RTL8306_MAX_LUT_NUM];
#endif

#ifdef RTL8306_TBLBAK        
rtl8306_ConfigBakPara_t rtl8306_TblBak; 
#endif 




uint32 rtk_getAsicOUIID (uint8 Phy, uint16 *oui )
{
	uint16 regData = 0;
	if(oui == NULL || Phy > 6) 
	{
		return FALSE;		  	//输入参数错误，则返回FAILED
	}
	RTL8306EPHYRead( Phy, 2, &regData );	   //读取OUI ID值  
	*oui = regData;		
	return TRUE;
}



/*********************************************************************************************************
** Function name:   	RTL8306E_setPowerDown
** Descriptions:        设置使能掉电模式
** input parameters:    phyad       PHY ID
                        enabled     使能
** output parameters:   无
** Returned value:      成功或失败                                
** Created by:			Wang ying                                           
** Created Date:		2010-08-12                                            
**--------------------------------------------------------------------------------------------------------
** Modified by:			                                            
** Modified date:			                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 RTL8306E_setPowerDown(uint32 phyad, uint32 enabled)
{
	if(phyad > RTL8306E_PHY_MAXNumber )
	{
		return FALSE;				//输入参数越界，则返回FAILED
	}

	RTL8306EPHYWriteBit( phyad, 0, 11, enabled);	 //是否使能掉电模式
	
	return TRUE;
}

/*********************************************************************************************************
** Function name:   	RTL8306E_getPowerDown
** Descriptions:        读取掉电模式设置
** input parameters:    phyad       PHY ID                        
** output parameters:   enabled     使能
** Returned value:      成功或失败                                
** Created by:			Wang ying                                           
** Created Date:		2010-08-12                                            
**--------------------------------------------------------------------------------------------------------
** Modified by:			                                            
** Modified date:			                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 RTL8306E_getPowerDown(uint32 phyad, uint32 *enabled)
{
	uint32 BitValue = 0;
	if((phyad > RTL8306E_PHY_MAXNumber) || (enabled == NULL) )
	{
		return FALSE;		   	//输入参数越界，则返回FAILED
	}			
	RTL8306EPHYReadBit( phyad, 0, 11, &BitValue);	  //读取寄存器中掉电设置值	
	*enabled = ((BitValue != 0) ? TRUE : FALSE);   //给输出值赋值，表示是否使能掉电模式		
	return TRUE;
}










/*********************************************************************************************************
** Function name:   	rtl8306e_reg_set
** Descriptions:         Write Asic Register
** input parameters:    phyad   Specify Phy address (0 ~6)
       					regad   Specify register address (0 ~31)
       					npage   Specify page number (0 ~3)
       					value   Value to be write into the register
** output parameters:   NONE
** Returned value:      成功或失败  
** Note:                利用本程序可对所有的RTL8306E的寄存器进行写操作                              
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_reg_set(uint32 phyad, uint32 regad, uint32 npage, uint32 value) 
{
    uint16 rdata = 0; 
    if ((phyad >= RTL8306_PHY_NUMBER) || (npage >= RTL8306_PAGE_NUMBER)){
        return FALSE;
	}    
    /* Select PHY Register Page through configuring PHY 0 Register 16 [bit1 bit15] */
    value = value & 0xFFFF;
    RTL8306EPHYRead(0, 16, &rdata); 
    switch (npage) 
    {
        case RTL8306_REGPAGE0:
            RTL8306EPHYWrite(0, 16, (rdata & 0x7FFF) | 0x0002);
            break;
        case RTL8306_REGPAGE1:
            RTL8306EPHYWrite(0, 16, rdata | 0x8002 );
            break;
        case RTL8306_REGPAGE2:
            RTL8306EPHYWrite(0, 16, rdata & 0x7FFD);
            break;
        case RTL8306_REGPAGE3:
            RTL8306EPHYWrite(0, 16, (rdata & 0xFFFD) | 0x8000);
            break;
        case RTL8306_REGPAGE4:
            RTL8306EPHYRead(5, 16, &rdata);
            rdata |= 0x2;
            RTL8306EPHYWrite(5, 16, rdata);
            break;                        
        default:
            return FALSE;
    }
    RTL8306EPHYWrite(phyad, regad, value);
    if(RTL8306_REGPAGE4 == npage)
    {
        /*exit page 4*/
        RTL8306EPHYRead(5, 16, &rdata);
        rdata &= ~0x2;
        RTL8306EPHYWrite(5, 16, rdata);
    }    
    return TRUE;
}
/*********************************************************************************************************
** Function name:   	rtl8306e_reg_get
** Descriptions:         Read Asic Register
** input parameters:     phyad   Specify Phy address (0 ~6)
       					 regad   Specify register address (0 ~31)
       					 npage   Specify page number (0 ~3)
** output parameters:    pvalue  The pointer of value read back from register
** Returned value:      成功或失败  
** Note:                利用本程序可对所有的RTL8306E的寄存器进行读操作                              
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_reg_get(uint32 phyad, uint32 regad, uint32 npage, uint16 *pvalue)
{
    uint16 rdata = 0;
    if ((phyad >= RTL8306_PHY_NUMBER) || (npage >= RTL8306_PAGE_NUMBER)){
        return FALSE;
	}
    /* Select PHY Register Page through configuring PHY 0 Register 16 [bit1 bit15] */
    RTL8306EPHYRead(0, 16, &rdata); 
    switch (npage) 
    {
        case RTL8306_REGPAGE0:
            RTL8306EPHYWrite(0, 16, (rdata & 0x7FFF) | 0x0002);
            break;
        case RTL8306_REGPAGE1:
            RTL8306EPHYWrite(0, 16, rdata | 0x8002 );
            break;
        case RTL8306_REGPAGE2:
            RTL8306EPHYWrite(0, 16, rdata & 0x7FFD);
            break;
        case RTL8306_REGPAGE3:
            RTL8306EPHYWrite(0, 16, (rdata & 0xFFFD) | 0x8000);
            break;
        case RTL8306_REGPAGE4:
            RTL8306EPHYRead(5, 16, &rdata);
            rdata |= 0x2;
            RTL8306EPHYWrite(5, 16, rdata);
            break;
        default:
            return FALSE;
    }
    RTL8306EPHYRead(phyad, regad, pvalue);
    *pvalue = *pvalue & 0xFFFF;
    if(RTL8306_REGPAGE4 == npage)
    {
        /*exit page 4*/
        RTL8306EPHYRead(5, 16, &rdata);
        rdata &= ~0x2;
        RTL8306EPHYWrite(5, 16, rdata);
    }        
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_regbit_set
** Descriptions:         Write one bit of Asic Register
** input parameters:     phyad    Specify Phy address (0 ~6)
       					 regad    Specify register address (0 ~31)
       					 bit      Specify bit position(0 ~ 15)
      					 npage    Specify page number (0 ~3)
       					 value    Value to be write(0, 1)
** output parameters:    none
** Returned value:       成功或失败  
** Note:                 利用本程序可对所有的RTL8306E的寄存器进行位写操作                              
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_regbit_set(uint32 phyad, uint32 regad, uint32 bit, uint32 npage,  uint32 value) 
{
    uint16 rdata;    
    if ((phyad >= RTL8306_PHY_NUMBER) || (npage >= RTL8306_PAGE_NUMBER) ||(bit > 15) || (value > 1)){
        return FALSE;
    }
    rtl8306e_reg_get(phyad, regad,  npage, &rdata);
    if(value != 0){ 
        rtl8306e_reg_set(phyad, regad, npage, rdata | (1 << bit));
	}
    else{
        rtl8306e_reg_set(phyad, regad, npage, rdata & (~(1 << bit)));
	}
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_regbit_get
** Descriptions:         Read one bit of Asic PHY Register
** input parameters:     phyad    Specify Phy address (0 ~6)
       					 regad    Specify register address (0 ~31)
       					 bit      Specify bit position(0 ~ 15)
      					 npage    Specify page number (0 ~3)
** output parameters:    pvalue  - The pointer of value read back
** Returned value:       成功或失败  
** Note:                 利用本程序可对所有的RTL8306E的寄存器进行位读操作                              
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_regbit_get(uint32 phyad, uint32 regad, uint32 bit, uint32 npage,  uint32 * pvalue) 
{
    uint16 rdata = 0;
    if ((phyad >= RTL8306_PHY_NUMBER) || (npage >= RTL8306_PAGE_NUMBER) || (bit > 15) || (pvalue == NULL)){
        return FALSE;
    }
    rtl8306e_reg_get(phyad, regad, npage, &rdata);
    if(rdata & (1 << bit)){
        *pvalue =1;
	}
    else{ 
        *pvalue =0;
	}
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_phyReg_set
** Descriptions:         Write PCS page register
** input parameters:     phyad   - Specify Phy address (0 ~6)
       					 regad    - Specify register address (0 ~31)
       					 npage   - Specify page number (0 ~5)
       					 value    - Value to be write into the register
** output parameters:    none
** Returned value:       成功或失败  
** Note:                 利用本程序可对所有的RTL8306E可配置的进程控制系统（PCS）寄存器进行写操作  
						 用于操作MMD的PCS寄存器                            
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_phyReg_set(uint32 phyad, uint32 regad, uint32 npage, uint32 value) 
{
    uint16 rdata = 0;
    uint16 regval = 0; 

    if ((phyad >= RTL8306_PHY_NUMBER) || (npage > 0x5)){
        return FALSE;
	}   
    RTL8306EPHYRead(5, 16, &rdata);   /*read/write pcs register*/
    RTL8306EPHYWrite(5, 16, rdata|0x0001);
    
    RTL8306EPHYRead(phyad, 31, &regval); /*Select PHY Register Page*/
    regval &= ~0xFF;
    regval |= npage;
    RTL8306EPHYWrite(phyad, 31, regval);
    RTL8306EPHYWrite(phyad, regad, value);
    RTL8306EPHYWrite(5, 16, rdata & (~0x0001));
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_phyReg_get
** Descriptions:         Read PCS page register
** input parameters:     phyad    Specify Phy address (0 ~6)
       					 regad    Specify register address (0 ~31)
       					 npage    Specify page number (0 ~5)
** output parameters:    pvalue    - The pointer of value read back from register
** Returned value:       成功或失败  
** Note:                 利用本程序可对所有的RTL8306E可配置的进程控制系统（PCS）寄存器进行读操作 
						 用于操作MMD的PCS寄存器                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_phyReg_get(uint32 phyad, uint32 regad, uint32 npage, uint16 *pvalue)
{
    uint16 rdata = 0;
    uint16 regval = 0; 

    if ((phyad >= RTL8306_PHY_NUMBER) || (npage > 0x5)){
        return FALSE;
	}   
    RTL8306EPHYRead(5, 16, &rdata);		  /*read/write pcs register*/
    RTL8306EPHYWrite(5, 16, rdata|0x0001);
    
    RTL8306EPHYRead(phyad, 31, &regval);/*Select PHY Register Page*/
    regval &= ~0xFF;
    regval |= npage;
    RTL8306EPHYWrite(phyad, 31, regval);
    RTL8306EPHYRead(phyad, regad, pvalue);

    *pvalue = *pvalue & 0xFFFF;
    RTL8306EPHYWrite(5, 16, rdata & (~0x0001));
    return TRUE;
}


/*********************************************************************************************************
** Function name:   	 rtl8306e_asic_init
** Descriptions:         对RTL8306E 的ASIC驱动初始化
** input parameters:     none
** output parameters:    none
** Returned value:       成功或失败                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:
**********************************************************************************************************/
uint32 rtl8306e_asic_init(void)
{
    uint16 regval;
    uint16 regval2;
    uint16 regval3;
    uint32 phy;

    /*by default: enable xor lut hash algorithm*/
    rtl8306e_regbit_set(1, 23, 12, 0, 1);

#ifdef   RTL8306_TBLBAK
    uint32 cnt;
    /*Vlan default value*/
    rtl8306_TblBak.vlanConfig.enVlan = FALSE;
    rtl8306_TblBak.vlanConfig.enArpVlan = FALSE;
    rtl8306_TblBak.vlanConfig.enLeakVlan = FALSE;
    rtl8306_TblBak.vlanConfig.enVlanTagOnly = FALSE;
    rtl8306_TblBak.vlanConfig.enIngress =  FALSE;
    rtl8306_TblBak.vlanConfig.enTagAware = FALSE;
    rtl8306_TblBak.vlanConfig.enIPMleaky = FALSE;
    rtl8306_TblBak.vlanConfig.enMirLeaky = FALSE;
    for (cnt = 0; cnt < 6; cnt++) 
    {
        rtl8306_TblBak.vlanConfig_perport[cnt].vlantagInserRm = RTL8306_VLAN_UNDOTAG;
        rtl8306_TblBak.vlanConfig_perport[cnt].en1PRemark = FALSE;
        rtl8306_TblBak.vlanConfig_perport[cnt].enNulPvidRep =  FALSE;
    }
    for (cnt = 0; cnt < 16; cnt++) 
    {
        rtl8306_TblBak.vlanTable[cnt].vid = cnt;
        if ((cnt % 5) == 4 )
        {            
            rtl8306_TblBak.vlanTable[cnt].memberPortMask = 0x1F;                
        } 
        else  
        {
            rtl8306_TblBak.vlanTable[cnt].memberPortMask = (0x1 << 4) | (0x1 << (cnt % 5));
        }
    }
    for (cnt = 0; cnt < 6; cnt++) 
    {
        rtl8306_TblBak.vlanPvidIdx[cnt] = (uint8)cnt;
        rtl8306_TblBak.dot1DportCtl[cnt] = RTL8306_SPAN_FORWARD;
    }
    rtl8306_TblBak.En1PremarkPortMask = 0;
    rtl8306_TblBak.dot1PremarkCtl[0] = 0x3;
    rtl8306_TblBak.dot1PremarkCtl[1] = 0x4;
    rtl8306_TblBak.dot1PremarkCtl[2] = 0x5;
    rtl8306_TblBak.dot1PremarkCtl[3] = 0x6;

    for (cnt = 0; cnt < RTL8306_ACL_ENTRYNUM; cnt++)
    {
        rtl8306_TblBak.aclTbl[cnt].phy_port = RTL8306_ACL_INVALID;
        rtl8306_TblBak.aclTbl[cnt].proto = RTL8306_ACL_ETHER;
        rtl8306_TblBak.aclTbl[cnt].data = 0;
        rtl8306_TblBak.aclTbl[cnt].action = RTL8306_ACT_PERMIT;
        rtl8306_TblBak.aclTbl[cnt].pri = RTL8306_PRIO0;            
    }
    rtl8306_TblBak.mir.mirPort = 0x7;
    rtl8306_TblBak.mir.mirRxPortMask = 0;
    rtl8306_TblBak.mir.mirTxPortMask = 0;
    rtl8306_TblBak.mir.enMirself = FALSE;
    rtl8306_TblBak.mir.enMirMac = FALSE;
    rtl8306_TblBak.mir.mir_mac[0] = 0x0;
    rtl8306_TblBak.mir.mir_mac[1] = 0x0;
    rtl8306_TblBak.mir.mir_mac[2] = 0x0;
    rtl8306_TblBak.mir.mir_mac[3] = 0x0;
    rtl8306_TblBak.mir.mir_mac[4] = 0x0;
    rtl8306_TblBak.mir.mir_mac[5] = 0x0;
#endif

#ifdef RTL8306_LUT_CACHE
    memset(rtl8306_LutCache, 0, sizeof(rtl8306_LutCache));
#endif

    rtl8306e_regbit_set(0, 16, 11, 0, 1);
    rtl8306e_regbit_set(4, 23, 5, 0, 1); 
    rtl8306e_reg_get(4, 30, 0, &regval);
    rtl8306e_reg_get(4, 26, 0, &regval2);
    rtl8306e_regbit_set(0, 16, 11, 0, 0);
    rtl8306e_regbit_set(4, 23, 5, 0, 0); 
    if (0x6167 == regval)
    {
        if ((((regval2 & (0x7<<13)) >> 13) == 1) || (((regval2 & (0x7<<13)) >> 13) == 2))
        {
            for (phy = 0; phy <= 4; phy++)
            {
                rtl8306e_phyReg_get(phy, 22, 0, &regval3);
                regval3 &= ~(0x1 << 14);
                rtl8306e_phyReg_set(phy, 22, 0, regval3);
            }
        }
        if (((regval2 & (0x7<<13)) >> 13) == 1)
        {
            rtl8306e_regbit_set(0, 19, 2, 0, 0);
            rtl8306e_regbit_set(4, 23, 8, 0, 1);
            rtl8306e_reg_get(0, 31, 3, &regval3);
            regval3 &= ~0x3;
            regval3 |= 0x2;
            rtl8306e_reg_set(0, 31, 3, regval3);
            rtl8306e_reg_get(1, 31, 3, &regval3);
            regval3 &= ~0x3;
            regval3 |= 0x2;
            rtl8306e_reg_set(1, 31, 3, regval3);
            rtl8306e_reg_get(2, 31, 3, &regval3);
            regval3 &= ~0x3;
            regval3 |= 0x2;
            rtl8306e_reg_set(2, 31, 3, regval3);
            rtl8306e_reg_get(3, 31, 3, &regval3);
            regval3 &= ~0x3;
            regval3 |= 0x2;
            rtl8306e_reg_set(3, 31, 3, regval3);
            rtl8306e_reg_get(5, 31, 3, &regval3);
            regval3 &= ~0x3;
            regval3 |= 0x2;
            rtl8306e_reg_set(5, 31, 3, regval3);
            rtl8306e_regbit_set(4, 23, 8, 0, 0);

            rtl8306e_phyReg_get(0, 25, 4, &regval3);
            regval3 &= ~(0x7 << 4);
            regval3 |= (0x6 << 4);
            rtl8306e_phyReg_set(0, 25, 4, regval3);

            rtl8306e_phyReg_get(0, 28, 4, &regval3);
            regval3 &= ~(0x1 << 8);
            regval3 |= (0x1 << 8);
            rtl8306e_phyReg_set(0, 28, 4, regval3);

            rtl8306e_phyReg_set(0, 29, 4, 0x5000);
            rtl8306e_phyReg_set(0, 29, 4, 0x6000);
            rtl8306e_phyReg_set(0, 29, 4, 0x7000);
            rtl8306e_phyReg_set(0, 29, 4, 0x4000);
            rtl8306e_phyReg_set(0, 29, 4, 0x8700);
            rtl8306e_phyReg_set(0, 29, 4, 0xD36C);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFFF);
            rtl8306e_phyReg_set(0, 29, 4, 0xCA6C);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFFD);
            rtl8306e_phyReg_set(0, 29, 4, 0x5060);
            rtl8306e_phyReg_set(0, 29, 4, 0x61C5);
            rtl8306e_phyReg_set(0, 29, 4, 0x7010);
            rtl8306e_phyReg_set(0, 29, 4, 0x4001);
            rtl8306e_phyReg_set(0, 29, 4, 0x5061);
            rtl8306e_phyReg_set(0, 29, 4, 0x4001);
            rtl8306e_phyReg_set(0, 29, 4, 0x87F1);
            rtl8306e_phyReg_set(0, 29, 4, 0xCE60);
            rtl8306e_phyReg_set(0, 29, 4, 0x0026);
            rtl8306e_phyReg_set(0, 29, 4, 0x8E03);
            rtl8306e_phyReg_set(0, 29, 4, 0xA021);
            rtl8306e_phyReg_set(0, 29, 4, 0x300F);
            rtl8306e_phyReg_set(0, 29, 4, 0x58A0);
            rtl8306e_phyReg_set(0, 29, 4, 0x629C);
            rtl8306e_phyReg_set(0, 29, 4, 0x7010);
            rtl8306e_phyReg_set(0, 29, 4, 0x4002);
            rtl8306e_phyReg_set(0, 29, 4, 0x58A1);
            rtl8306e_phyReg_set(0, 29, 4, 0x87E6);
            rtl8306e_phyReg_set(0, 29, 4, 0xAE25);
            rtl8306e_phyReg_set(0, 29, 4, 0xA018);
            rtl8306e_phyReg_set(0, 29, 4, 0x301A);
            rtl8306e_phyReg_set(0, 29, 4, 0x6E94);
            rtl8306e_phyReg_set(0, 29, 4, 0x6694);
            rtl8306e_phyReg_set(0, 29, 4, 0x5123);
            rtl8306e_phyReg_set(0, 29, 4, 0x63C2);
            rtl8306e_phyReg_set(0, 29, 4, 0x5127);
            rtl8306e_phyReg_set(0, 29, 4, 0x4003);
            rtl8306e_phyReg_set(0, 29, 4, 0x87DC);
            rtl8306e_phyReg_set(0, 29, 4, 0x8EF3);
            rtl8306e_phyReg_set(0, 29, 4, 0xA10E);
            rtl8306e_phyReg_set(0, 29, 4, 0xCC40);
            rtl8306e_phyReg_set(0, 29, 4, 0x0007);
            rtl8306e_phyReg_set(0, 29, 4, 0xCA40);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFDF);
            rtl8306e_phyReg_set(0, 29, 4, 0xA202);
            rtl8306e_phyReg_set(0, 29, 4, 0x3024);
            rtl8306e_phyReg_set(0, 29, 4, 0x7018);
            rtl8306e_phyReg_set(0, 29, 4, 0x3024);
            rtl8306e_phyReg_set(0, 29, 4, 0xCC44);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFF4);
            rtl8306e_phyReg_set(0, 29, 4, 0xCC44);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFF2);
            rtl8306e_phyReg_set(0, 29, 4, 0x3000);
            rtl8306e_phyReg_set(0, 29, 4, 0x5220);
            rtl8306e_phyReg_set(0, 29, 4, 0x4004);
            rtl8306e_phyReg_set(0, 29, 4, 0x3000);
            rtl8306e_phyReg_set(0, 29, 4, 0x64A0);
            rtl8306e_phyReg_set(0, 29, 4, 0x5429);
            rtl8306e_phyReg_set(0, 29, 4, 0x4005);
            rtl8306e_phyReg_set(0, 29, 4, 0x87C6);
            rtl8306e_phyReg_set(0, 29, 4, 0xCE18);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFC4);
            rtl8306e_phyReg_set(0, 29, 4, 0xCE64);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFCF);
            rtl8306e_phyReg_set(0, 29, 4, 0x303A);
            rtl8306e_phyReg_set(0, 29, 4, 0x65C0);
            rtl8306e_phyReg_set(0, 29, 4, 0x50A9);
            rtl8306e_phyReg_set(0, 29, 4, 0x4006);
            rtl8306e_phyReg_set(0, 29, 4, 0xA3DB);
            rtl8306e_phyReg_set(0, 29, 4, 0x3043);
            rtl8306e_phyReg_set(0, 29, 4, 0x5000);
            rtl8306e_phyReg_set(0, 29, 4, 0x60F3);
            rtl8306e_phyReg_set(0, 29, 4, 0x5008);
            rtl8306e_phyReg_set(0, 29, 4, 0x7010);
            rtl8306e_phyReg_set(0, 29, 4, 0x4000);
            rtl8306e_phyReg_set(0, 29, 4, 0x87B6);
            rtl8306e_phyReg_set(0, 29, 4, 0xA3B5);
            rtl8306e_phyReg_set(0, 29, 4, 0xD36C);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFFD);
            rtl8306e_phyReg_set(0, 29, 4, 0xCA68);
            rtl8306e_phyReg_set(0, 29, 4, 0xFFBA);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);
            rtl8306e_phyReg_set(0, 29, 4, 0x0000);

            rtl8306e_phyReg_get(0, 28, 4, &regval3);
            regval3 &= ~(0x1 << 8);
            rtl8306e_phyReg_set(0, 28, 4, regval3);

            rtl8306e_phyReg_get(0, 25, 4, &regval3);
            regval3 &= ~(0x7 << 4);
            regval3 |= (0x3 << 4);
            rtl8306e_phyReg_set(0, 25, 4, regval3);

            for (phy = 0; phy <= 4; phy++)
            {
                rtl8306e_phyReg_get(phy, 24, 4, &regval3);
                regval3 &= ~(0xFF);
                regval3 |= 0xF3;
                rtl8306e_phyReg_set(phy, 24, 4, regval3);
            }

            /*RTCT*/
            for (phy = 0; phy <= 4; phy++)
            {
                rtl8306e_phyReg_get(phy, 16, 2, &regval3);
                regval3 &= ~(0x3FF);
                regval3 |= 0xFA;
                rtl8306e_phyReg_set(phy, 16, 2, regval3);
                rtl8306e_phyReg_get(phy, 22, 2, &regval3);
                regval3 &= ~(0x7FF);
                regval3 |= 0x12C;
                rtl8306e_phyReg_set(phy, 22, 2, regval3);
                rtl8306e_phyReg_get(phy, 23, 2, &regval3);
                regval3 &= ~(0x3FF);
                regval3 |= 0xC8;
                rtl8306e_phyReg_set(phy, 23, 2, regval3);
                rtl8306e_phyReg_get(phy, 24, 2, &regval3);
                regval3 &= ~(0x1FF);
                regval3 |= 0x32;
                rtl8306e_phyReg_set(phy, 24, 2, regval3);
                rtl8306e_phyReg_get(phy, 19, 2, &regval3);
                regval3 &= ~(0xF << 12);
                regval3 |= (0x4 << 12);
                rtl8306e_phyReg_set(phy, 19, 2, regval3);
                rtl8306e_phyReg_get(phy, 18, 2, &regval3);
                regval3 &= ~(0x1F << 10);
                regval3 |= (0x5 << 10);
                rtl8306e_phyReg_set(phy, 18, 2, regval3);
                rtl8306e_phyReg_get(phy, 25, 2, &regval3);
                regval3 &= ~(0xFF << 8);
                regval3 |= (0x4 << 8);
                rtl8306e_phyReg_set(phy, 25, 2, regval3);
                rtl8306e_phyReg_get(phy, 25, 2, &regval3);
                regval3 &= ~0xFF;
                regval3 |= 0x40;
                rtl8306e_phyReg_set(phy, 25, 2, regval3);

            }
        }    
    }
	for(phy= 0; phy<6; phy++){
		rtl8306e_regbit_set(phy, 16, 2, 0, 0);
	}
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_phy_reset
** Descriptions:         PHY复位
** input parameters:     phy    Specify Phy address (0 ~4)
** output parameters:    none
** Returned value:       成功或失败                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_phy_reset(uint32 phy)
{
    uint16 regval, regval2, dupSpd;
    uint32 nway, pause; 
    if (phy > 4){
        return FALSE;
    }

    rtl8306e_regbit_set(0, 16, 11, 0, 1);
    rtl8306e_regbit_set(4, 23, 5, 0, 1); 
    rtl8306e_reg_get(4, 30, 0, &regval);
    rtl8306e_reg_get(4, 26, 0, &regval2);
    rtl8306e_regbit_set(0, 16, 11, 0, 0);
    rtl8306e_regbit_set(4, 23, 5, 0, 0); 
    if ((0x6167 == regval) && ((regval2 & (0x7<<13)) >> 13 == 1))
    {
        rtl8306e_regbit_get(phy, 22, 6, 0, &nway);
        rtl8306e_regbit_get(phy, 22, 3, 0, &pause);
        rtl8306e_reg_get(phy, 22, 0, &dupSpd);         
        rtl8306e_regbit_set(phy, 0, 15, 0, 1);
        if (nway)
        {
            switch((dupSpd & (0x3 << 4)) >> 4)
            {
                case 0x3:
                    rtl8306e_regbit_set(phy, 0, 8, 0, 1);
                    rtl8306e_regbit_set(phy, 0, 13, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 8, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 7, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 6, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 5, 0, 1);
                    break;
                case 0x2:
                    rtl8306e_regbit_set(phy, 0, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 0, 13, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 7, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 6, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 5, 0, 1);
                    break;
                case 0x1:
                    rtl8306e_regbit_set(phy, 0, 8, 0, 1);
                    rtl8306e_regbit_set(phy, 0, 13, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 7, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 6, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 5, 0, 1);
                    break;
                case 0x0:
                    rtl8306e_regbit_set(phy, 0, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 0, 13, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 7, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 6, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 5, 0, 1);
                    break;
                default:
                   break;
            } 
            rtl8306e_regbit_set(phy, 0, 12, 0, 1);
            rtl8306e_regbit_set(phy, 0, 9, 0, 1);
        }
        else
        {
            rtl8306e_regbit_set(phy, 0, 12, 0, 0);
            switch((dupSpd & (0x3 << 4)) >> 4)
            {
                case 0x3:
                    rtl8306e_regbit_set(phy, 0, 8, 0, 1);
                    rtl8306e_regbit_set(phy, 0, 13, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 8, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 7, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 6, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 5, 0, 0);
                    break;
                case 0x2:
                    rtl8306e_regbit_set(phy, 0, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 0, 13, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 7, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 6, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 5, 0, 0);
                    break;
                case 0x1:
                    rtl8306e_regbit_set(phy, 0, 8, 0, 1);
                    rtl8306e_regbit_set(phy, 0, 13, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 7, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 6, 0, 1);
                    rtl8306e_regbit_set(phy, 4, 5, 0, 0);
                    break;
                case 0x0:
                    rtl8306e_regbit_set(phy, 0, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 0, 13, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 8, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 7, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 6, 0, 0);
                    rtl8306e_regbit_set(phy, 4, 5, 0, 1);
                    break;
                default:
                   break;
            }  
        }       
        rtl8306e_regbit_set(phy, 4, 10, 0, pause);       
    }
    else {
        rtl8306e_regbit_set(phy, 0, 15, 0, 1);
	}
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_switch_maxPktLen_set
** Descriptions:         set Max packet length which could be forwarded by
** input parameters:     maxLen        max packet length
** output parameters:    none
** Returned value:       成功或失败  
** Note:                 最大包长有4种选择：1526，1536，1552，2000                           
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_switch_maxPktLen_set(uint32 maxLen)
{
    switch(maxLen)
    {
        case RTL8306_MAX_PKT_LEN_1518:
            rtl8306e_regbit_set(2, 23, 1, 3, 1);
            rtl8306e_regbit_set(0, 29, 15, 3, 0);
            break;

        case RTL8306_MAX_PKT_LEN_1536:
            rtl8306e_regbit_set(2, 23, 1, 3, 0);
            rtl8306e_regbit_set(0, 18, 14, 0, 1);
            rtl8306e_regbit_set(0, 29, 15, 3, 0);            
            break;

        case RTL8306_MAX_PKT_LEN_1552:
            rtl8306e_regbit_set(2, 23, 1, 3, 0);
            rtl8306e_regbit_set(0, 18, 14, 0, 0);
            rtl8306e_regbit_set(0, 29, 15, 3, 0);            
            break;

        case RTL8306_MAX_PKT_LEN_2000:
            rtl8306e_regbit_set(0, 29, 15, 3, 1);
            break;
            
        default:
            return FALSE;
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_switch_maxPktLen_get
** Descriptions:         get Max packet length which could be forwarded by
** input parameters:     none
** output parameters:    maxLen        max packet length
** Returned value:       成功或失败  
** Note:                 最大包长有4种选择：1526，1536，1552，2000                           
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_switch_maxPktLen_get(uint32 *pMaxLen)
{
    uint32 regval;
    if (pMaxLen == NULL){
        return FALSE;
    }
    rtl8306e_regbit_get(0, 29, 15, 3, &regval);
    if(regval)
    {
        *pMaxLen = RTL8306_MAX_PKT_LEN_2000;
    }
    else
    {
        rtl8306e_regbit_get(2, 23, 1, 3, &regval);
        if (regval)
        {
            *pMaxLen = RTL8306_MAX_PKT_LEN_1518;
        }
        else 
        {
            rtl8306e_regbit_get(0, 18, 14, 0, &regval);
            if (regval)
            {
                *pMaxLen = RTL8306_MAX_PKT_LEN_1536;            
            }
            else
            {
                *pMaxLen = RTL8306_MAX_PKT_LEN_1552;                        
            }
        }
    }   
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_etherPhy_set
** Descriptions:         配置PHY寄存器
** input parameters:     phy                 Specify the phy to configure
       					 autoNegotiation     Specify whether enable auto-negotiation
       					 advCapability       When auto-negotiation is enabled, specify the advertised capability
       					 speed               When auto-negotiation is disabled, specify the force mode speed
       					 fullDuplex          When auto-negotiatoin is disabled, specify the force mode duplex mode
** output parameters:    none
** Returned value:       成功或失败  
** Note:      			 When auto-negotiation is enabled, the advertisement capability is used to handshaking with link partner.
			      		 When auto-negotiation is disabled, the phy is configured into force mode and the speed and duplex mode 
			       		 setting is based on speed and fullDuplex setting.Port number should be smaller than RTL8306_PHY_NUMBER.
			       		 AdverCapability should be ranged between RTL8306_ETHER_AUTO_100FULL and RTL8306_ETHER_AUTO_10HALF.
			       		 Speed should be either RTL8306_ETHER_SPEED_100 or RTL8306_ETHER_SPEED_10.                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_etherPhy_set(uint32 phy, uint32 autoNegotiation, uint32 advCapability, uint32 speed, uint32 fullDuplex) 
{
    uint32 ctrlReg = 0;
    if(phy >= RTL8306_PHY_NUMBER || advCapability < RTL8306_ETHER_AUTO_100FULL ||
       advCapability > RTL8306_ETHER_AUTO_10HALF ||(speed != 100 && speed != 10)){
           return FALSE;
	}
    if(RTL8306_ETHER_AUTO_100FULL == advCapability){
        rtl8306e_reg_set(phy, 4, 0, RTL8306_CAPABLE_PAUSE | RTL8306_CAPABLE_100BASE_TX_FD 
                                  | RTL8306_CAPABLE_100BASE_TX_HD | RTL8306_CAPABLE_10BASE_TX_FD 
                                  | RTL8306_CAPABLE_10BASE_TX_HD | 0x1);
	}
    else if(RTL8306_ETHER_AUTO_100HALF == advCapability){
        rtl8306e_reg_set(phy, 4, 0, RTL8306_CAPABLE_PAUSE | RTL8306_CAPABLE_100BASE_TX_HD
                                  | RTL8306_CAPABLE_10BASE_TX_FD | RTL8306_CAPABLE_10BASE_TX_HD | 0x1);
	}
    else if( RTL8306_ETHER_AUTO_10FULL == advCapability){
        rtl8306e_reg_set(phy, 4, 0, RTL8306_CAPABLE_PAUSE | RTL8306_CAPABLE_10BASE_TX_FD 
                                  | RTL8306_CAPABLE_10BASE_TX_HD | 0x1);
	}
    else if(RTL8306_ETHER_AUTO_10HALF == advCapability){
        rtl8306e_reg_set(phy, 4, 0, RTL8306_CAPABLE_PAUSE | RTL8306_CAPABLE_10BASE_TX_HD | 0x1);
	}
    /*Each time the link ability of the RTL8306 is reconfigured, 
     *the auto-negotiation process should be executed to allow
     *the configuration to take effect. 
     */
    if(TRUE == autoNegotiation){ 
        ctrlReg = RTL8306_ENABLE_AUTONEGO | RTL8306_RESTART_AUTONEGO; 
	}
    else{
        ctrlReg = 0;
	}
    if(100 == speed){ 
        ctrlReg |= RTL8306_SPEED_SELECT_100M;
	}
    if(TRUE == fullDuplex){
        ctrlReg |= RTL8306_SELECT_FULL_DUPLEX;
	}
    rtl8306e_reg_set(phy, 0, RTL8306_REGPAGE0, ctrlReg);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_etherPhy_get
** Descriptions:         PHY寄存器配置的读取
** input parameters:     phy                 Specify the phy to configure
** output parameters:    pAutoNegotiation    Get whether auto-negotiation is enabled
       					 pAdvCapability      When auto-negotiation is enabled, Get the advertised capability
       					 pSpeed              When auto-negotiation is disabled, Get the force mode speed
       					 pFullDuplex         When auto-negotiatoin is disabled, Get the force mode duplex mode
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-17 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_etherPhy_get(uint32 phy, uint32 *pAutoNegotiation, uint32 *pAdvCapability, uint32 *pSpeed, uint32 *pFullDuplex)
{
    uint16 regData;

    if((phy >= RTL8306_PHY_NUMBER) || (NULL == pAutoNegotiation) || (NULL == pAdvCapability)
        || (NULL ==  pSpeed) || (NULL == pFullDuplex))
        return FALSE;

    rtl8306e_reg_get(phy, 0, RTL8306_REGPAGE0, &regData);
    *pAutoNegotiation = (regData & RTL8306_ENABLE_AUTONEGO) ? TRUE: FALSE;
    *pSpeed = (regData & RTL8306_SPEED_SELECT_100M) ? 100: 10;
    *pFullDuplex = (regData & RTL8306_SELECT_FULL_DUPLEX) ? TRUE: FALSE;

    rtl8306e_reg_get(phy, 4, RTL8306_REGPAGE0, &regData);
    if(regData & RTL8306_CAPABLE_100BASE_TX_FD)
        *pAdvCapability = RTL8306_ETHER_AUTO_100FULL;
    else if(regData & RTL8306_CAPABLE_100BASE_TX_HD)
        *pAdvCapability = RTL8306_ETHER_AUTO_100HALF;
    else if(regData & RTL8306_CAPABLE_10BASE_TX_FD)
        *pAdvCapability = RTL8306_ETHER_AUTO_10FULL;
    else if(regData & RTL8306_CAPABLE_10BASE_TX_HD)
        *pAdvCapability = RTL8306_ETHER_AUTO_10HALF;
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_port5LinkStatus_set
** Descriptions:         设置PORT5的LINK状态
** input parameters:     enabled             使能LINK或禁能LINK
** output parameters:    none
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_port5LinkStatus_set(uint32 enabled) 
{
    uint32 duplex, speed, nway;
    
    rtl8306e_regbit_get(6, 0, 13, 0, &speed);  /*save phy 6 reg 0.13, 0.12, 0.8*/
    rtl8306e_regbit_get(6, 0, 12, 0, &nway);
    rtl8306e_regbit_get(6, 0, 8, 0, &duplex);
      
    rtl8306e_regbit_set(6, 22, 15, 0, enabled ? 1:0);
        
    rtl8306e_regbit_set(6, 0, 13, 0, speed);	/*restore phy 6 reg 0.13, 0.12, 0.8*/
    rtl8306e_regbit_set(6, 0, 12, 0, nway);
    rtl8306e_regbit_set(6, 0, 8, 0, duplex);

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_port5LinkStatus_get
** Descriptions:         读取PORT5的LINK状态
** input parameters:     none
** output parameters:    enabled             使能LINK或禁能LINK
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_port5LinkStatus_get(uint32 *pEnabled)
{
    uint32 bitValue;
    if (NULL == pEnabled){ 
        return FALSE;
    }
    rtl8306e_regbit_get(6, 22, 15, 0, &bitValue);
    *pEnabled = (bitValue ? TRUE : FALSE);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_phyLinkStatus_get
** Descriptions:         读取PHY端口的LINK状态（Read the link status of PHY register 1）
** input parameters:     phy         Specify the phy
** output parameters:    plinkUp     Describe whether link status is up or not
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_phyLinkStatus_get(uint32 phy, uint32 *plinkUp) 
{
    uint32 bitValue;
    if (NULL == plinkUp){
        return FALSE;
    }
    rtl8306e_regbit_get(phy, 1, 2, RTL8306_REGPAGE0, &bitValue);
    rtl8306e_regbit_get(phy, 1, 2, RTL8306_REGPAGE0, &bitValue);    
    *plinkUp = (bitValue ? TRUE: FALSE);

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_phyAutoNegotiationDone_get
** Descriptions:         读取自协商是否完成状态（Read the auto-negotiation complete status of PHY register 1）
** input parameters:     phy         Specify the phy
** output parameters:    pDone       Describe whether auto-negotiation is done or not
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_phyAutoNegotiationDone_get(uint32 phy, uint32 *pDone) 
{
    uint32 bitValue;

    if (NULL == pDone)
        return FALSE;
    
    rtl8306e_regbit_get(phy, 1, 5, 0, &bitValue);
    *pDone = (bitValue ? TRUE: FALSE);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_phyLoopback_set
** Descriptions:         设置PHY的环回模式是否使能（Only phy 0~4）
** input parameters:     phy         Specify the phy to configure
						 enabled     Enable phy loopback
** output parameters:    none
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_phyLoopback_set(uint32 phy, uint32 enabled) 
{
    if(phy > 4)
        return FALSE;
    rtl8306e_regbit_set(phy, 0, 14, 0, enabled ? 1 : 0);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_phyLoopback_get
** Descriptions:         读取PHY的环回模式是否使能（Only phy 0~4）
** input parameters:     phy         Specify the phy to get status
** output parameters:    pEnabled    phy loopback setting
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_phyLoopback_get(uint32 phy, uint32 *pEnabled) 
{
    uint32 bitValue;

    if (NULL == pEnabled)
        return FALSE;
    
    rtl8306e_regbit_get(phy, 0, 14, 0, &bitValue);
    *pEnabled = (bitValue ? TRUE: FALSE);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_portLearningAbility_set
** Descriptions:         设置端口的学习能力
** input parameters:     port        - Specify port number (0 ~ 5)
						 enabled -  TRUE or FALSE
** output parameters:    none
** Returned value:       成功                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_portLearningAbility_set(uint32 port, uint32 enabled)
{
    if (port > RTL8306_PORT5){
        return FALSE;
	}
    if (RTL8306_PORT5 == port){
        port++;
	}
    rtl8306e_regbit_set(port, 24, 9, 0, enabled ? 1 : 0);

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_isolation_set
** Descriptions:         设置端口隔离
** input parameters:     isomsk    - port isolation port mask
** output parameters:    none
** Returned value:       成功   
** Note:                 each bit of isomsk determine two port's isolation,
				         1 means two port could not forward packet between
				         each other.bit为1，则表示两端口间不能进行包传送。
				         bit 0  - Port0 & Port1 
				         bit 1  - Port0 & Port2 
				         bit 2  - Port0 & Port3
				         bit 3  - Port0 & Port4
				         bit 4  - Port0 & Port5
				         bit 5  - Port1 & Port2
				         bit 6  - Port1 & Port3
				         bit 7  - Port1 & Port4
				         bit 8  - Port1 & Port5
				         bit 9  - Port2 & Port3
				         bit 10 - Port2 & Port4
				         bit 11 - Port2 & Port5
				         bit 12 - Port3 & Port4
				         bit 13 - Port3 & Port5
				         bit 14 - Port4 & Port5                       
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_isolation_set(uint32 isomsk)
{
    uint16 regval;

    rtl8306e_reg_get(0, 29, 3, &regval);
    regval &= ~0x7FFF;
    regval |= isomsk & 0x7FFF;
	
    rtl8306e_reg_set(0, 29, 3, regval);
    
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_port_isolation_get
** Descriptions:         读端口隔离状态
** input parameters:     none
** output parameters:    pIsomsk      the pointer of port isolation port mask
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_port_isolation_get(uint32 *pIsomsk)
{
    uint16 regval;

    if (NULL == pIsomsk){
        return FALSE;
	}
    rtl8306e_reg_get(0, 29, 3, &regval);
    *pIsomsk = regval & 0x7FFF;

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_tagAware_set
** Descriptions:         配置VLAN TAG awared
** input parameters:     enabled  - Configure RTL8306 VLAN tag awared
** output parameters:    none
** Returned value:       成功或失败                          
** Created by:			                                          
** Created Date:		 If switch is unawared VLAN tag, packet with vlan tag is treated as untagged 
						 pkt  and assigned PVID as VID.                                          
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_tagAware_set(uint32 enabled) 
{
    rtl8306e_regbit_set(0, 16, 10, 0, enabled ? 0: 1);        
#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.vlanConfig.enTagAware = (uint8) enabled;
#endif
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_tagAware_get
** Descriptions:         读取VLAN TAG  awared
** input parameters:     pEnabled  - the pointer of RTL8306 VLAN tag awared status 
** output parameters:    none
** Returned value:       成功或失败 
** Note:				 If switch is unawared VLAN tag, packet with vlan tag is treated as untagged pkt
				         and assigned PVID as VID.                      
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_tagAware_get(uint32 * pEnabled) 
{
    uint32 bitValue;				   
    if (pEnabled == NULL){
        return FALSE;
    }
    rtl8306e_regbit_get(0, 16, 10, 0, &bitValue);
    *pEnabled = (bitValue ? FALSE: TRUE);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_IgrFilterEnable_set
** Descriptions:         配置VLAN入口过滤
** input parameters:     enabled     enable or disable 
** output parameters:    none
** Returned value:       成功或失败                     
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_IgrFilterEnable_set(uint32 enabled) 
{

    rtl8306e_regbit_set(0, 16, 9, 0, enabled ? 0 : 1);    
#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.vlanConfig.enIngress = (uint8) enabled;
#endif
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_IgrFilterEnable_get
** Descriptions:         读取VLAN入口过滤状态
** input parameters:     pEnabled     enable or disable
** output parameters:    none
** Returned value:       成功或失败                     
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_IgrFilterEnable_get(uint32 *pEnabled) 
{
    uint32 bitValue;
    if (NULL == pEnabled){
        return FALSE;
    }
    rtl8306e_regbit_get(0, 16, 9, 0, &bitValue);
    *pEnabled = (bitValue ? 0: 1);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_leaky_set
** Descriptions:         Configure switch to forward frames to other VLANs ignoring the egress rule
** input parameters:     type   -  vlan leaky type
						 enabled  - enable or disable
** output parameters:    none
** Returned value:       成功或失败   
** Note:				 type coulde be:
			             RTL8306_VALN_LEAKY_UNICAST - Vlan leaky for unicast pkt
			             RTL8306_VALN_LEAKY_MULTICAST - Vlan leaky for multicast pkt
			             RTL8306_VALN_LEAKY_ARP - Vlan leaky for ARP brodcast pkt 
			             RTL8306_VALN_LEAKY_MIRROR - Vlan leaky for mirror function
			
					     1.When the Vlan leaky for unicast pkt is enabled, it enables the inter-VLANs unicast packet forwarding. 
					     That is, if the L2 look up MAC table search hit, then the unicast packet will be forwarded
					     to the egress port ignoring the egress rule.
					     2.When Vlan leaky for multicast pkt is enabled, multicast packet may be flood to all multicast address
					     group member set, ignoring the VLAN member set domain limitation.
					     3.When Vlan leaky for ARP pkt is enabled, the ARP broadcast packets will be forward to all the other
					     ports ignoring the egress rule.
					     4.When Vlan leaky for mirror function is enabled, it enables the inter-VLANs mirror function, 
					     ignoring the VLAN member set domain limitation.   
                      
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_leaky_set(uint32 type, uint32 enabled)
{
    switch(type) 
    {
        case RTL8306_VALN_LEAKY_UNICAST:
            rtl8306e_regbit_set(0, 18, 11, 0, enabled ? 0 : 1);
		#ifdef RTL8306_TBLBAK
            rtl8306_TblBak.vlanConfig.enLeakVlan = (uint8) enabled;
		#endif
            break;
        case RTL8306_VALN_LEAKY_MULTICAST:
            rtl8306e_regbit_set(2, 23, 7, 3, enabled ? 0 : 1);
		#ifdef RTL8306_TBLBAK
            rtl8306_TblBak.vlanConfig.enIPMleaky = (uint8) enabled;
		#endif
            break;
        case RTL8306_VALN_LEAKY_ARP:
            rtl8306e_regbit_set(0, 18, 10, 0, enabled ? 0 : 1);
		#ifdef RTL8306_TBLBAK
            rtl8306_TblBak.vlanConfig.enArpVlan = (uint8) enabled;
		#endif
            break;
        case RTL8306_VALN_LEAKY_MIRROR:
            rtl8306e_regbit_set(2, 23, 6, 3, enabled ? 0 : 1);
		#ifdef RTL8306_TBLBAK
            rtl8306_TblBak.vlanConfig.enMirLeaky = (uint8) enabled;
		#endif
            break;
        default:
            return FALSE;
    }    
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_leaky_get
** Descriptions:         Configure switch to forward frames to other VLANs ignoring the egress rule
** input parameters:     type          vlan leaky type
** output parameters:    pEnabled      the pointer of Vlan Leaky status(Dsiabled or Enabled) 
** Returned value:       成功或失败   
** Note:				 type coulde be:
			             RTL8306_VALN_LEAKY_UNICAST - Vlan leaky for unicast pkt
			             RTL8306_VALN_LEAKY_MULTICAST - Vlan leaky for multicast pkt
			             RTL8306_VALN_LEAKY_ARP - Vlan leaky for ARP brodcast pkt 
			             RTL8306_VALN_LEAKY_MIRROR - Vlan leaky for mirror function
			
					     1.When the Vlan leaky for unicast pkt is enabled, it enables the inter-VLANs unicast packet forwarding. 
					     That is, if the L2 look up MAC table search hit, then the unicast packet will be forwarded
					     to the egress port ignoring the egress rule.
					     2.When Vlan leaky for multicast pkt is enabled, multicast packet may be flood to all multicast address
					     group member set, ignoring the VLAN member set domain limitation.
					     3.When Vlan leaky for ARP pkt is enabled, the ARP broadcast packets will be forward to all the other
					     ports ignoring the egress rule.
					     4.When Vlan leaky for mirror function is enabled, it enables the inter-VLANs mirror function, 
					     ignoring the VLAN member set domain limitation.   
                      
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_leaky_get(uint32 type, uint32 *pEnabled)
{
    uint32 bitValue;
    if(NULL == pEnabled){
        return FALSE;
	}
    switch(type) 
    {
        case RTL8306_VALN_LEAKY_UNICAST:
            rtl8306e_regbit_get(0, 18, 11, 0, &bitValue);
            break;
        case RTL8306_VALN_LEAKY_MULTICAST:
            rtl8306e_regbit_get(2, 23, 7, 3, &bitValue);
            break;
        case RTL8306_VALN_LEAKY_ARP:
            rtl8306e_regbit_get(0, 18, 10, 0, &bitValue);
            break;
        case RTL8306_VALN_LEAKY_MIRROR:
            rtl8306e_regbit_get(2, 23, 6, 3, &bitValue);
            break;
        default:
            return FALSE;
    }
    *pEnabled = (bitValue ?  FALSE : TRUE);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_nullVidReplace_set
** Descriptions:         Configure switch to replace Null VID tagged frame by PVID if it is tag aware
** input parameters:     port   -  port number
                         enabled  - enable or disable
** output parameters:    none
** Returned value:       成功或失败 
** Note:				 1.When Null VID replacement is enabled, 8306E only captures tagged packet with VID=0,
					     then replace VID with input port's PVID. If switch received a packet that is not tagged, 
					     it will not insert a tag with PVID to this packet.
					     2. When Null VID replacement is disabled, switch will drop or deal the null VID tagged 
					     frame depends on the configuration.                        
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_nullVidReplace_set(uint32 port, uint32 enabled)
{
    uint32 speed, duplex, nway;
    if (port > RTL8306_PORT5){
        return FALSE;
    }
    speed = 0; 
    duplex = 0;
    nway = 0;      
    if (4 == port) 
    {				 /*save mac 4 or port status when operate reg.22*/ 
        rtl8306e_regbit_get(5, 0, 13, 0, &speed);
        rtl8306e_regbit_get(5, 0, 12, 0, &nway);
        rtl8306e_regbit_get(5, 0, 8, 0, &duplex);            
    } 
    else if (5 == port) 
    {
        rtl8306e_regbit_get(6, 0, 13, 0, &speed);
        rtl8306e_regbit_get(6, 0, 12, 0, &nway);
        rtl8306e_regbit_get(6, 0, 8, 0, &duplex);            
    }

    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ; 
    
    rtl8306e_regbit_set(port, 22, 12, 0, enabled ? 1 : 0);
    
    /*restore mac 4 or port status when operate reg.22*/    
    if (4 == port) 
    {
        rtl8306e_regbit_set(5, 0, 13, 0, speed);
        rtl8306e_regbit_set(5, 0, 12, 0, nway);
        rtl8306e_regbit_set(5, 0, 8, 0, duplex);            
    }
    else if (6 == port) 
    { 
        /*for port++ when port 5*/
        rtl8306e_regbit_set(6, 0, 13, 0, speed);
        rtl8306e_regbit_set(6, 0, 12, 0, nway);
        rtl8306e_regbit_set(6, 0, 8, 0, duplex);
    }           
    
#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.vlanConfig_perport[port].enNulPvidRep = (uint8) enabled;
#endif
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_nullVidReplace_get
** Descriptions:         read switch to replace Null VID tagged frame by PVID if it is tag aware
** input parameters:     port        port number
** output parameters:    pEnabled    the pointer of Null VID replacement ability(Dsiabled or Enabled)
** Returned value:       成功或失败 
** Note:				 1.When Null VID replacement is enabled, 8306E only captures tagged packet with VID=0,
					     then replace VID with input port's PVID. If switch received a packet that is not tagged, 
					     it will not insert a tag with PVID to this packet.
					     2. When Null VID replacement is disabled, switch will drop or deal the null VID tagged 
					     frame depends on the configuration.                        
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_nullVidReplace_get(uint32 port, uint32 *pEnabled)
{
    uint32 bitValue;    
    if ( (port > RTL8306_PORT5) || (NULL == pEnabled )){
        return FALSE;
    }
    /*Port 5 corresponding PHY6*/    
    if (RTL8306_PORT5 == port)  
        port ++ ; 
    
    rtl8306e_regbit_get(port, 22, 12, 0, &bitValue);
    *pEnabled = (bitValue ? TRUE : FALSE);

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_portPvidIndex_set
** Descriptions:         配置端口PVID索引（用端口号作为VLAN ID号）
** input parameters:     port              Specify the port(port 0 ~ port 5) to configure VLAN index
                         vlanIndex         Specify the VLAN index
** output parameters:    none
** Returned value:       成功或失败                       
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_portPvidIndex_set(uint32 port, uint32 vlanIndex)
{
    uint16 regValue;

    if(port > RTL8306_PORT5 || vlanIndex > (RTL8306_VLAN_ENTRYS -1))
        return FALSE;
    
    if (port < RTL8306_PORT5) 
    {
        rtl8306e_reg_get(port, 24, 0, &regValue);
        regValue = (regValue & 0xFFF) | (vlanIndex << 12);
        rtl8306e_reg_set(port, 24, 0, regValue);
    } else 
    {
        rtl8306e_reg_get(0, 26, 1, &regValue);
        regValue = (regValue & 0xFFF) | (vlanIndex << 12);
        rtl8306e_reg_set(0, 26, 1, regValue);
    }
#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.vlanPvidIdx[port]= (uint8) vlanIndex;
#endif
       
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_portPvidIndex_get
** Descriptions:         读取端口PVID索引（用端口号作为VLAN ID号）
** input parameters:     port              Specify the port(port 0 ~ port 5) to configure VLAN index
** output parameters:    pVlanIndex        pointer of VLAN index number
** Returned value:       成功或失败                       
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-20 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_portPvidIndex_get(uint32 port, uint16 *pVlanIndex) 
{
    if((port > RTL8306_PORT5) || pVlanIndex == NULL)
        return FALSE;
    
    if (port < RTL8306_PORT5) 
        rtl8306e_reg_get(port, 24, 0, pVlanIndex);
    else 
        rtl8306e_reg_get(0, 26, 1, pVlanIndex);
    *pVlanIndex = (*pVlanIndex >> 12) & 0xF;
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_portAcceptFrameType_set
** Descriptions:         设置VLAN支持的帧类型（用于检查802.1Q的TAG帧）
** input parameters:     port                 Port id
                         accept_frame_type    accept frame type
** output parameters:    none
** Returned value:       成功或失败   
** Note:				 支持的帧模式包括:
					     RTL8306E_ACCEPT_ALL  接收所有帧
					     RTL8306E_ACCEPT_TAG_ONLY	 只接收TAG帧
					     RTL8306E_ACCEPT_UNTAG_ONLY  不接收TAG帧					                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_portAcceptFrameType_set(uint32 port, rtl8306e_acceptFrameType_t accept_frame_type)
{
    uint16 regval;
    
    if(port > RTL8306_PORT5)
        return FALSE;
    
    if(RTL8306_PORT0 == port)
    {
        rtl8306e_reg_get(0, 31, 0, &regval);
        regval &= ~(0x3 << 7);
        regval |= (accept_frame_type << 7);
        rtl8306e_reg_set(0, 31, 0, regval);
    }
    else if (RTL8306_PORT5 == port)
    {
        rtl8306e_reg_get(6, 30, 1, &regval);
        regval &= ~(0x3 << 6);
        regval |= (accept_frame_type << 6);
        rtl8306e_reg_set(6, 30, 1, regval);        
    }
    else
    {
        rtl8306e_reg_get(port, 21, 2, &regval);
        regval &= ~(0x3 << 11);
        regval |= (accept_frame_type << 11);
        rtl8306e_reg_set(port, 21, 2, regval);        
    }
#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.vlanConfig.enVlanTagOnly = (accept_frame_type == RTL8306E_ACCEPT_TAG_ONLY ? TRUE : FALSE);
#endif
    return TRUE;
}


/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_portAcceptFrameType_get
** Descriptions:         读取VLAN支持的帧类型（用于检查802.1Q的TAG帧）
** input parameters:     port                      Port id
** output parameters:    pAccept_frame_type        accept frame type pointer
** Returned value:       成功或失败   
** Note:				 支持的帧模式包括:
					     RTL8306E_ACCEPT_ALL  接收所有帧
					     RTL8306E_ACCEPT_TAG_ONLY	 只接收TAG帧
					     RTL8306E_ACCEPT_UNTAG_ONLY  不接收TAG帧					                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_portAcceptFrameType_get(uint32 port, rtl8306e_acceptFrameType_t *pAccept_frame_type)
{
    uint16 regval;
    
    if((port > RTL8306_PORT5) || (pAccept_frame_type == NULL))
        return FALSE;

    if(RTL8306_PORT0 == port)
    {
        rtl8306e_reg_get(0, 31, 0, &regval);
        regval &= (0x3 << 7);
        *pAccept_frame_type = (rtl8306e_acceptFrameType_t)(regval >> 7);
    }
    else if (RTL8306_PORT5 == port)
    {
        rtl8306e_reg_get(6, 30, 1, &regval);
        regval &= (0x3 << 6);
        *pAccept_frame_type = (rtl8306e_acceptFrameType_t)(regval >> 6);
    }
    else
    {
        rtl8306e_reg_get(port, 21, 2, &regval);
        regval &= (0x3 << 11);
        *pAccept_frame_type = (rtl8306e_acceptFrameType_t)(regval >> 11);        
    }

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_tagInsert_set
** Descriptions:         在入口处插入VLAN TAG
** input parameters:     egPort               egress port number 0~5（输出端口）
                         igPortMsk            ingress port mask（入口屏蔽）
** output parameters:    none
** Returned value:       成功或失败   
** Note:				 从输入端口来的包没加VLAN TAG则给这个包加上VLAN TAG	
						 从PORT1,3,5过来的包要是从PORT0输出，则添加VLAN TAG
						 rtl8306e_vlan_tagInsert_set(0, 0x2A)				                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_tagInsert_set(uint32 egPort, uint32 igPortMsk)
{
    uint16 regval;
    
    if((egPort > RTL8306_PORT5) || (igPortMsk > 0x3F))
        return FALSE;
    
    /*enable EN_INSERT_TAG*/
    rtl8306e_regbit_set(0, 28, 0, 3, 1);

    if(RTL8306_PORT0 == egPort)
    {
        rtl8306e_reg_get(0, 28, 3, &regval);
        regval &= ~(0x3F << 1);
        regval |= (igPortMsk << 1);
        rtl8306e_reg_set(0, 28, 3, regval);        
    }
    else if(RTL8306_PORT5 == egPort)
    {
        rtl8306e_reg_get(6, 30, 1, &regval);
        regval &= ~0x3F;
        regval |= igPortMsk;
        rtl8306e_reg_set(6, 30, 1, regval);
    }
    else
    {
        rtl8306e_reg_get(egPort, 30, 1, &regval);
        regval &= ~(0x3F << 9);
        regval |= (igPortMsk << 9);
        rtl8306e_reg_set(egPort, 30, 1, regval);
    }                
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_tagInsert_get
** Descriptions:         在入口处插入VLAN TAG
** input parameters:     egPort               egress port number 0~5（输出端口）
** output parameters:    igPortMsk            ingress port mask（入口屏蔽）
** Returned value:       成功或失败   
** Note:				 从输入端口来的包没加VLAN TAG则给这个包加上VLAN TAG					                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_tagInsert_get(uint32 egPort, uint32 * pIgPortMsk)
{
    uint32 regval ;
    uint16 regvalue = 0;
    if ((egPort > RTL8306_PORT5) || (NULL == pIgPortMsk)){
        return FALSE;
	}  
    rtl8306e_regbit_get(0, 28, 0, 3, &regval); /*EN_INSERT_TAG = 0, insert tag operation is disable*/
    if(!regval){
        *pIgPortMsk = 0;
    }
    if(RTL8306_PORT0 == egPort)
    {
        rtl8306e_reg_get(0, 28, 3, &regvalue);
        regvalue &= (0x3F << 1);
        *pIgPortMsk = regvalue >> 1;
    }
    else if(RTL8306_PORT5 == egPort)
    {
        rtl8306e_reg_get(6, 30, 1, &regvalue);
        regvalue &= 0x3F;
        *pIgPortMsk = regvalue;
    }
    else 
    {
        rtl8306e_reg_get(egPort, 30, 1, &regvalue);
        regvalue &= (0x3F << 9);
        *pIgPortMsk = regvalue >> 9;
    }    
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_entry_set
** Descriptions:         写VLAN成员
** input parameters:     vlanIndex     VLAN entry index
					     vid           VLAN ID to configure
					     mbrmsk        VLAN member set portmask
					     untagmsk      VLAN untag set portmask
** output parameters:    none
** Returned value:       成功或失败   
** Note:				 There are 16 VLAN entry supported. User could configure the member set and untag set
					     for specified vid through this API. The portmask's bit N means port N.
					     For example, mbrmask 23=0x17=010111 means port 0,1,2,4 in the member set.				                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_entry_set(uint32 vlanIndex, uint32 vid, uint32 mbrmsk, uint32 untagmsk )
{
    uint16 regValue;

    if ((vid > RTL8306_VIDMAX) || (mbrmsk > 0x3F) || (untagmsk > 0x3F))
        return FALSE;
    
    /*enable EN_UNTAG_SET*/
    rtl8306e_regbit_set(0, 29, 12, 0, 1);
    
    /*set vlan entry*/
    switch(vlanIndex) 
    {
        case 0: /* VLAN[A] */
            rtl8306e_reg_get(0, 25, 0, &regValue);
            regValue = (regValue & 0xF000) | vid ;
            rtl8306e_reg_set(0, 25, 0, regValue);
            rtl8306e_reg_get(0, 24, 0, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(0, 24, 0, regValue);
            rtl8306e_reg_get(0, 29, 0, &regValue);
            regValue &= ~0x3F;
            regValue |= untagmsk;
            rtl8306e_reg_set(0, 29, 0, regValue);            
            break;

        case 1: /* VLAN[B] */
            rtl8306e_reg_get(1, 25, 0, &regValue);
            regValue = (regValue & 0xF000) | vid ;
            rtl8306e_reg_set(1, 25, 0, regValue);
            rtl8306e_reg_get(1, 24, 0, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(1, 24, 0, regValue);
            rtl8306e_reg_get(1, 30, 1, &regValue);
            regValue &= ~0x3F;
            regValue |= untagmsk;
            rtl8306e_reg_set(1, 30, 1, regValue);            
            break;

        case 2: /* VLAN[C] */
            rtl8306e_reg_get(2, 25, 0, &regValue);
            regValue = (regValue & 0xF000) | vid ;
            rtl8306e_reg_set(2, 25, 0, regValue);
            rtl8306e_reg_get(2, 24, 0, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(2, 24, 0, regValue);
            rtl8306e_reg_get(2, 30, 1, &regValue);
            regValue &= ~0x3F;
            regValue |= untagmsk;
            rtl8306e_reg_set(2, 30, 1, regValue);                
            break;

        case 3: /* VLAN[D] */
            rtl8306e_reg_get(3, 25, 0, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(3, 25, 0, regValue);
            rtl8306e_reg_get(3, 24, 0, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(3, 24, 0, regValue);
            rtl8306e_reg_get(3, 30, 1, &regValue);
            regValue &= ~0x3F;
            regValue |= untagmsk;
            rtl8306e_reg_set(3, 30, 1, regValue);                
            break;

        case 4: /* VLAN[E] */
            rtl8306e_reg_get(4, 25, 0, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(4, 25, 0, regValue);
            rtl8306e_reg_get(4, 24, 0, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(4, 24, 0, regValue);
            rtl8306e_reg_get(4, 30, 1, &regValue);
            regValue &= ~0x3F;
            regValue |= untagmsk;
            rtl8306e_reg_set(4, 30, 1, regValue);                            
            break;

        case 5: /* VLAN[F] */
            rtl8306e_reg_get(0, 27, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(0, 27, 1, regValue);
            rtl8306e_reg_get(0, 26, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(0, 26, 1, regValue);
            rtl8306e_reg_get(0, 26, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(0, 26, 1, regValue);            
            break;
        
        case 6: /* VLAN[G] */
            rtl8306e_reg_get(1, 27, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(1, 27, 1, regValue);
            rtl8306e_reg_get(1, 26, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(1, 26, 1, regValue);
            rtl8306e_reg_get(1, 26, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(1, 26, 1, regValue);                        
            break;

        case 7: /* VLAN[H] */
            rtl8306e_reg_get(2, 27, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(2, 27, 1, regValue);
            rtl8306e_reg_get(2, 26, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(2, 26, 1, regValue);
            rtl8306e_reg_get(2, 26, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(2, 26, 1, regValue);                                    
            break;

        case 8: /* VLAN[I] */
            rtl8306e_reg_get(3, 27, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(3, 27, 1, regValue);
            rtl8306e_reg_get(3, 26, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(3, 26, 1, regValue);
            rtl8306e_reg_get(3, 26, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(3, 26, 1, regValue);                        
            
            break;

        case 9: /* VLAN[J] */
            rtl8306e_reg_get(4, 27, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(4, 27, 1, regValue);
            rtl8306e_reg_get(4, 26, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(4, 26, 1, regValue);
            rtl8306e_reg_get(4, 26, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(4, 26, 1, regValue);                                    
            break;

        case 10: /* VLAN[K] */
            rtl8306e_reg_get(0, 29, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(0, 29, 1, regValue);
            rtl8306e_reg_get(0, 28, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(0, 28, 1, regValue);
            rtl8306e_reg_get(0, 28, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(0, 28, 1, regValue);                                    
            break;

        case 11: /* VLAN[L] */
            rtl8306e_reg_get(1, 29, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(1, 29, 1, regValue);
            rtl8306e_reg_get(1, 28, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(1, 28, 1, regValue);
            rtl8306e_reg_get(1, 28, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(1, 28, 1, regValue);                                                
            break;

        case 12: /* VLAN[M] */
            rtl8306e_reg_get(2, 29, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(2, 29, 1, regValue);
            rtl8306e_reg_get(2, 28, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(2, 28, 1, regValue);
            rtl8306e_reg_get(2, 28, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(2, 28, 1, regValue);                                                
            break;

        case 13: /* VLAN[N] */
            rtl8306e_reg_get(3, 29, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(3, 29, 1, regValue);
            rtl8306e_reg_get(3, 28, 1, &regValue);
            regValue = (regValue & 0xFFC0) |mbrmsk;
            rtl8306e_reg_set(3, 28, 1, regValue);
            rtl8306e_reg_get(3, 28, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(3, 28, 1, regValue);                                                
            break;

        case 14: /* VLAN[O] */
            rtl8306e_reg_get(4, 29, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(4, 29, 1, regValue);
            rtl8306e_reg_get(4, 28, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(4, 28, 1, regValue);
            rtl8306e_reg_get(4, 28, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(4, 28, 1, regValue);                                                
            break;

        case 15: /* VLAN[P] */
            rtl8306e_reg_get(0, 31, 1, &regValue);
            regValue = (regValue & 0xF000) | vid;
            rtl8306e_reg_set(0, 31, 1, regValue);
            rtl8306e_reg_get(0, 30, 1, &regValue);
            regValue = (regValue & 0xFFC0) | mbrmsk;
            rtl8306e_reg_set(0, 30, 1, regValue);
            rtl8306e_reg_get(0, 30, 1, &regValue);
            regValue &= ~(0x3F << 6);
            regValue |= (untagmsk << 6);
            rtl8306e_reg_set(0, 30, 1, regValue);                                                
            break;
        default:
            return FALSE;

    }    

#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.vlanTable[vlanIndex].vid = (uint16)vid;
    rtl8306_TblBak.vlanTable[vlanIndex].memberPortMask = (uint8)mbrmsk;
#endif
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_entry_get
** Descriptions:         读取VLAN成员
** input parameters:     vlanIndex     VLAN entry index				
** output parameters:    pVid          the pointer of VLAN ID 
					     pMbrmsk       the pointer of VLAN member set portmask
					     pUntagmsk     the pointer of VLAN untag set portmask
** Returned value:       成功或失败   				                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_entry_get(uint32 vlanIndex, uint16 *pVid, uint16 *pMbrmsk, uint16 *pUntagmsk)
{

    if(  (NULL == pVid) ||  (NULL == pMbrmsk))
        return FALSE;
    
    switch(vlanIndex)
    {
        case 0: /*VLAN[A]*/
            rtl8306e_reg_get(0, 25, 0, pVid);
            rtl8306e_reg_get(0, 24, 0, pMbrmsk);
            rtl8306e_reg_get(0, 29, 0, pUntagmsk);            
            break;        
            
        case 1: /*VLAN[B]*/
            rtl8306e_reg_get(1, 25, 0, pVid);
            rtl8306e_reg_get(1, 24, 0, pMbrmsk);
            rtl8306e_reg_get(1, 30, 1, pUntagmsk);                        
            break;
            
        case 2: /*VLAN[C]*/
            rtl8306e_reg_get(2, 25, 0, pVid);
            rtl8306e_reg_get(2, 24, 0, pMbrmsk);
            rtl8306e_reg_get(2, 30, 1, pUntagmsk);                                    
            break;
            
        case 3: /*VLAN[D]*/
            rtl8306e_reg_get(3, 25, 0, pVid);
            rtl8306e_reg_get(3, 24, 0, pMbrmsk);
            rtl8306e_reg_get(3, 30, 1, pUntagmsk);                                    
            break;
            
        case 4: /*VLAN[E]*/
            rtl8306e_reg_get(4, 25, 0, pVid);
            rtl8306e_reg_get(4, 24, 0, pMbrmsk);
            rtl8306e_reg_get(4, 30, 1, pUntagmsk);                                    
            break;
            
        case 5: /*VLAN[F]*/
            rtl8306e_reg_get(0, 27, 1, pVid);
            rtl8306e_reg_get(0, 26, 1, pMbrmsk);
            rtl8306e_reg_get(0, 26, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 6: /*VLAN[G]*/
            rtl8306e_reg_get(1, 27, 1, pVid);
            rtl8306e_reg_get(1, 26, 1, pMbrmsk);
            rtl8306e_reg_get(1, 26, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 7: /*VLAN[H]*/
            rtl8306e_reg_get(2, 27, 1, pVid);
            rtl8306e_reg_get(2, 26, 1, pMbrmsk);
            rtl8306e_reg_get(2, 26, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 8: /*VLAN[I]*/        
            rtl8306e_reg_get(3, 27, 1, pVid);
            rtl8306e_reg_get(3, 26, 1, pMbrmsk);
            rtl8306e_reg_get(3, 26, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 9: /*VLAN[J]*/
            rtl8306e_reg_get(4, 27, 1, pVid);
            rtl8306e_reg_get(4, 26, 1, pMbrmsk);
            rtl8306e_reg_get(4, 26, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 10: /*VLAN[K]*/
            rtl8306e_reg_get(0, 29, 1, pVid);
            rtl8306e_reg_get(0, 28, 1, pMbrmsk);
            rtl8306e_reg_get(0, 28, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 11: /*VLAN[L]*/
            rtl8306e_reg_get(1, 29, 1, pVid);
            rtl8306e_reg_get(1, 28, 1, pMbrmsk);
            rtl8306e_reg_get(1, 28, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 12: /*VLAN[M]*/
            rtl8306e_reg_get(2, 29, 1, pVid);
            rtl8306e_reg_get(2, 28, 1, pMbrmsk);
            rtl8306e_reg_get(2, 28, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 13: /*VLAN[N]*/
            rtl8306e_reg_get(3, 29, 1, pVid);
            rtl8306e_reg_get(3, 28, 1, pMbrmsk);
            rtl8306e_reg_get(3, 28, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 14: /*VLAN[O]*/
            rtl8306e_reg_get(4, 29, 1, pVid);
            rtl8306e_reg_get(4, 28, 1, pMbrmsk);
            rtl8306e_reg_get(4, 28, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        case 15: /*VLAN[P]*/
            rtl8306e_reg_get(0, 31, 1, pVid);
            rtl8306e_reg_get(0, 30, 1, pMbrmsk);
            rtl8306e_reg_get(0, 30, 1, pUntagmsk);   
            *pUntagmsk >>= 6;
            break;
            
        default:
            return  FALSE;
    }
    
    *pVid  &= 0xFFF;
    *pMbrmsk  &= 0x3F;
    *pUntagmsk &= 0x3F;
    
    return  TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_vlanBasedPriority_set
** Descriptions:         设置VLAN优先级
** input parameters:     vlanIndex     VLAN entry index	
						 pri           the specified VLAN priority			
** output parameters:    none
** Returned value:       成功或失败   
** Note：                每一个VLAN都可以指定优先级，如果vlanIndex > 15，则VID不在VLAN组里面，不匹配的VID
						 也可指定优先级				                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_vlanBasedPriority_set(uint32 vlanIndex, uint32 pri)
{
    uint16 regval;
    
    if (pri > 3)
        return FALSE;

    switch(vlanIndex)
    {
        case 0: /*VLAN[A]*/
            rtl8306e_regbit_set(0, 29, 8, 0, 1);
            rtl8306e_reg_get(0, 29, 0, &regval);
            regval &= ~(0x3 << 6);
            regval |= (pri << 6);
            rtl8306e_reg_set(0, 29, 0, regval);            
            break;        
            
        case 1: /*VLAN[B]*/
            rtl8306e_regbit_set(1, 30, 8, 1, 1);
            rtl8306e_reg_get(1, 30, 1, &regval);
            regval &= ~(0x3 << 6);
            regval |= (pri << 6);
            rtl8306e_reg_set(1, 30, 1, regval);                                   
            break;
            
        case 2: /*VLAN[C]*/
            rtl8306e_regbit_set(2, 30, 8, 1, 1);
            rtl8306e_reg_get(2, 30, 1, &regval);
            regval &= ~(0x3 << 6);
            regval |= (pri << 6);
            rtl8306e_reg_set(2, 30, 1, regval);                                   
            break;
            
        case 3: /*VLAN[D]*/
            rtl8306e_regbit_set(3, 30, 8, 1, 1);
            rtl8306e_reg_get(3, 30, 1, &regval);
            regval &= ~(0x3 << 6);
            regval |= (pri << 6);
            rtl8306e_reg_set(3, 30, 1, regval);                                               
            break;
            
        case 4: /*VLAN[E]*/
            rtl8306e_regbit_set(4, 30, 8, 1, 1);
            rtl8306e_reg_get(4, 30, 1, &regval);
            regval &= ~(0x3 << 6);
            regval |= (pri << 6);
            rtl8306e_reg_set(4, 30, 1, regval);                                               
            break;
            
        case 5: /*VLAN[F]*/
            rtl8306e_regbit_set(0, 27, 14, 1, 0);
            rtl8306e_reg_get(0, 27, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(0, 27, 1, regval);                                               
            break;
            
        case 6: /*VLAN[G]*/
            rtl8306e_regbit_set(1, 26, 14, 1, 0);
            rtl8306e_reg_get(1, 26, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(1, 26, 1, regval);                                                           
            break;
            
        case 7: /*VLAN[H]*/
            rtl8306e_regbit_set(2, 26, 14, 1, 0);
            rtl8306e_reg_get(2, 26, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(2, 26, 1, regval);                                                                       
            break;
            
        case 8: /*VLAN[I]*/        
            rtl8306e_regbit_set(3, 26, 14, 1, 1);
            rtl8306e_reg_get(3, 26, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(3, 26, 1, regval);                                                                                   
            break;
            
        case 9: /*VLAN[J]*/
            rtl8306e_regbit_set(4, 26, 14, 1, 1);
            rtl8306e_reg_get(4, 26, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(4, 26, 1, regval);                                                                                               
            break;
            
        case 10: /*VLAN[K]*/
            rtl8306e_regbit_set(0, 28, 14, 1, 1);
            rtl8306e_reg_get(0, 28, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(0, 28, 1, regval);                                                                                                           
            break;
            
        case 11: /*VLAN[L]*/
            rtl8306e_regbit_set(1, 28, 14, 1, 1);
            rtl8306e_reg_get(1, 28, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(1, 28, 1, regval);                                                                                                                       
            break;
            
        case 12: /*VLAN[M]*/
            rtl8306e_regbit_set(2, 28, 14, 1, 0);
            rtl8306e_reg_get(2, 28, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(2, 28, 1, regval);                                                                                                                                   
            break;
            
        case 13: /*VLAN[N]*/
            rtl8306e_regbit_set(3, 28, 14, 1, 0);
            rtl8306e_reg_get(3, 28, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(3, 28, 1, regval);                                                                                                                                               
            break;
            
        case 14: /*VLAN[O]*/
            rtl8306e_regbit_set(4, 28, 14, 1, 0);
            rtl8306e_reg_get(4, 28, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(4, 28, 1, regval);                                                                                                                                                           
            break;
            
        case 15: /*VLAN[P]*/
            rtl8306e_regbit_set(0, 30, 14, 1, 0);
            rtl8306e_reg_get(0, 30, 1, &regval);
            regval &= ~(0x3 << 12);
            regval |= (pri << 12);
            rtl8306e_reg_set(0, 30, 1, regval);                                                                                                                                                                       
            break;
            
        default: /*unmatched vlan entry*/
            rtl8306e_regbit_set(0, 29, 11, 0, 1);
            rtl8306e_reg_get(0, 29, 0, &regval);
            regval &= ~(0x3 << 9);
            regval |= (pri << 9);
            rtl8306e_reg_set(0, 29, 0, regval);                                                                                                                                                                                                          
            return  FALSE;
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_vlanBasedPriority_get
** Descriptions:         设置VLAN优先级
** input parameters:     vlanIndex     VLAN entry index							 		
** output parameters:    pri           the specified VLAN priority	
** Returned value:       成功或失败   
** Note：                每一个VLAN都可以指定优先级，如果vlanIndex > 15，则VID不在VLAN组里面，不匹配的VID
						 也可指定优先级				                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_vlanBasedPriority_get(uint32 vlanIndex, uint32 *pPri)
{
    uint16 regval;
    
    if (NULL == pPri)
        return FALSE;

    switch(vlanIndex)
    {
        case 0: /*VLAN[A]*/
            rtl8306e_reg_get(0, 29, 0, &regval);
            regval &= (0x3 << 6);
            *pPri = regval >> 6;
            break;        
            
        case 1: /*VLAN[B]*/
            rtl8306e_reg_get(1, 30, 1, &regval);
            regval &= (0x3 << 6);
            *pPri = regval >> 6;
            break;
            
        case 2: /*VLAN[C]*/
            rtl8306e_reg_get(2, 30, 1, &regval);
            regval &= (0x3 << 6);
            *pPri = regval >> 6;
            break;
            
        case 3: /*VLAN[D]*/
            rtl8306e_reg_get(3, 30, 1, &regval);
            regval &= (0x3 << 6);
            *pPri = regval >> 6;
            break;
            
        case 4: /*VLAN[E]*/
            rtl8306e_reg_get(4, 30, 1, &regval);
            regval &= (0x3 << 6);
            *pPri = regval >> 6;
            break;
            
        case 5: /*VLAN[F]*/
            rtl8306e_reg_get(0, 27, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 6: /*VLAN[G]*/
            rtl8306e_reg_get(1, 26, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 7: /*VLAN[H]*/
            rtl8306e_reg_get(2, 26, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 8: /*VLAN[I]*/        
            rtl8306e_reg_get(3, 26, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 9: /*VLAN[J]*/
            rtl8306e_reg_get(4, 26, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 10: /*VLAN[K]*/
            rtl8306e_reg_get(0, 28, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 11: /*VLAN[L]*/
            rtl8306e_reg_get(1, 28, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 12: /*VLAN[M]*/
            rtl8306e_reg_get(2, 28, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 13: /*VLAN[N]*/
            rtl8306e_reg_get(3, 28, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 14: /*VLAN[O]*/
            rtl8306e_reg_get(4, 28, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        case 15: /*VLAN[P]*/
            rtl8306e_reg_get(0, 30, 1, &regval);
            regval &= (0x3 << 12);
            *pPri = regval >> 12;
            break;
            
        default: /*unmatched vlan entry*/
            rtl8306e_reg_get(0, 29, 0, &regval);
            regval &= (0x3 << 9);
            *pPri = regval >> 9;
            return  FALSE;
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_transEnable_set
** Descriptions:         配置
** input parameters:     enable          enable or disable VLAN translation	
						 portmask    -   NNI port is set 1 and UNI port is set 0					 		
** output parameters:    none	
** Returned value:       成功或失败   
** Note：                只有在NNI（网络节点接口）和 UNI（用户网接口）之间传输的时候需要随VID变化	
						 the VLAN tranlation function and Q-in-Q(SVLAN) could not be enabled  
       					 at the same time, user should choose one of them. 		                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_transEnable_set(uint32 enable, uint32 portmask)
{
    uint16 regval;

    rtl8306e_reg_get(6, 30, 3, &regval);

    if(enable)
    {
        regval &= ~0xff;
        regval |= (1 << 6) | (portmask & 0x3F);
        rtl8306e_reg_set(6, 30, 3, regval);
    }
    else
    {
        regval &= ~0xff;
        rtl8306e_reg_set(6, 30, 3, regval);
    }

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_transEnable_get
** Descriptions:         
** input parameters:     none					 		
** output parameters:    pEnable         the pointer of enable or disable VLAN translation
 					     pPortMask       the pointer of VLAN translation port mask	
** Returned value:       成功或失败   
** Note：                只有在NNI（网络节点接口）和 UNI（用户网接口）之间传输的时候需要随VID变化	
						 the VLAN tranlation function and Q-in-Q(SVLAN) could not be enabled  
       					 at the same time, user should choose one of them. 		                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_transEnable_get(uint32 *pEnable, uint32 *pPortMask)
{
    uint16 regval;

    if((NULL == pEnable) || (NULL == pPortMask))
        return FALSE;
    
    rtl8306e_reg_get(6, 30, 3, &regval);
    if((regval & (0x3 << 6)) == (0x1 << 6))
    {
        *pEnable = 1;
        *pPortMask = regval & 0x3F;
    }
    else
    {
        *pEnable = 0;
        *pPortMask = 0;
    }

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_transparentEnable_set
** Descriptions:         使能VLAN transparent
** input parameters:     enable       -   enable or disable VLAN transparent.					 		
** output parameters:    none
** Returned value:       成功或失败   		                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_transparentEnable_set(uint32 enable)
{
    uint32 port;

    if (enable)
    {        
        rtl8306e_regbit_set(0, 18, 8, 0, 1); /*set vlan disabled*/      
        rtl8306e_vlan_tagAware_set(FALSE);  /*disable tag aware*/        
        rtl8306e_regbit_set(0, 29, 12, 0, 0); /*disable EN_UNTAG_SET*/             
        rtl8306e_regbit_set(6, 30, 6, 3, 0);  /*set vlan translation disabled*/                
        for (port = 0; port < 5; port ++)
        {
            rtl8306e_regbit_set(port, 22, 15, 0, 1);/*set port0~5 untag unawre and disable Non-PVID discard*/
            rtl8306e_regbit_set(port, 22, 11, 0, 0);
        } 
        rtl8306e_regbit_set(6, 24, 1, 0, 1);
        rtl8306e_regbit_set(6, 22, 11, 0, 0);                
        rtl8306e_regbit_set(0, 28, 0, 3, 0); /*disable EN_INSERT_TAG*/
    }
    else
    {       
        rtl8306e_regbit_set(0, 18, 8, 0, 0); /*set vlan enabled*/        
        rtl8306e_vlan_tagAware_set(TRUE); /*enable tag aware*/
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_transVid_set
** Descriptions:         Set the translated VID	（替换为新的VID）
** input parameters:     vlanIndex      the VLAN entry index
       					 transVid       the new VID					 		
** output parameters:    none
** Returned value:       成功或失败   		                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_transVid_set(uint32 vlanIndex, uint32 transVid)    
{
   uint16 regval;
   
   if((vlanIndex > 15) || (transVid > 0xFFF)){
        return FALSE;
   }
   if(vlanIndex < 15)     
   {
        rtl8306e_reg_get(6, 17 + vlanIndex, 4, &regval);
        regval &= ~0xfff;
        regval |= transVid;
        rtl8306e_reg_set(6, 17 + vlanIndex, 4, regval);
   }
   else
   {
        rtl8306e_reg_get(6, 18, 1, &regval);
        regval &= ~0xfff;
        regval |= transVid;
        rtl8306e_reg_set(6, 18, 1, regval);
   }       
   return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_vlan_transVid_get
** Descriptions:         get the translated VID	（替换为新的VID）
** input parameters:     vlanIndex      the VLAN entry index       					 					 		
** output parameters:    ptransVid       the new VID
** Returned value:       成功或失败   		                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_vlan_transVid_get(uint32 vlanIndex, uint32 *pTransVid)
{
    uint16 regval;

    if((vlanIndex > 15) || (NULL == pTransVid)){
        return FALSE;
	}
    if(vlanIndex < 15)
    {
       rtl8306e_reg_get(6, 17 + vlanIndex, 4, &regval);
       *pTransVid = (regval & 0xfff);
    }
    else
    {
       rtl8306e_reg_get(6, 18, 1, &regval);
       *pTransVid = (regval & 0xfff);
    }       
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_svlan_tagAdmit_set
** Descriptions:         Set Q-in-Q tag admit control
** input parameters:     port             port id
                         enable           enable tag admit control       					 					 		
** output parameters:    none
** Returned value:       成功或失败   		                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_svlan_tagAdmit_set(uint32 port, uint32 enable)
{
    if (port > 5)
        return FALSE;

    if(5 == port)
    {
        rtl8306e_regbit_set(6, 23, 0, 0, enable ? 1:0);
    }
    else
    {
        rtl8306e_regbit_set(6, 17 + port, 0, 0, enable ? 1:0);
    }

    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_svlan_tagAdmit_get
** Descriptions:         get Q-in-Q tag admit control
** input parameters:     port             port id     					 					 		
** output parameters:    pEnable          the pointer of enable tag admit control
** Returned value:       成功或失败   		                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_svlan_tagAdmit_get(uint32 port, uint32 *pEnable)
{
    uint16 regval;    
    if(port > 5){
        return FALSE;
    }
    if(5 == port)
    {
        rtl8306e_reg_get(6, 23, 0, &regval);
        *pEnable = regval ? 1:0;
    }
    else 
    {
        rtl8306e_reg_get(6, 17 + port, 0, &regval);
        *pEnable = regval ? 1:0;        
    }        
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_svlan_otagSrc_set
** Descriptions:         设置外部TAG VLAN和优先级
** input parameters:     port            port id
				         ovidSrc         ovid comes from
				         opriSrc         opri comes from    					 					 		
** output parameters:    none
** Returned value:       成功或失败  
** Note:				 ovidSrc RTL8306E_VIDSRC_POVID : ovid is port-based ovid,    RTL8306E_VIDSRC_NVID:ovid is new vid(translated vid)
				         opriSrc  RTL8306E_PRISRC_PPRI   : opri is port-based priority, RTL8306E_PRISRC_1PRMK: opri is 1p remarking value 		                             
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_svlan_otagSrc_set(uint32 port, uint32 ovidSrc, uint32 opriSrc)
{
    uint16 regval;
    
    if(port > 5){
        return FALSE;
	}
    if(5 == port)
    {
        rtl8306e_reg_get(6, 23, 0, &regval);
        regval &= ~0xC;
        regval |= ovidSrc ? (1 << 3):0;
        regval |= opriSrc ? (1 << 2) :0;
        rtl8306e_reg_set(6, 23, 0, regval);
    }
    else
    {
        rtl8306e_reg_get(6, 17 + port, 0, &regval);
        regval &= ~0xC;
        regval |= ovidSrc ? (1 << 3):0;
        regval |= opriSrc ? (1 << 2) :0;
        rtl8306e_reg_set(6, 17 + port, 0, regval);        
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_svlan_otagSrc_set
** Descriptions:         设置外部TAG VLAN和优先级
** input parameters:     port            port id 					 					 		
** output parameters:    pOvidsrc         the pointer of ovid comes from
					     pOpriSrc         the pointer of opri comes from 
** Returned value:       成功或失败  
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_svlan_otagSrc_get(uint32 port, uint32 *pOvidsrc, uint32 *pOpriSrc)
{
    uint16 regval;

    if(port > 5)
        return FALSE;

    if(5 == port)
    {
        rtl8306e_reg_get(6, 23, 0, &regval);
        *pOvidsrc = (regval & (1 << 3)) ? 1:0;
        *pOpriSrc = (regval & (1 << 2)) ? 1:0;
    }
    else
    {
        rtl8306e_reg_get(6, 17 + port, 0, &regval);
        *pOvidsrc = (regval & (1 << 3)) ? 1:0;
        *pOpriSrc = (regval & (1 << 2)) ? 1:0;
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_cpu_set
** Descriptions:         指定Asic CPU端口
** input parameters:     port         Specify the port
 				         enTag        CPU tag insert or not					 					 		
** output parameters:    none
** Returned value:       成功或失败 
**Note:					 If the port is specified RTL8306_NOCPUPORT, it means
       					 that no port is assigned as cpu port        
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_cpu_set(uint32 port, uint32 enTag) 
{
    uint16 regValue;
    if (port > RTL8306_NOCPUPORT){
        return FALSE;
	}
    if (port < RTL8306_PORT_NUMBER) 
    {        
        rtl8306e_regbit_set(2, 21, 15, 3, 0);  /*enable CPU port Function */                     
        rtl8306e_regbit_set(2, 21, 12, 3, enTag ? 1 : 0);  /*whether inserting CPU tag*/                
        rtl8306e_regbit_set(4, 21, 7, 0, 1);   /*enable the ability to check cpu tag*/                
        rtl8306e_regbit_set(2, 21, 11, 3, 1);	/*enable removing CPU tag*/
        rtl8306e_reg_get(4, 21, 0, &regValue);
        regValue = (regValue & 0xFFF8) | port;
        rtl8306e_reg_set(4, 21, 0, regValue);      
        rtl8306e_regbit_set(4, 21, 3, 0, 0);   /*enable asic recaculate crc for pkt with cpu tag*/
               
        if (port < RTL8306_PORT5) 
        {
            rtl8306e_regbit_set(port, 17, 9, 2, 0);	 /*disable IEEE802.1x function of CPU Port*/
            rtl8306e_regbit_set(port, 17, 8, 2, 0);
        }
        else 
        {
            rtl8306e_regbit_set(6, 17, 9, 2, 0);
            rtl8306e_regbit_set(6, 17, 8, 2, 0);
        }
             
        if (RTL8306_PORT5 == port)
        {
            rtl8306e_regbit_set(6, 22, 15, 0, TRUE);    /*Port 5 should be enabled especially*/
        }
    }   
    else 
    {       
        rtl8306e_regbit_set(2, 21, 15, 3, 1);  /*disable CPU port Function */
        rtl8306e_regbit_set(2, 21, 12, 3, 0);        
        rtl8306e_reg_get(4, 21, 0, &regValue);
        regValue = (regValue & 0xFFF8) | port;
        rtl8306e_reg_set(4, 21, 0, regValue);
    }   
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_cpu_Get
** Descriptions:         读取指定Asic CPU端口数量
** input parameters:     none				 					 		
** output parameters:    pPort      the pointer of CPU port number
 					     pEnTag     the pointer of CPU tag insert or not
** Returned value:       成功或失败 
**Note:					 If the port is specified RTL8306_NOCPUPORT, it means
       					 that no port is assigned as cpu port        
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_cpu_get(uint32 *pPort, uint32 *pEnTag) 
{
    uint16 regValue;
    uint32 bitValue, bitVal, cpufun;

    if ((NULL == pPort ) || (NULL == pEnTag)){
        return FALSE;
    }
    rtl8306e_regbit_get(2, 21, 12, 3, &bitValue);
    rtl8306e_regbit_get(2, 21, 15, 3, &cpufun);
    rtl8306e_regbit_get(4, 21, 7, 0, &bitVal);
    
    rtl8306e_reg_get(4, 21, 0, &regValue);
    *pPort = regValue & 0x7;

    if ((!cpufun) && bitValue && bitVal){
        *pEnTag = TRUE;
	}
    else{ 
        *pEnTag = FALSE;
    }
    if(cpufun){
        *pPort = RTL8306_NOCPUPORT;
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_softReset_set
** Descriptions:         QOS软件复位
** input parameters:     none				 					 		
** output parameters:    none
** Returned value:       成功或失败       
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_softReset_set(void) 
{    
    /*software reset*/
    rtl8306e_regbit_set(0, 16, 12, 0, 1);    
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_queueNum_set
** Descriptions:         写输出端口队列数(1 ~4)
** input parameters:     none				 					 		
** output parameters:    none
** Returned value:       成功或失败 
** Note:      			 Queue number is global configuration for switch.     
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_queueNum_set(uint32 num) 
{
    uint16 regValue;    
    if ((num == 0) ||(num > 4)){
        return FALSE;
    }
    rtl8306e_reg_get(2, 22, 3, &regValue);
    rtl8306e_reg_set(2, 22, 3, (regValue & 0xFFF3) | ((num-1) << 2));
    rtl8306e_qos_softReset_set( );/*A soft-reset is required after configuring queue num*/    
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_queueNum_get
** Descriptions:         读取输出端口队列数(1 ~4)
** input parameters:     none				 					 		
** output parameters:    none
** Returned value:       成功或失败 
** Note:      			 Queue number is global configuration for switch.     
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_queueNum_get(uint32 *pNum) 
{
    uint16 regValue;
    if (NULL == pNum){ 
        return FALSE;
    }
    rtl8306e_reg_get(2, 22, 3, &regValue);
    *pNum = ((regValue & 0xC) >> 2) + 1;
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_priToQueMap_set
** Descriptions:         为队列ID映射设置优先级（利用优先级进行归类）
** input parameters:     priority     priority value (0 ~ 3)
 					     qid          Queue id (0~3)				 					 		
** output parameters:    none
** Returned value:       成功或失败 
** Note:      			 Packets could be classified into specified queue through their priority. 
 				         we can use this function to set pkt priority with queue id mapping    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_priToQueMap_set(uint32 priority, uint32 qid) 
{
    uint16 regValue;
    if ((qid > 3) || (priority > 3)){ 
        return FALSE;
    }
    rtl8306e_reg_get(1, 22, 3, &regValue);
    switch(priority) 
    {
        case 0:
            regValue = (regValue & 0xFFFC) | qid;
            break;
        case 1:
            regValue = (regValue & 0xFFF3) | (qid << 2);
            break;
        case 2:
            regValue = (regValue & 0xFFCF) | (qid << 4);
            break;
        case 3:
            regValue = (regValue & 0xFF3F) | (qid << 6);
            break;
        default:
            return FALSE;
    }
    rtl8306e_reg_set(1, 22, 3, regValue);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_priToQueMap_get
** Descriptions:         为队列ID映射设置优先级（利用优先级进行归类）
** input parameters:     priority     priority value (0 ~ 3)				 					 		
** output parameters:    pQid      -  pointer of Queue id (0~3)
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_priToQueMap_get(uint32 priority, uint32 *pQid) 
{
    uint16 regValue;

    if ((priority > 3) || (NULL == pQid)){
        return FALSE;
    }
    rtl8306e_reg_get(1, 22, 3, &regValue);   
    switch(priority) 
    {
        case 0:
            *pQid = regValue & 0x3;
            break;
        case 1:
            *pQid = (regValue & 0xC) >> 2;
            break;
        case 2:
            *pQid = (regValue & 0x30) >> 4;
            break;
        case 3:
            *pQid = (regValue & 0xC0) >> 6;
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_portRate_set
** Descriptions:         设置端口带宽速率控制
** input parameters:     port            -  port number (0~5)
				         n64Kbps       -  Port rate (0~1526), unit 64Kbps
				         direction      -  Ingress or Egress bandwidth control
				         enabled       -  enable bandwidth control				 					 		
** output parameters:    none
** Note:				 每个端口，都需要输入和输出带宽控制
						 RTL8306_PORT_RX represents port input bandwidth control, 
				      	 RTL8306_PORT_TX represents port output bandwidth control.
				         端口速率单位是64Kbps. For output rate control, enable/disable 
				         is configured per port, but for input rate control, it is for all port.
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_portRate_set(uint32 port, uint32 n64Kbps, uint32 direction, uint32 enabled)
{
    uint16 regValue;    
    if ((port > RTL8306_PORT5) || (n64Kbps > 0x5F6) || (direction > 1)){
        return FALSE;
    }    
    if (RTL8306_PORT5 == port) {/*Port 5 corresponding PHY6*/ 
        port ++ ;  
    }
    if (RTL8306_PORT_RX == direction) 
    {          
        if (!enabled ) 
        {			   /*configure port Rx rate*/
            rtl8306e_regbit_set(0, 21, 15, 3, 1);
        } 
        else 
        {
            rtl8306e_regbit_set(0, 21, 15, 3, 0);
            rtl8306e_reg_get(port, 21, 2, &regValue);
            regValue = (regValue & 0xF800) | (n64Kbps & 0x7FF);
            rtl8306e_reg_set(port, 21, 2, regValue);
        }
    } 
    else 
    {         
        if (!enabled) 
        {								 /*configure port Tx rate*/
            rtl8306e_regbit_set(port, 18, 15, 2, 0);
        } 
        else 
        {
            rtl8306e_regbit_set(port, 18, 15, 2, 1);
            rtl8306e_reg_get(port, 18, 2, &regValue);
            regValue = (regValue & 0xF800) | (n64Kbps & 0x7FF);
            rtl8306e_reg_set(port, 18, 2, regValue);
        }
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_portRate_get
** Descriptions:         读端口带宽速率控制
** input parameters:     port              port number (0~5)				 					 		
** output parameters:    *pN64Kbps         Port rate (0~1526), unit 64Kbps
				         direction         Input or output bandwidth control
				         *enabled          enabled or disabled bandwidth control
** Note:				 每个端口，都需要输入和输出带宽控制
						 RTL8306_PORT_RX represents port input bandwidth control, 
				      	 RTL8306_PORT_TX represents port output bandwidth control.
				         端口速率单位是64Kbps. For output rate control, enable/disable 
				         is configured per port, but for input rate control, it is for all port.
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_portRate_get(uint32 port, uint32 *pN64Kbps, uint32 direction, uint32 *pEnabled) 
{
    uint32 regValue;
	uint16 value = 0;
    if ((port > RTL8306_PORT5) || (NULL == pN64Kbps) || (direction > RTL8306_PORT_TX) || (NULL == pEnabled)){
        return FALSE;
    }
    
    if (RTL8306_PORT5 == port){  /*Port 5 corresponding PHY6*/
        port ++ ;  
	}
    if (RTL8306_PORT_RX == direction)
    {				 /*Get port Rx rate*/       
        rtl8306e_regbit_get(0, 21, 15, 3, &regValue);
        *pEnabled = (regValue ? FALSE:TRUE);
        rtl8306e_reg_get(port, 21, 2, &value);
        *pN64Kbps = value & 0x7FF;
    } 
    else 
    { 	 /*Get port Tx rate*/        
        rtl8306e_regbit_get(port, 18, 15, 2, pEnabled);
        rtl8306e_reg_get(port, 18, 2, &value);
        *pN64Kbps = value & 0x7FF;
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_1pRemarkEnable_set
** Descriptions:         Set 802.1P remarking ability(使能802.1P)
** input parameters:     port              port number (0~5)
				 		 enabled           TRUE or FALSE			 		
** output parameters:    none
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_1pRemarkEnable_set(uint32 port, uint32 enabled)
{
    if (port > RTL8306_PORT5){
        return FALSE;
    }    
    if (RTL8306_PORT5 == port){ /*Port 5 corresponding PHY6*/ 
        port ++ ;
	}    
    rtl8306e_regbit_set(0, 28, 13, 3, 1); /*enable new 1p remarking function*/
    rtl8306e_regbit_set(port, 17, 0, 2, enabled ? 1:0);
#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.vlanConfig_perport[port].en1PRemark= (uint8) enabled;
#endif    
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_1pRemarkEnable_get
** Descriptions:         get 802.1P remarking ability(读802.1P使能状态)
** input parameters:     port              port number (0~5)		 		
** output parameters:    pEnabled          pointer of the ability status
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_1pRemarkEnable_get(uint32 port, uint32 *pEnabled) 
{
    uint32 bitValue;    
    if (port > RTL8306_PORT5 || (NULL == pEnabled)){
        return FALSE;
    }
    
    if (RTL8306_PORT5 == port){  /*Port 5 corresponding PHY6*/
        port ++ ;
    }
    rtl8306e_regbit_get(port, 17, 0, 2, &bitValue);
    *pEnabled = (bitValue ? TRUE:FALSE);
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_1pRemark_set
** Descriptions:         设置802.1P优先级
** input parameters:     priority         Packet priority(0~4)
 				         priority1p       802.1P priority(0~7)		 		
** output parameters:    none
** Note:				 switch determines packet priority, the priority souce could
       					 be port-based, 1Q-based, dscp-based, vid-based, ip address,cpu tag.       
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_1pRemark_set(uint32 priority, uint32 priority1p)
{
    uint16 regValue;
    if ( (priority > 3) || (priority1p > 0x7) ){ 
        return FALSE;
    }
    rtl8306e_reg_get(0, 24, 3, &regValue);
    switch(priority) 
    {
        case 0:
            regValue = (regValue & 0xFFF8) | priority1p;
            break;
        case 1:
            regValue = (regValue & 0xFFC7) | (priority1p << 3);
            break;
        case 2:
            regValue = (regValue & 0xFE3F) | (priority1p <<6);
            break;
        case 3:
            regValue = (regValue & 0xF1FF) | (priority1p <<9);
            break;
        default:
            return FALSE;
    }    
    rtl8306e_reg_set(0, 24, 3, regValue);
#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.dot1PremarkCtl[priority] = (uint8) priority1p;
#endif
    
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_1pRemark_get
** Descriptions:         读取802.1P优先级
** input parameters:     priority         Packet priority(0~4)	 		
** output parameters:    pPriority1p      the pointer of 802.1P priority(0~7)
** Note:				 switch determines packet priority, the priority souce could
       					 be port-based, 1Q-based, dscp-based, vid-based, ip address,cpu tag.       
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_1pRemark_get(uint32 priority, uint32 *pPriority1p) 
{
    uint16 regValue;
    if ( (priority > 3) || (NULL == pPriority1p) ){ 
        return FALSE;
    }
    rtl8306e_reg_get(0, 24, 3, &regValue);
    switch(priority)
    {
        case 0:
            *pPriority1p = (regValue & 0x7);
            break;
        case 1:
            *pPriority1p = (regValue & 0x0038) >> 3;
            break;
        case 2:
            *pPriority1p = (regValue & 0x01C0) >> 6;
            break;
        case 3:
            *pPriority1p = (regValue & 0x0E00) >> 9;
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_portPri_set
** Descriptions:         设置端口优先级
** input parameters:     port            port number (0~5)
 				         priority        Packet port-based priority(0~3)	 		
** output parameters:    none
** Note:				 packet will be assigned a port-based priority correspond to the ingress port      
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_portPri_set(uint32 port, uint32 priority)
{
    uint16 regValue;

    if ((port > RTL8306_PORT5) ||(priority > 3)){
        return FALSE;
    }    
    if (RTL8306_PORT5 == port){  /*Port 5 corresponding PHY6*/
        port ++ ;  
    }
    rtl8306e_reg_get(port, 17, 2, &regValue);
    regValue = (regValue & 0xE7FF) | (priority << 11);
    rtl8306e_reg_set(port, 17, 2, regValue);    
    return TRUE;
}

/*********************************************************************************************************
** Function name:   	 rtl8306e_qos_portPri_get
** Descriptions:         读取端口优先级
** input parameters:     port            port number (0~5)	 		
** output parameters:    pPriority       pointer of packet port-based priority(0~4)
** Note:				 packet will be assigned a port-based priority correspond to the ingress port      
** Returned value:       成功或失败    
** Created by:			                                          
** Created Date:		                                           
**--------------------------------------------------------------------------------------------------------
** Modified by:			Wang ying                                             
** Modified date:		2010-12-21 	                                            
** Descriptions:		           
**********************************************************************************************************/
uint32 rtl8306e_qos_portPri_get(uint32 port, uint32 *pPriority) 
{
    uint16 regValue;
    if ((port > RTL8306_PORT5) ||(NULL == pPriority)){
        return FALSE;
    }
    if (port < RTL8306_PORT5){ 
        rtl8306e_reg_get(port, 17, 2, &regValue);
	}
    else{
        rtl8306e_reg_get(6, 17, 2, &regValue);
    }
    *pPriority = (regValue & 0x1800) >> 11;
    return TRUE;
}

/* Function Name:
 *      rtl8306e_qos_1pPriRemap_set
 * Description:
 *      Set Asic 1Q-tag priority mapping to 2-bit priority
 * Input:
 *      tagprio  -  1Q-tag proirty (0~7, 3 bit value)
 *      prio      -   internal use 2-bit priority
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      switch internal use 2-bit priority, so it should map 3-bit 1Q-tag priority
 *      to 2-bit priority
 */ 
uint32 rtl8306e_qos_1pPriRemap_set(uint32 tagprio, uint32 prio) 
{
    uint16 regValue;

    if ((tagprio > RTL8306_1QTAG_PRIO7) || (prio > RTL8306_PRIO3 ))
        return FALSE;
    
    rtl8306e_reg_get(2, 24, 3, &regValue);
    switch(tagprio) 
    {
        case RTL8306_1QTAG_PRIO0:
            regValue = (regValue & 0xFFFC) | prio;
            break;
        case RTL8306_1QTAG_PRIO1:
            regValue = (regValue & 0xFFF3) |(prio << 2);
            break;
        case RTL8306_1QTAG_PRIO2:
            regValue = (regValue & 0xFFCF) | (prio << 4);
            break;
        case RTL8306_1QTAG_PRIO3:
            regValue = (regValue & 0xFF3F) | (prio << 6);
            break;
        case RTL8306_1QTAG_PRIO4:
            regValue = (regValue & 0xFCFF) | (prio << 8);
            break;
        case RTL8306_1QTAG_PRIO5:
            regValue = (regValue & 0xF3FF) | (prio << 10);
            break;
        case RTL8306_1QTAG_PRIO6:
            regValue = (regValue & 0xCFFF) | (prio << 12);
            break;
        case RTL8306_1QTAG_PRIO7:
            regValue = (regValue & 0x3FFF) | (prio << 14);
            break;
        default:
            return FALSE;
    }    

    rtl8306e_reg_set(2, 24, 3, regValue);    
    return TRUE;
}

/* Function Name:
 *      rtl8306e_qos_1pPriRemap_get
 * Description:
 *      Get Asic 1Q-tag priority mapping to 2-bit priority
 * Input:
 *      tagprio  -  1Q-tag proirty (0~7, 3 bit value)
 * Output:
 *      pPrio     -  pointer of  internal use 2-bit priority
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      switch internal use 2-bit priority, so it should map 3-bit 1Q-tag priority
 *      to 2-bit priority
 */ 
uint32 rtl8306e_qos_1pPriRemap_get(uint32 tagprio, uint32 *pPrio) 
{
    uint16 regValue;
    
    if ((tagprio > RTL8306_1QTAG_PRIO7) || (NULL == pPrio))
        return FALSE;
    
    rtl8306e_reg_get(2, 24, 3, &regValue);
    switch(tagprio) 
    {
        case RTL8306_1QTAG_PRIO0:
            *pPrio = regValue & 0x3;
            break;
        case RTL8306_1QTAG_PRIO1:
            *pPrio = (regValue & 0xC) >> 2;
            break;
        case RTL8306_1QTAG_PRIO2:
            *pPrio = (regValue & 0x30) >> 4;
            break;
        case RTL8306_1QTAG_PRIO3:
            *pPrio = (regValue & 0xC0) >> 6;
            break;
        case RTL8306_1QTAG_PRIO4:
            *pPrio = (regValue & 0x300) >> 8;
            break;
        case RTL8306_1QTAG_PRIO5:
            *pPrio = (regValue & 0xC00) >> 10;
            break;
        case RTL8306_1QTAG_PRIO6:
            *pPrio = (regValue & 0x3000) >> 12;
            break;
        case RTL8306_1QTAG_PRIO7:
            *pPrio = (regValue & 0xC000) >> 14;
            break;
        default:
            return FALSE;
    }

    return TRUE;
}

/* Function Name:
 *      rtl8306e_dscpPriRemap_set
 * Description:
 *      Set DSCP-based priority
 * Input:
 *      code      -  dscp code
 *      priority   -  dscp-based priority
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      switch support 16 kinds of dscp code:
 *          RTL8306_DSCP_EF          
 *                 - DSCP for the Expedited forwarding PHB, 101110   
 *          RTL8306_DSCP_AFL1         
 *                 - DSCP for AF PHB Class 1 low drop, 001010
 *          RTL8306_DSCP_AFM1     
 *                 - DSCP for AF PHB Class 1 medium drop, 001100
 *          RTL8306_DSCP_AFH1      
 *                 - DSCP for AF PHB Class 1 high drop, 001110
 *          RTL8306_DSCP_AFL2       
 *                 - DSCP for AF PHB Class 2 low drop, 01001
 *          RTL8306_DSCP_AFM2       
 *                 - DSCP for AF PHB Class 2 medium drop, 010100
 *          RTL8306_DSCP_AFH2   
 *                 - DSCP for AF PHB Class 2 high drop, 010110
 *          RTL8306_DSCP_AFL3    
 *                 - DSCP for AF PHB Class 3 low drop, 011010
 *          RTL8306_DSCP_AFM3      
 *                 - DSCP for AF PHB Class 3 medium drop, 011100
 *          RTL8306_DSCP_AFH3    
 *                 - DSCP for AF PHB Class 3 high drop, 0111
 *          RTL8306_DSCP_AFL4     
 *                 - DSCP for AF PHB Class 4 low drop, 100010
 *          RTL8306_DSCP_AFM4    
 *                 - DSCP for AF PHB Class 4 medium drop, 100100
 *          RTL8306_DSCP_AFH4     
 *                 - DSCP for AF PHB Class 4 high drop, 100110
 *          RTL8306_DSCP_NC        
 *                 - DSCP for network control, 110000 or 111000
 *          RTL8306_DSCP_REG_PRI 
 *                 - DSCP Register match priority, user could define two dscp code
 *          RTL8306_DSCP_BF        
 *                 - DSCP Default PHB
 *     
 */ 
uint32 rtl8306e_qos_dscpPriRemap_set(uint32 code, uint32 priority) 
{
    uint16 regValue1, regValue2;

    if ((code > RTL8306_DSCP_BF) ||(priority > RTL8306_PRIO3))
        return FALSE;

    rtl8306e_reg_get(1, 23, 3, &regValue1);
    rtl8306e_reg_get(1, 24, 3, &regValue2);
    switch(code) 
    {
        case RTL8306_DSCP_EF:
            regValue1 = (regValue1 & 0xFFFC) | priority;
            rtl8306e_reg_set(1, 23, 3, regValue1);
            break;            
        case RTL8306_DSCP_AFL1:
            regValue1 = (regValue1 & 0xFFF3) | (priority << 2);
            rtl8306e_reg_set(1, 23, 3, regValue1);
            break;
        case RTL8306_DSCP_AFM1:
            regValue1 = (regValue1 & 0xFFCF) | (priority << 4);
            rtl8306e_reg_set(1, 23, 3, regValue1);
            break;
        case RTL8306_DSCP_AFH1:
            regValue1 = (regValue1 & 0xFF3F) | (priority << 6);
            rtl8306e_reg_set(1, 23, 3, regValue1);
            break;
        case RTL8306_DSCP_AFL2:
            regValue1 = (regValue1 & 0xFCFF) | (priority << 8);
            rtl8306e_reg_set(1, 23, 3, regValue1);
            break;
        case RTL8306_DSCP_AFM2:
            regValue1 = (regValue1 & 0xF3FF) | (priority << 10);
            rtl8306e_reg_set(1, 23, 3, regValue1);
            break;
        case RTL8306_DSCP_AFH2:
            regValue1 = (regValue1 & 0xCFFF) |(priority << 12);
            rtl8306e_reg_set(1, 23, 3, regValue1);
            break;
        case RTL8306_DSCP_AFL3:
            regValue1 = (regValue1 & 0x3FFF) | (priority << 14);
            rtl8306e_reg_set(1, 23, 3, regValue1);
            break;
        case RTL8306_DSCP_AFM3:
            regValue2 = (regValue2 & 0xFFFC) | priority;
            rtl8306e_reg_set(1, 24, 3, regValue2);
            break;
        case RTL8306_DSCP_AFH3:
            regValue2 = (regValue2 & 0xFFF3) | (priority <<2);
            rtl8306e_reg_set(1, 24, 3, regValue2);
            break;
        case RTL8306_DSCP_AFL4:
            regValue2 = (regValue2 & 0xFFCF) | (priority <<4);
            rtl8306e_reg_set(1, 24, 3, regValue2);
            break;
        case RTL8306_DSCP_AFM4:
            regValue2 = (regValue2 & 0xFF3F) | (priority << 6);
            rtl8306e_reg_set(1, 24, 3, regValue2);
            break;
        case RTL8306_DSCP_AFH4:
            regValue2 = (regValue2 & 0xFCFF) | (priority << 8);
            rtl8306e_reg_set(1, 24, 3, regValue2);
            break;
        case RTL8306_DSCP_NC:
            regValue2 = (regValue2 & 0xF3FF) | (priority << 10);
            rtl8306e_reg_set(1, 24, 3, regValue2);
            break;
        case RTL8306_DSCP_REG_PRI:
            regValue2 = (regValue2 & 0xCFFF) | (priority << 12);
            rtl8306e_reg_set(1, 24, 3, regValue2);
            break;
        case RTL8306_DSCP_BF:
            regValue2 = (regValue2 & 0x3FFF) | (priority << 14);
            rtl8306e_reg_set(1, 24, 3, regValue2);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}


/* Function Name:
 *      rtl8306e_dscpPriRemap_set
 * Description:
 *      Get DSCP-based priority
 * Input:
 *      code      -  dscp code
 * Output:
 *      pPriority  -  the pointer of dscp-based priority
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      switch support 16 kinds of dscp code:
 *          RTL8306_DSCP_EF          
 *                 - DSCP for the Expedited forwarding PHB, 101110   
 *          RTL8306_DSCP_AFL1         
 *                 - DSCP for AF PHB Class 1 low drop, 001010
 *          RTL8306_DSCP_AFM1     
 *                 - DSCP for AF PHB Class 1 medium drop, 001100
 *          RTL8306_DSCP_AFH1      
 *                 - DSCP for AF PHB Class 1 high drop, 001110
 *          RTL8306_DSCP_AFL2       
 *                 - DSCP for AF PHB Class 2 low drop, 01001
 *          RTL8306_DSCP_AFM2       
 *                 - DSCP for AF PHB Class 2 medium drop, 010100
 *          RTL8306_DSCP_AFH2   
 *                 - DSCP for AF PHB Class 2 high drop, 010110
 *          RTL8306_DSCP_AFL3    
 *                 - DSCP for AF PHB Class 3 low drop, 011010
 *          RTL8306_DSCP_AFM3      
 *                 - DSCP for AF PHB Class 3 medium drop, 011100
 *          RTL8306_DSCP_AFH3    
 *                 - DSCP for AF PHB Class 3 high drop, 0111
 *          RTL8306_DSCP_AFL4     
 *                 - DSCP for AF PHB Class 4 low drop, 100010
 *          RTL8306_DSCP_AFM4    
 *                 - DSCP for AF PHB Class 4 medium drop, 100100
 *          RTL8306_DSCP_AFH4     
 *                 - DSCP for AF PHB Class 4 high drop, 100110
 *          RTL8306_DSCP_NC        
 *                 - DSCP for network control, 110000 or 111000
 *          RTL8306_DSCP_REG_PRI 
 *                 - DSCP Register match priority, user could define two dscp code
 *          RTL8306_DSCP_BF        
 *                 - DSCP Default PHB
 *     
 */ 
uint32 rtl8306e_qos_dscpPriRemap_get(uint32 code, uint32 *pPriority) 
{
    uint16  regValue1, regValue2;

    if ((code > RTL8306_DSCP_BF) || (NULL == pPriority))
        return FALSE;
    
    rtl8306e_reg_get(1, 23, 3, &regValue1);
    rtl8306e_reg_get(1, 24, 3, &regValue2);
    switch(code) 
    {
        case RTL8306_DSCP_EF:
            *pPriority = regValue1 & 0x3;
            break;
        case RTL8306_DSCP_AFL1:
            *pPriority = (regValue1 & 0xC)  >> 2;
            break;
        case RTL8306_DSCP_AFM1:
            *pPriority = (regValue1 & 0x30) >> 4;
            break;
        case RTL8306_DSCP_AFH1:
            *pPriority = (regValue1 & 0xC0) >> 6;
            break;
        case RTL8306_DSCP_AFL2:
            *pPriority = (regValue1 & 0x300) >> 8;
            break;
        case RTL8306_DSCP_AFM2:
            *pPriority = (regValue1 & 0xC00) >> 10;
            break;
        case RTL8306_DSCP_AFH2:
            *pPriority = (regValue1 & 0x3000) >> 12;
            break;
        case RTL8306_DSCP_AFL3:
            *pPriority = (regValue1 & 0xC000) >> 14;
            break;
        case RTL8306_DSCP_AFM3:
            *pPriority = regValue2 & 0x3;
            break;
        case RTL8306_DSCP_AFH3:
            *pPriority = (regValue2 & 0xC) >> 2;
            break;
        case RTL8306_DSCP_AFL4:
            *pPriority = (regValue2 & 0x30) >> 4;
            break;
        case RTL8306_DSCP_AFM4:
            *pPriority = (regValue2 & 0xC0) >> 6;
            break;
        case RTL8306_DSCP_AFH4:
            *pPriority = (regValue2 & 0x300) >> 8;
            break;
        case RTL8306_DSCP_NC:
            *pPriority = (regValue2 & 0xC00) >>10;
            break;
        case RTL8306_DSCP_REG_PRI:
            *pPriority = (regValue2 & 0x3000) >> 12;
            break;
        case RTL8306_DSCP_BF:
            *pPriority = (regValue2 & 0xC000) >> 14;
            break;
        default:
            return FALSE;
    }

    return TRUE;
} 


/* Function Name:
 *      rtl8306e_qos_priSrcArbit_set
 * Description:
 *      Set priority source arbitration level
 * Input:
 *      priArbit  - The structure describe levels of 5 kinds of priority 
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      switch could recognize 7 types of priority source at most, 
 *      and a packet properly has all of them. among them, there 
 *      are 5 type priorities could be set priority level, they are 
 *      ACL-based  priority, DSCP-based priority, 1Q-based priority,
 *      Port-based priority, VID- based priority.each one could be 
 *      set level from 0 to 5, arbitration module will decide their sequece 
 *      to take, the highest level priority will be adopted at first, 
 *      then  priority type of the sencond highest level. priority with level 0
 *      will not be recognized any more. 
 */

uint32 rtl8306e_qos_priSrcArbit_set(rtl8306e_qosPriArbitPara_t priArbit) 
{
    uint16 regval;

    if ((priArbit.acl_pri_lev > 5) || (priArbit.dscp_pri_lev > 5) ||
        (priArbit.dot1q_pri_lev > 5)   || (priArbit.port_pri_lev > 5)  ||
        (priArbit.vid_pri_lev > 5))
        return FALSE;
    
    /*vid based priority selection*/
    rtl8306e_reg_get(0, 28, 3, &regval);
    regval &= ~(0x1F << 8);
    if (priArbit.vid_pri_lev)
        regval |= (1 << (priArbit.vid_pri_lev -1 + 8));
    rtl8306e_reg_set(0, 28, 3, regval);

    /*acl based priority*/
    rtl8306e_reg_get(1, 21, 3, &regval);
    regval &= ~(0xF << 12);
    rtl8306e_reg_set(1, 21, 3, regval);    
    rtl8306e_regbit_set(0, 28, 7, 3, 0);
    if (5 == priArbit.acl_pri_lev)
    {
        rtl8306e_regbit_set(0, 28, 7, 3, 1);
    }
    else if (priArbit.acl_pri_lev > 0)
    {
        rtl8306e_reg_get(1, 21, 3, &regval); 
        regval |= (1 << (priArbit.acl_pri_lev -1 + 12));
        rtl8306e_reg_set(1, 21, 3, regval);
    }
        
    /*dscp based priority*/
    rtl8306e_reg_get(1, 21, 3, &regval);
    regval &= ~(0xF << 8);
    rtl8306e_reg_set(1, 21, 3, regval);    
    rtl8306e_regbit_set(0, 26, 15, 3, 0);
    if (5 == priArbit.dscp_pri_lev)
    {
        rtl8306e_regbit_set(0, 26, 15, 3, 1);
    }
    else if (priArbit.dscp_pri_lev > 0)
    {
        rtl8306e_reg_get(1, 21, 3, &regval);
        regval |= (1 << (priArbit.dscp_pri_lev -1 + 8));
        rtl8306e_reg_set(1, 21, 3, regval);
    }
    
    /*1Q based priority*/
    rtl8306e_reg_get(1, 21, 3, &regval);
    regval &= ~(0xF << 4);
    rtl8306e_reg_set(1, 21, 3, regval);
    rtl8306e_regbit_set(0, 26, 14, 3, 0);
    if (5 == priArbit.dot1q_pri_lev)
    {
        rtl8306e_regbit_set(0, 26, 14, 3, 1);                    
    }
    else if (priArbit.dot1q_pri_lev > 0)
    {
        rtl8306e_reg_get(1, 21, 3, &regval);        
        regval |= ( 1 << (priArbit.dot1q_pri_lev -1 + 4));
        rtl8306e_reg_set(1, 21, 3, regval);
    }

    /*port based priority*/
    rtl8306e_reg_get(1, 21, 3, &regval);
    regval &= ~0xF;
    rtl8306e_reg_set(1, 21, 3, regval);
    rtl8306e_regbit_set(0, 26, 13, 3, 0);
    if (5 == priArbit.port_pri_lev)
    {
        rtl8306e_regbit_set(0, 26, 13, 3, 1);        
    }
    else if (priArbit.port_pri_lev > 0)
    {
        rtl8306e_reg_get(1, 21, 3, &regval); 
        regval |= (1 << (priArbit.port_pri_lev -1));
        rtl8306e_reg_set(1, 21, 3, regval);
    }
    
    return TRUE;
}


/* Function Name:
 *      rtl8306e_qos_priSrcArbit_get
 * Description:
 *      Get priority source arbitration level
 * Input:
 *      none 
 * Output:
 *      pPriArbit  - The structure describe levels of 5 kinds of priority 
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      switch could recognize 7 types of priority source at most, 
 *      and a packet properly has all of them. among them, there 
 *      are 5 type priorities could be set priority level, they are 
 *      ACL-based  priority, DSCP-based priority, 1Q-based priority,
 *      Port-based priority, VID- based priority.each one could be 
 *      set level from 0 to 5, arbitration module will decide their sequece 
 *      to take, the highest level priority will be adopted at first, 
 *      then  priority type of the sencond highest level. priority with level 0
 *      will not be recognized any more. 
 */
uint32 rtl8306e_qos_priSrcArbit_get(rtl8306e_qosPriArbitPara_t *pPriArbit)
{
    uint16 regval;
    uint32 i ;
	uint32 flagRegVal = 0;
        
    if (NULL == pPriArbit)
        return FALSE;

    pPriArbit ->acl_pri_lev = 0;
    pPriArbit ->dot1q_pri_lev = 0;
    pPriArbit ->dscp_pri_lev = 0;
    pPriArbit ->port_pri_lev = 0;
    pPriArbit ->vid_pri_lev = 0;

    /*vid based priority selection*/
    rtl8306e_reg_get(0, 28, 3, &regval);
    regval &= (0x1F << 8);
    regval >>= 8;
    for (i = 5; i > 0; i --)
    {
        if(regval >> (i-1))
        {
            pPriArbit ->vid_pri_lev = i;
            break;
        }
    }

    /*acl based priority*/
    rtl8306e_regbit_get(0, 28, 7, 3, &flagRegVal);
    if(flagRegVal)
    {
        pPriArbit->acl_pri_lev = 5;
    }
    else
    {
        rtl8306e_reg_get(1, 21, 3, &regval);
        regval &= (0xF << 12);
        regval >>= 12;
        for (i = 4; i > 0; i --)
        {
            if(regval >> (i-1))
            {
                pPriArbit ->acl_pri_lev = i;
                break;
            }
        }        
    }

    /*dscp based priority*/
    rtl8306e_regbit_get(0, 26, 15, 3, &flagRegVal);
    if (flagRegVal)
    {
        pPriArbit ->dscp_pri_lev = 5;
    }
    else
    {
        rtl8306e_reg_get(1, 21, 3, &regval);
        regval &= (0xF << 8);
        regval >>= 8;
        for (i = 4; i > 0; i --)
        {
            if(regval >> (i-1))
            {
                pPriArbit ->dscp_pri_lev =  i;
                break;
            }
        }                
    }

    /*1Q based priority*/
    rtl8306e_regbit_get(0, 26, 14, 3, &flagRegVal);
    if (flagRegVal)
    {
        pPriArbit ->dot1q_pri_lev = 5;
    }
    else
    {
        rtl8306e_reg_get(1, 21, 3, &regval);
        regval &= (0xF << 4);
        regval >>= 4;
        for (i = 4; i > 0; i --)
        {
            if(regval >> (i-1))
            {
                pPriArbit ->dot1q_pri_lev = i;
                break;
            }
        }                        
    }

    /*port based priority*/
    rtl8306e_regbit_get(0, 26, 13, 3, &flagRegVal);
    if (flagRegVal)
    {
        pPriArbit ->port_pri_lev = 5;
    }
    else 
    {
        rtl8306e_reg_get(1, 21, 3, &regval);
        regval &= 0xF;

        for (i = 4; i > 0; i --)
        {
            if(regval >> (i-1))
            {
                pPriArbit ->port_pri_lev = i;
                break;
            }
        }                                
    }
        
    return TRUE;
}

/* Function Name:
 *      rtl8306e_qos_priSrcEnable_set
 * Description:
 *      enable/disable Qos priority source for ingress port
 * Input:
 *      port      -  Specify port number (0 ~5)
 *      priSrc    -  Specify priority source  
 *      enabled -   TRUE of FALSE  
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *     There are 4 kind of priority source for each port which could
 *     be enabled ordisabled:
 *          RTL8306_DSCP_PRIO     - DSCP-based priority
 *          RTL8306_1QBP_PRIO     - 1Q-based priority
 *          RTL8306_PBP_PRIO        - port-based priority
 *          RTL8306_CPUTAG_PRIO  - cpu tag priority
 */
uint32 rtl8306e_qos_priSrcEnable_set(uint32 port, uint32 priSrc, uint32 enabled) 
{
    uint32 duplex, speed, nway;
      
    if (port > RTL8306_PORT5)
        return FALSE;

    duplex = 0;
    speed = 0;
    nway = 0;
    
    /*save mac 4 or port status when operate reg.22*/    
    if (4 == port) 
    {
        rtl8306e_regbit_get(5, 0, 13, 0, &speed);
        rtl8306e_regbit_get(5, 0, 12, 0, &nway);
        rtl8306e_regbit_get(5, 0, 8, 0, &duplex);            
    } 
    else if (5 == port) 
    {
        rtl8306e_regbit_get(6, 0, 13, 0, &speed);
        rtl8306e_regbit_get(6, 0, 12, 0, &nway);
        rtl8306e_regbit_get(6, 0, 8, 0, &duplex);            
    }

    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ;  
    
    switch(priSrc) 
    {
        case RTL8306_DSCP_PRIO:
            rtl8306e_regbit_set(port, 22, 9, 0, enabled ? 0:1);
            break;
        case RTL8306_1QBP_PRIO:
            rtl8306e_regbit_set(port, 22, 10, 0, enabled ? 0:1);
            break;
        case RTL8306_PBP_PRIO:
            rtl8306e_regbit_set(port, 22, 8, 0, enabled ? 0:1);
            break;
        case RTL8306_CPUTAG_PRIO:
            rtl8306e_regbit_set(port, 17, 1, 2, enabled ? 1:0);
            break;
        default:
            return FALSE;
    }
    
    /*restore mac 4 or port status when operate reg.22*/    
    if (4 == port) 
    {
        rtl8306e_regbit_set(5, 0, 13, 0, speed);
        rtl8306e_regbit_set(5, 0, 12, 0, nway);
        rtl8306e_regbit_set(5, 0, 8, 0, duplex);            
    }
    else if (6 == port) 
    { 
        /*for port++ when port 5*/
        rtl8306e_regbit_set(6, 0, 13, 0, speed);
        rtl8306e_regbit_set(6, 0, 12, 0, nway);
        rtl8306e_regbit_set(6, 0, 8, 0, duplex);
    }      
    return TRUE;
}


/* Function Name:
 *      rtl8306e_qos_priSrcEnable_get
 * Description:
 *      enable/disable Qos priority source for  ingress port
 * Input:
 *      port       -  Specify port number (0 ~5)
 *      priSrc     -  Specify priority source  
 * Output:
 *      pEnabled -  the pointer of priority source status  
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *     There are 4 kind of priority source for each port which could
 *     be enabled ordisabled:
 *          RTL8306_DSCP_PRIO     - DSCP-based priority
 *          RTL8306_1QBP_PRIO     - 1Q-based priority
 *          RTL8306_PBP_PRIO        - port-based priority
 *          RTL8306_CPUTAG_PRIO  - cpu tag priority
 */
uint32 rtl8306e_qos_priSrcEnable_get(uint32 port, uint32 priSrc, uint32 *pEnabled) 
{
    uint32 bitValue;

    if ((port > RTL8306_PORT5) || (NULL == pEnabled))
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (port == RTL8306_PORT5 )  
        port ++ ;  
    
    switch(priSrc)
    {
        case RTL8306_DSCP_PRIO:
            rtl8306e_regbit_get(port, 22, 9, 0, &bitValue);
            *pEnabled = (bitValue ? FALSE : TRUE);
            break;
        case RTL8306_1QBP_PRIO:
            rtl8306e_regbit_get(port, 22, 10, 0, &bitValue);
            *pEnabled = (bitValue ? FALSE : TRUE);
            break;
        case RTL8306_PBP_PRIO:
            rtl8306e_regbit_get(port, 22, 8, 0, &bitValue);
            *pEnabled = (bitValue ? FALSE : TRUE);
            break;
        case RTL8306_CPUTAG_PRIO:
            rtl8306e_regbit_get(port, 17, 1, 2, &bitValue);
            *pEnabled = (bitValue ? TRUE : FALSE);
            break;
        default:
            return FALSE;
    }

    return TRUE;
}


/* Function Name:
 *      rtl8306e_qos_ipAddrPri_set
 * Description:
 *      Set IP address priority
 * Input:
 *      priority  -  internal use 2-bit priority value (0~3)  
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */
uint32 rtl8306e_qos_ipAddrPri_set(uint32 priority) 
{
    uint16 regValue;

    if (priority > 3)
        return FALSE;
    
    rtl8306e_reg_get(2, 22, 3, &regValue);
    rtl8306e_reg_set(2, 22, 3, (regValue & 0xFFFC) |priority);

    return TRUE;
}


/* Function Name:
 *      rtl8306e_qos_ipAddrPri_get
 * Description:
 *      Get IP address priority
 * Input:
 *      priority  -  internal use 2-bit priority value (0~3)  
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */
uint32 rtl8306e_qos_ipAddrPri_get(uint32 *priority)
{
    uint16 regValue;

    if (priority == NULL)
        return FALSE;
    
    rtl8306e_reg_get(2, 22, 3, &regValue);
    *priority =  regValue & 0x3;

    return TRUE;
}


/* Function Name:
 *      rtl8306e_qos_ipAddr_set
 * Description:
 *      Set IP address
 * Input:
 *      entry        -   specify entry
         ip            -   ip address
         mask        -  ip mask
         enabled    -   enable the entry
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      There are two entries RTL8306_IPADD_A and RTL8306_IPADD_B
 *      for user setting ip address, if ip address of packet matches
 *      the entry, the packet will be assign the priority of ip address
 *      priority which is configured by rtl8306e_qos_ipAddrPri_set.
 */
uint32 rtl8306e_qos_ipAddr_set(uint32 entry, uint32 ip, uint32 mask, uint32 enabled) 
{
    uint32 regValue;

    if (entry > 1) 
        return FALSE;

    switch(entry) 
    {
        case RTL8306_IPADD_A:        
            if (enabled == TRUE) 
            {
                rtl8306e_regbit_set(0, 17, 14, 0, 1);
                regValue = ip & 0xFFFF;
                rtl8306e_reg_set(1, 17, 0, regValue);
                regValue = (ip & 0xFFFF0000) >> 16;
                rtl8306e_reg_set(1, 16, 0, regValue);
                regValue = mask & 0xFFFF;
                rtl8306e_reg_set(2, 17, 0, regValue);
                regValue = (mask & 0xFFFF0000) >> 16;
                rtl8306e_reg_set(2, 16, 0, regValue);
            }    
            else 
                rtl8306e_regbit_set(0, 17, 14, 0, 0);
            break;
        case RTL8306_IPADD_B:        
            if (enabled == TRUE)
            {
                rtl8306e_regbit_set(0, 17, 6, 0, 1);
                regValue = ip & 0xFFFF;
                rtl8306e_reg_set(1, 19, 0, regValue);
                regValue = (ip & 0xFFFF0000) >> 16;
                rtl8306e_reg_set(1, 18, 0, regValue);
                regValue = mask & 0xFFFF;
                rtl8306e_reg_set(2, 19, 0, regValue);
                regValue = (mask & 0xFFFF0000) >> 16;
                rtl8306e_reg_set(2, 18, 0, regValue);
            }
            else 
                rtl8306e_regbit_set(0, 17, 6, 0, 0);        
            break;
        default:
            return FALSE;
    }

    return TRUE;
}


/* Function Name:
 *      rtl8306e_qos_ipAddr_get
 * Description:
 *      Get IP address user seting
 * Input:
 *      entry       -   specify entry
 * Output:
 *      pIp            -   ip address
         pMask        -   ip mask
         pEnabled    -  enabled or disabled the entry for IP Priority
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */
uint32 rtl8306e_qos_ipAddr_get(uint32 entry, uint32 *pIp, uint32 *pMask , uint32 *pEnabled) 
{
    uint16 hi, lo;
    uint32 bitValue;

    if ((entry > 1) || (pIp == NULL) || (pMask == NULL) || (pEnabled == NULL))
        return FALSE;
    
    switch (entry) 
    {
        case RTL8306_IPADD_A :
            rtl8306e_reg_get(1, 17, 0, &lo);
            rtl8306e_reg_get(1, 16, 0, &hi);
            *pIp = lo + (hi << 16);
            rtl8306e_reg_get(2, 17, 0, &lo);
            rtl8306e_reg_get(2, 16, 0, &hi);
            *pMask = lo + (hi << 16);
            rtl8306e_regbit_get(0, 17, 14, 0, &bitValue);
            *pEnabled = (bitValue == 1 ? TRUE : FALSE);
            break;
        case RTL8306_IPADD_B :
            rtl8306e_reg_get(1, 19, 0, &lo);
            rtl8306e_reg_get(1, 18, 0, &hi);
            *pIp = lo + (hi << 16);
            rtl8306e_reg_get(2, 19, 0, &lo);
            rtl8306e_reg_get(2, 18, 0, &hi);
            *pMask = lo + (hi << 16); 
            rtl8306e_regbit_get(0, 17, 6, 0, &bitValue);
            *pEnabled = (bitValue == 1 ? TRUE : FALSE);

            break;
        default :
            return FALSE;
    }

    
    return TRUE;
}


/* Function Name:
 *      rtl8306e_qos_schedulingPara_set
 * Description:
 *      Set qos scheduling parameter
 * Input:
 *      set          -  RTL8306_QOS_SET0 or RTL8306_QOS_SET1
 *      sch_para  -  The structure describe schedule parameter (描述表)
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      switch supports 4 queue per egress port, scheduling algorithm could be WRR(Weight Round Robin) or 
 *      SP(Strict Priority). Only high queue Q3 and Q2 could be set as strict priority queue. There two set of 
 *      scheduling parameter in whole system(RTL8306_QOS_SET0/RTL8306_QOS_SET1), each egress port select
 *      one of them. The parameter defined by rtl8306e_qosSchPara_t, q0_wt and q1_wt should between 1~127,
 *      that means Q0 and Q1 WRR weight, q2_wt and  q3_wt could be 0~127, 0 means strict priority. q2_n64Kbps 
 *      and q3_n64Kbps means Q2/Q3 queue bandwidth control, unit is 64Kbps.
 */
uint32 rtl8306e_qos_schedulingPara_set(uint32 set, rtl8306e_qosSchPara_t sch_para)
{
    uint16 regValue;
    if ((sch_para.q0_wt > 127) || (sch_para.q1_wt > 127) || (sch_para.q2_wt > 127) ||
         (sch_para.q3_wt > 127) || (0 == sch_para.q0_wt ) || (0 == sch_para.q1_wt)  ||
         (sch_para.q2_n64Kbps > 0x7FF) || (sch_para.q3_n64Kbps > 0x7FF))
         return FALSE;

    switch(set)
    {
        case RTL8306_QOS_SET0:   
            rtl8306e_reg_get(5, 20, 3, &regValue);
            regValue &= ~0x7F;
            regValue &= ~(0x7F << 8); 
            regValue |= (sch_para.q0_wt | (sch_para.q1_wt << 8));
            rtl8306e_reg_set(5, 20, 3, regValue);

            regValue = 0;
            regValue |=  (!sch_para.q3_wt) ? (1 << 15) :0;
            regValue |= (sch_para.q3_wt << 8);
            regValue |= (!sch_para.q2_wt) ? (1 << 7):0;
            regValue |= sch_para.q2_wt;
            rtl8306e_reg_set(5, 21, 3, regValue);
            
            rtl8306e_reg_get(5, 18, 3, &regValue);
            regValue &= ~0x7FF;
            regValue |= sch_para.q2_n64Kbps;
            rtl8306e_reg_set(5, 18, 3, regValue);
            
            rtl8306e_reg_get(5, 19, 3, &regValue);
            regValue &= ~0x7FF;
            regValue |= sch_para.q3_n64Kbps;
            rtl8306e_reg_set(5, 19, 3, regValue);                        
            break;

        case RTL8306_QOS_SET1:
            rtl8306e_reg_get(5, 25, 3, &regValue);
            regValue &= ~0x7F;
            regValue &= ~(0x7F << 8); 
            regValue |= (sch_para.q0_wt | (sch_para.q1_wt << 8));
            rtl8306e_reg_set(5, 25, 3, regValue);

            regValue = 0;
            regValue |=  (!sch_para.q3_wt) ? (1 << 15) :0;
            regValue |= (sch_para.q3_wt << 8);
            regValue |= (!sch_para.q2_wt) ? (1 << 7):0;
            regValue |= sch_para.q2_wt;
            rtl8306e_reg_set(5, 26, 3, regValue);

            rtl8306e_reg_get(5, 23, 3, &regValue);
            regValue &= ~0x7FF;
            regValue |= sch_para.q2_n64Kbps;
            rtl8306e_reg_set(5, 23, 3, regValue);

            rtl8306e_reg_get(5, 24, 3, &regValue);
            regValue &= ~0x7FF;
            regValue |= sch_para.q3_n64Kbps;
            rtl8306e_reg_set(5, 24, 3, regValue);                                                                       
            break;

         default:
            return FALSE;
    }
                    
    return TRUE;
}

/* Function Name:
 *      rtl8306e_qos_schedulingPara_get
 * Description:
 *      Set qos scheduling parameter
 * Input:
 *      set           -  RTL8306_QOS_SET0 or RTL8306_QOS_SET1
 * Output:
 *      pSch_para  - the pointer of schedule parameter
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      switch supports 4 queue per egress port, scheduling algorithm could be WRR(Weight Round Robin) or 
 *      SP(Strict Priority). Only high queue Q3 and Q3 could be set as strict priority queue. There two set of 
 *      scheduling parameter in whole system(RTL8306_QOS_SET0/RTL8306_QOS_SET1), each egress port select
 *      one of them. The parameter defined by rtl8306e_qosSchPara_t, q0_wt and q1_wt should between 1~127,
 *      that means Q0 and Q1 WRR weight, q2_wt and  q3_wt could be 0~127, 0 means strict priority. q2_n64Kbps 
 *      and q3_n64Kbps means Q2/Q3 queue bandwidth control, unit is 64Kbps.
 */
uint32 rtl8306e_qos_schedulingPara_get(uint32 set, rtl8306e_qosSchPara_t *pSch_para)
{
    uint16 regValue;
    
    if (NULL == pSch_para)
        return FALSE;

    switch(set)
    {
        case RTL8306_QOS_SET0:
            rtl8306e_reg_get(5, 20, 3, &regValue);            
            pSch_para->q0_wt = regValue & 0x7F;
            pSch_para->q1_wt = (regValue & (0x7F << 8)) >> 8;

            rtl8306e_reg_get(5, 21, 3, &regValue);
            pSch_para->q2_wt = regValue & 0x7F;
            pSch_para->q3_wt = (regValue & (0x7F << 8)) >> 8;
            if (regValue & (1 << 7))
            {
                pSch_para->q2_wt = 0;
            }
            
            if (regValue & (1 << 15))
            {
                pSch_para->q3_wt = 0;
            }

            rtl8306e_reg_get(5, 18, 3, &regValue);
            pSch_para->q2_n64Kbps = regValue & 0x7FF;
            rtl8306e_reg_get(5, 19, 3, &regValue);
            pSch_para->q3_n64Kbps = regValue & 0x7FF;
                        
            break;
            
        case RTL8306_QOS_SET1:
            rtl8306e_reg_get(5, 25, 3, &regValue);            
            pSch_para->q0_wt = regValue & 0x7F;
            pSch_para->q1_wt = (regValue & (0x7F << 8)) >> 8;
            
            rtl8306e_reg_get(5, 26, 3, &regValue);
            pSch_para->q2_wt = regValue & 0x7F;
            pSch_para->q3_wt = (regValue & (0x7F << 8)) >> 8;

            if (regValue & (1 << 7))
            {
                pSch_para->q2_wt = 0;
            }
            
            if (regValue & (1 << 15))
            {
                pSch_para->q3_wt = 0;
            }
            
            rtl8306e_reg_get(5, 23, 3, &regValue);
            pSch_para->q2_n64Kbps = regValue & 0x7FF;
            rtl8306e_reg_get(5, 24, 3, &regValue);
            pSch_para->q3_n64Kbps = regValue & 0x7FF;            
            
            break;
        default:
            return FALSE;
    }
    
    return TRUE;
}

/* Function Name:
 *      rtl8306e_qos_portSchedulingMode_set
 * Description:
 *      Select port schedule algorithm  from two sets.
 * Input:
 *      port    -   port number (0 ~ 5)
 *      set     -   RTL8306_QOS_SET0 or RTL8306_QOS_SET1
 *      lbmsk  -   Queue mask for enable queue leaky buckt
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      There are two sets configuration for schedule mode including strict priority 
 *      enable/disable, queue weight and queue leaky bucket, every port could select
 *      one of them. Queue leaky bucket of each port could be enable separately, so 
 *      you can set queue mask to enable/disable them, because only queue 3 and queue 2
 *      have leaky bucket, only bit 3 and bit 2 of quemask have effect, bit 3 represents
 *      queue 3 and set 1 to enable it.
 */
uint32 rtl8306e_qos_portSchedulingMode_set(uint32 port, uint32 set, uint32 lbmsk)
{
    uint16 regValue;
    
    if ((port > RTL8306_PORT5) ||(set > 1))
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ; 
    
    lbmsk = ((lbmsk & 0x8) >> 3 ) | ((lbmsk & 0x4) >> 1);
    rtl8306e_reg_get(port, 18, 2, &regValue);
    regValue = (regValue & 0x97FF) | (lbmsk << 13) | (set & 0x1) << 11;
    rtl8306e_reg_set(port, 18, 2, regValue);
    return TRUE;
}

/* Function Name:
 *      rtl8306e_qos_portSchedulingMode_get
 * Description:
 *      Get which set of schedule algorithm  for the specified port 
 * Input:
 *      port    -   port number (0 ~ 5)
 *      set     -   RTL8306_QOS_SET0 or RTL8306_QOS_SET1
 *      lbmsk  -   Queue mask for enable queue leaky buckt
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      There are two sets configuration for schedule mode including strict priority 
 *      enable/disable, queue weight and queue leaky bucket, every port could select
 *      one of them. Queue leaky bucket of each port could be enable separately, so 
 *      you can set queue mask to enable/disable them, because only queue 3 and queue 2
 *      have leaky bucket, only bit 3 and bit 2 of quemask have effect, bit 3 represents
 *      queue 3 and set 1 to enable it.
 */
uint32 rtl8306e_qos_portSchedulingMode_get(uint32 port, uint32 *pSet, uint32 *pLbmsk) 
{
    uint16 regValue;

    if ((port > RTL8306_PORT5) ||(NULL == pSet) || (NULL == pLbmsk))
        return FALSE;

    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ;  

    rtl8306e_reg_get(port, 18, 2, &regValue );
    *pSet = (regValue >> 11) & 0x1;
    *pLbmsk = (regValue >> 13) & 0x3;
    *pLbmsk = ((*pLbmsk & 0x1) << 3) | ((*pLbmsk & 0x2) << 1);
    
    return TRUE;
}


uint32 rtl8306e_qos_queFlcThr_set(uint32 queue, uint32 type, uint32 onoff, uint32 set, uint32 value)
{
    uint16 regValue;
	uint32 mask;
    uint32 selection;
    uint32 reg, shift;

    if ((queue > RTL8306_QUEUE3) || (type > RTL8306_FCO_QLEN) ||
        (onoff > RTL8306_FCON) || (set > RTL8306_FCO_SET1) || (value > 127))
        return FALSE;
    
    selection = (set << 2) | (onoff <<1) |type;
    value &= 0x7f;
    switch (selection) 
    {
        case 0 :  /*set 0, turn off, DSC*/
            if (RTL8306_QUEUE0 == queue)
            {
                reg = 17;
                mask = 0xFFF0;
                shift = 0;
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                reg = 17;
                mask = 0xF0FF;
                shift = 8;
            } 
            else if (RTL8306_QUEUE2 == queue) 
            {
                reg = 20;
                mask = 0xFFF0;
                shift = 0;
            } 
            else 
            {
                reg = 20;
                mask = 0xF0FF;
                shift = 8;
            }
            rtl8306e_reg_get(5, reg, 2, &regValue);
            regValue = (regValue & mask) | ((value & 0xf)  << shift);
            rtl8306e_reg_set(5, reg, 2, regValue);
        
             /*flc bit[6:4]*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);  
                regValue &= 0xfff8;
                regValue |= (value & 0x70) >> 4;
                rtl8306e_reg_set(1, 26, 3, regValue);                
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);  
                regValue &= 0xfe3f;
                regValue |= ((value & 0x70) >> 4) << 6;
                rtl8306e_reg_set(1, 26, 3, regValue);
            }
            else if (RTL8306_QUEUE2 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);  
                regValue &= 0x8fff;
                regValue |=   ((value & 0x70) >> 4) << 12;
                rtl8306e_reg_set(1, 26, 3, regValue);                
            } 
            else  
            {
                rtl8306e_reg_get(1, 27, 3, &regValue);  
                regValue &= 0xffe3;
                regValue |=   ((value & 0x70) >> 4) << 2;
                rtl8306e_reg_set(1, 27, 3, regValue);
            }             
            break;
        
        case 1 :     /*set 0, turn off, QLEN*/
            if (RTL8306_QUEUE0 == queue) 
            {
                reg = 17;
                mask = 0xFF0F;
                shift = 4;
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                reg = 17;
                mask = 0x0FFF;
                shift = 12;
            } 
            else if (RTL8306_QUEUE2 == queue) 
            {
                reg = 20;
                mask = 0xFF0F;
                shift = 4;
            } 
            else  
            {
                reg = 20;
                mask = 0x0FFF;
                shift = 12;
            }
            rtl8306e_reg_get(5, reg, 2, &regValue);
            regValue = (regValue & mask) | ((value & 0xf) << shift);
            rtl8306e_reg_set(5, reg, 2, regValue);

            /*bit[6:4]*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);  
                regValue &= 0xffc7;
                regValue |= ((value & 0x70) >> 4) << 3;
                rtl8306e_reg_set(1, 26, 3, regValue);                                   
             } 
             else if (RTL8306_QUEUE1 == queue) 
             {
                rtl8306e_reg_get(1, 26, 3, &regValue);  
                regValue &= 0xf1ff;
                regValue |= ((value & 0x70) >> 4) << 9;
                rtl8306e_reg_set(1, 26, 3, regValue);                                                   
             }
             else if (RTL8306_QUEUE2 == queue) 
             {
                /*bit[4]*/
                rtl8306e_reg_get(1, 26, 3, &regValue);                  
                regValue &= 0x7fff;
                regValue |= (((value & 0x10) >> 4) << 15);
                rtl8306e_reg_set(1, 26, 3, regValue);   

                /*bit[6:5]*/
                rtl8306e_reg_get(1, 27, 3, &regValue);         
                regValue &= 0xfffc;
                regValue |= ((value & 0x60) >> 5) ;
                rtl8306e_reg_set(1, 27, 3, regValue);
             } 
             else  
             {
                 rtl8306e_reg_get(1, 27, 3, &regValue);       
                 regValue &= 0xff1f;
                 regValue |= ((value & 0x70) >> 4) << 5;
                 rtl8306e_reg_set(1, 27, 3, regValue);
             }             
                     
             break;
        case 2 :    /*set 0, turn on, DSC*/
            if (RTL8306_QUEUE0 == queue) 
                reg = 18;
            else if (RTL8306_QUEUE1 == queue) 
                reg = 19;
            else if (RTL8306_QUEUE2 == queue)
                reg = 21;
            else  
                reg = 22;
            rtl8306e_reg_get(5, reg, 2, &regValue);
            regValue = (regValue & 0xFFC0) | (value & 0x3f);
            rtl8306e_reg_set(5, reg, 2, regValue);

             /*bit[6]*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_regbit_set(5, 21, 7, 2, (value & 0x40) ? 1:0);            
            }      
            else if (RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_regbit_set(5, 21, 15, 2, (value & 0x40) ? 1:0);            
            }
            else if (RTL8306_QUEUE2 == queue)
            {
                rtl8306e_regbit_set(5, 24, 7, 2, (value & 0x40) ? 1:0);                        
            }
            else 
            {
                rtl8306e_regbit_set(5, 24, 15, 2, (value & 0x40) ? 1:0);                        
            }            
            break;
            
        case 3:   /*set 0, turn  on, QLEN*/
            if (RTL8306_QUEUE0 == queue) 
                reg = 18;
            else if (RTL8306_QUEUE1 == queue) 
                reg = 19;
            else if (RTL8306_QUEUE2 == queue) 
                reg = 21;
            else  
                reg = 22;
            if (queue != RTL8306_QUEUE3)  
            {
                rtl8306e_reg_get(5, reg, 2, &regValue);
                regValue = (regValue & 0xC0FF) | ((value & 0x3f) << 8);
                rtl8306e_reg_set(5, reg, 2, regValue);
            }  
            else 
            {
                rtl8306e_reg_get(5, reg, 2, &regValue);
                regValue = (regValue & 0x3FF) | ((value & 0x3f) << 10);
                rtl8306e_reg_set(5, reg, 2, regValue);
            }
        
             /*bit[6]*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_regbit_set(5, 21, 6, 2, (value & 0x40) ? 1:0);    
            }      
            else if (RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_regbit_set(5, 21, 14, 2, (value & 0x40) ? 1:0);                      
            }
            else if (RTL8306_QUEUE2 == queue)
            {
                rtl8306e_regbit_set(5, 24, 6, 2, (value & 0x40) ? 1:0);                        
            }
            else 
            {
                rtl8306e_regbit_set(5, 24, 14, 2, (value & 0x40) ? 1:0);                        
            }                   
            break;
        
        case 4:     /*set 1, turn off, DSC*/
            if (RTL8306_QUEUE0 == queue) 
            {
                reg = 23;
                mask = 0xFFF0;
                shift =0;
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                reg = 23;
                mask = 0xF0FF;
                shift =8;
            } 
            else if (RTL8306_QUEUE2 == queue)
            {
                reg = 26;
                mask = 0xFFF0;
                shift =0;
            }
            else 
            {
                reg = 26;
                mask = 0xF0FF;
                shift =8;
            }
            rtl8306e_reg_get(5, reg, 2, &regValue);
            regValue = (regValue & mask) | ((value & 0xf) << shift);
            rtl8306e_reg_set(5, reg, 2, regValue);

            /*flc bit[6:4]*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_reg_get(1, 27, 3, &regValue);  
                regValue &= 0xf8ff;
                regValue |= ((value & 0x70) >> 4) << 8;
                rtl8306e_reg_set(1, 27, 3, regValue);                
             } 
             else if (RTL8306_QUEUE1 == queue) 
             {                
                rtl8306e_reg_get(1, 27, 3, &regValue);  
                regValue &= 0x3fff;
                regValue |= ((value & 0x30) >> 4) << 14;
                rtl8306e_reg_set(1, 27, 3, regValue);           
                rtl8306e_regbit_set(1, 28, 0, 3, (value & 0x40) ? 1:0);
                    
             }
             else if (RTL8306_QUEUE2 == queue) 
             {
                rtl8306e_reg_get(1, 28, 3, &regValue);
                regValue &= 0xff8f;
                regValue |= ((value & 0x70) >> 4) << 4;
                rtl8306e_reg_set(1, 28, 3, regValue);
             } 
             else  
             {
                rtl8306e_reg_get(1, 28, 3, &regValue);
                regValue &= 0xe3ff;
                regValue |= ((value & 0x70) >> 4) << 10;
                rtl8306e_reg_set(1, 28, 3, regValue);                
             }                        
            break;
        
        case 5:     /*set 1, turn off, QLEN*/
            if (RTL8306_QUEUE0 == queue) 
            {
                reg = 23;
                mask = 0xFF0F;
                shift = 4;
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                reg = 23;
                mask = 0x0FFF;
                shift = 12;
            } 
            else if (RTL8306_QUEUE2 == queue) 
            {
                reg = 26;
                mask = 0xFF0F;
                shift = 4;
            } 
            else 
            {
                reg = 26;
                mask = 0x0FFF;
                shift = 12;
            }
            rtl8306e_reg_get(5, reg, 2, &regValue);
            regValue = (regValue & mask) | ((value & 0xf) << shift);
            rtl8306e_reg_set(5, reg, 2, regValue);

             /*bit[6:4]*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_reg_get(1, 27, 3, &regValue);  
                regValue &= 0xc7ff;
                regValue |= ((value & 0x70) >> 4) << 11;
                rtl8306e_reg_set(1, 27, 3, regValue);
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_reg_get(1, 28, 3, &regValue);  
                regValue &= 0xfff1;
                regValue |= ((value & 0x70) >> 4) << 1;
                rtl8306e_reg_set(1, 28, 3, regValue);                                
            }
            else if (RTL8306_QUEUE2 == queue) 
            {
                rtl8306e_reg_get(1, 28, 3, &regValue);  
                regValue &= 0xfc7f;
                regValue |= ((value & 0x70) >> 4) << 7;
                rtl8306e_reg_set(1, 28, 3, regValue);                                
            } 
            else  
            {
                rtl8306e_reg_get(1, 28, 3, &regValue);
                regValue &= 0x1fff;
                regValue |= ((value & 0x70) >> 4) << 13;
                rtl8306e_reg_set(1, 28, 3, regValue);                                                
            }                                 
            break;
        
        case 6:    /*set 1, turn on, DSC*/
            if (RTL8306_QUEUE0 == queue) 
                reg = 24;
            else if  (RTL8306_QUEUE1 == queue) 
                reg =25;
            else if (RTL8306_QUEUE2 == queue) 
                reg = 27;
            else  
                reg = 28;
            rtl8306e_reg_get(5, reg, 2, &regValue);
            regValue = (regValue & 0xFFC0) | (value & 0x3f);
            rtl8306e_reg_set(5, reg, 2, regValue);

             /*bit[6]*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_regbit_set(5, 25, 7, 2, (value & 0x40) ? 1:0);            
            }      
            else if(RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_regbit_set(5, 25, 15, 2, (value & 0x40) ? 1:0);            
            }
            else if(RTL8306_QUEUE2 == queue)
            {
                rtl8306e_regbit_set(5, 27, 7, 2, (value & 0x40) ? 1:0);            
            }
            else 
            {
                rtl8306e_regbit_set(5, 27, 15, 2, (value & 0x40) ? 1:0);            
            }              
            break;
        
        case 7:     /*set 1, turn  on, QLEN*/
            if (RTL8306_QUEUE0 == queue) 
                reg = 24;
            else if (RTL8306_QUEUE1 == queue) 
                reg =25;
            else if (RTL8306_QUEUE2 == queue) 
                reg = 27;
            else  
                reg = 28;
            if (queue != RTL8306_QUEUE3)  
            {
                rtl8306e_reg_get(5, reg, 2, &regValue);
                regValue = (regValue & 0xC0FF) | ((value & 0x3f) << 8);
                rtl8306e_reg_set(5, reg, 2, regValue);
            } 
            else 
            {
                rtl8306e_reg_get(5, reg, 2, &regValue);
                regValue = (regValue & 0x3FF) | ((value & 0x3f) << 10);
                rtl8306e_reg_set(5, reg, 2, regValue);
            }

            /*bit[6]*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_regbit_set(5, 25, 6, 2, (value & 0x40) ? 1:0);            
            }      
            else if(RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_regbit_set(5, 25, 14, 2, (value & 0x40) ? 1:0);            
            } 
            else if (RTL8306_QUEUE2 == queue)
            {
                rtl8306e_regbit_set(5, 27, 6, 2, (value & 0x40) ? 1:0);                        
            } 
            else 
            {
                rtl8306e_regbit_set(5, 27, 14, 2, (value & 0x40) ? 1:0);                        
            }              
            break;
            
        default:
            return FALSE;
       }

    return TRUE;
}

uint32 rtl8306e_qos_queFlcThr_get(uint32 queue, uint32 type, uint32 onoff, uint32 set, uint32* pValue) 
{
    uint16 regValue;
	uint32 QUEValue = 0;
	uint32 mask;
    uint32 selection;
    uint32 reg, shift = 0;
    
    if ((queue > RTL8306_QUEUE3) || (type > RTL8306_FCO_QLEN) || (onoff > RTL8306_FCON) ||
        (set > RTL8306_FCO_SET1) || (NULL == pValue))
        return FALSE;
    
    selection = (set << 2) | (onoff <<1) |type;
    *pValue = 0;
    switch (selection) 
    {
        case 0 :    /*set 0, turn off, DSC*/
            if (RTL8306_QUEUE0 == queue) 
            {
                reg = 17;
                mask = 0xF;
                shift = 0;
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                reg = 17;
                mask = 0x0F00;
                shift = 8;
            }
            else if (RTL8306_QUEUE2 == queue) 
            {
                reg = 20;
                mask = 0xF;
                shift = 0;
            } else 
            {
                reg = 20;
                mask = 0x0F00;
                shift = 8;
            }
            rtl8306e_reg_get(5, reg, 2, &regValue);
            *pValue = (regValue & mask) >> shift;

            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);
                regValue &= 0x7;
                *pValue |= (regValue << 4);                    
             } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);
                regValue &= 0x1c0;
                regValue = regValue >> 6;
                *pValue |= (regValue << 4);                     
            } 
            else if (RTL8306_QUEUE2 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);
                regValue &= 0x7000;
                regValue = regValue >> 12;
                *pValue |= (regValue << 4);                                
            } 
            else  
            {
                rtl8306e_reg_get(1, 27, 3, &regValue);
                regValue &= 0x1c;
                regValue = regValue >> 2;
                *pValue |= (regValue << 4);                                                  
            }                     
            break;
        
        case 1 :    /*set 0, turn off, QLEN*/
            if (RTL8306_QUEUE0 == queue) 
            {
                reg = 17;
                mask = 0x00F0;
                shift = 4;
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                reg = 17;
                mask = 0xF000;
                shift = 12;
            } 
            else if (RTL8306_QUEUE2 == queue) 
            {
                reg = 20;
                mask = 0x00F0;
                shift = 4;
            }
            else  
            {
                reg = 20;
                mask = 0xF000;
                shift = 12;
            }
            rtl8306e_reg_get(5, reg, 2, &regValue);
            *pValue = (regValue & mask) >> shift;

            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);
                regValue &= 0x38;
                regValue = regValue >> 3;
                *pValue |= (regValue << 4);                                                                           
             } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);
                regValue &= 0xe00;
                regValue = regValue >> 9;
                *pValue |= (regValue << 4);                                                                                               
            }
            else if (RTL8306_QUEUE2 == queue)
            {
                rtl8306e_reg_get(1, 26, 3, &regValue);
                regValue &= 0x8000;
                regValue = regValue >> 15;
                *pValue |= (regValue << 4);                                                                                               
                  
                rtl8306e_reg_get(1, 27, 3, &regValue);
                regValue &= 0x3;
                *pValue |= (regValue << 5);                                                                                                       
            } 
            else  
            {
                rtl8306e_reg_get(1, 27, 3, &regValue);
                regValue &= 0xe0;
                regValue = regValue >> 5;
                *pValue |= (regValue << 4);  
            }
        
        break;
        
        case 2 :    /*set 0, turn on, DSC*/
            if (RTL8306_QUEUE0 == queue) 
                reg = 18;
            else if (RTL8306_QUEUE1 == queue) 
                reg = 19;
            else if (RTL8306_QUEUE2 == queue)
                reg = 21;
            else  
                reg = 22;
            rtl8306e_reg_get(5, reg, 2, &regValue);
            *pValue = regValue & 0x3F;

            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_regbit_get(5, 21, 7, 2, &QUEValue);
                *pValue |= (QUEValue << 6);
            }      
            else if (RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_regbit_get(5, 21, 15, 2, &QUEValue);
                *pValue |= (QUEValue << 6);                
            }      
            else if (RTL8306_QUEUE2 == queue)
            {
                rtl8306e_regbit_get(5, 24, 7, 2, &QUEValue);
                *pValue |= (QUEValue << 6);                             
            }      
            else  
            {
                rtl8306e_regbit_get(5, 24, 15, 2, &QUEValue);
                *pValue |= (QUEValue << 6);                             
            }              
            break;
            
    case 3:   /*set 0, turn  on, QLEN*/
        if (RTL8306_QUEUE0 == queue) 
            reg = 18;
        else if  (RTL8306_QUEUE1 == queue) 
            reg = 19;
        else if (RTL8306_QUEUE2 == queue) 
            reg = 21;
        else  
            reg = 22;
        if (queue != RTL8306_QUEUE3) 
        {
            rtl8306e_reg_get(5, reg, 2, &regValue);
            *pValue = (regValue & 0x3F00) >> 8 ;
        } else 
        {
            rtl8306e_reg_get(5, reg, 2, &regValue);
            *pValue = (regValue & 0xFC00) >> 10;
        }

        if (RTL8306_QUEUE0 == queue) 
        {
            rtl8306e_regbit_get(5, 21, 6, 2, &QUEValue);
            *pValue |= (QUEValue << 6);
        }      
        else if (RTL8306_QUEUE1 == queue) 
        {
            rtl8306e_regbit_get(5, 21, 14, 2, &QUEValue);
            *pValue |= (QUEValue << 6);                
        }      
        else if (RTL8306_QUEUE2 == queue)
        {
            rtl8306e_regbit_get(5, 24, 6, 2, &QUEValue);
            *pValue |= (QUEValue << 6);                             
        }      
        else  
        {
            rtl8306e_regbit_get(5, 24, 14, 2, &QUEValue);
            *pValue |= (QUEValue << 6);                             
        }               
        break;
        
        case 4:     /*set 1, turn off, DSC*/
            if (RTL8306_QUEUE0 == queue) 
            {
                reg = 23;
                mask = 0x000F;
                shift =0;
            } 
            else if (RTL8306_QUEUE1 == queue) 
            {
                reg = 23;
                mask = 0x0F00;
                shift =8;
            }
            else if (RTL8306_QUEUE2 == queue)
            {
                reg = 26;
                mask = 0x000F;
                shift =0;
            }
            else 
            {
                reg = 26;
                mask = 0x0F00;
                shift =8;
            }
            rtl8306e_reg_get(5, reg, 2, &regValue);
            *pValue = (regValue & mask) >> shift;
        
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_reg_get(1, 27, 3, &regValue);
                regValue &= 0x700;
                regValue = regValue >> 8;                 
                *pValue |= (regValue << 4);                    
            }
            else if (RTL8306_QUEUE1 == queue) 
            {
                rtl8306e_reg_get(1, 27, 3, &regValue);
                regValue &= 0xc000;
                regValue = regValue >> 14;                 
                *pValue |= (regValue << 4);
                rtl8306e_regbit_get(1, 28, 0, 3, &QUEValue);
                *pValue |= (QUEValue << 6);                 
            }
            else if (RTL8306_QUEUE2 == queue) 
            {
                rtl8306e_reg_get(1, 28, 3, &regValue);
                regValue &= 0x70;
                 regValue = regValue >> 4;                 
                 *pValue |= (regValue << 4);  
            } 
			else  
            {
                rtl8306e_reg_get(1, 28, 3, &regValue);
                regValue &= 0x1c00;
                regValue = regValue >> 10;                 
                *pValue |= (regValue << 4);  
            }                             
            break;
        
    case 5:     /*set 1, turn off, QLEN*/
        if (RTL8306_QUEUE0 == queue) 
        {
            reg = 23;
            mask = 0xF0;
            shift = 4;
        } 
        else if (RTL8306_QUEUE1 == queue)
        {
            reg = 23;
            mask = 0xF000;
            shift = 12;
        }
        else if (RTL8306_QUEUE2 == queue)
        {
            reg = 26;
            mask = 0xF0;
            shift = 4;
        } 
        else  
        {
            reg = 26;
            mask = 0xF000;
            shift = 12;
        }
        rtl8306e_reg_get(5, reg, 2, &regValue);
        *pValue = (regValue & mask) >> shift;

        if (RTL8306_QUEUE0 == queue) 
        {
            rtl8306e_reg_get(1, 27, 3, &regValue);
            regValue &= 0x3800;
            regValue = regValue >> 11;                 
            *pValue |= (regValue << 4);                    
        } 
        else if (RTL8306_QUEUE1 == queue) 
        {
            rtl8306e_reg_get(1, 28, 3, &regValue);
            regValue &= 0xe;
            regValue = regValue >> 1;                 
            *pValue |= (regValue << 4);                    
        } 
        else if (RTL8306_QUEUE2 == queue)   
        {
            rtl8306e_reg_get(1, 28, 3, &regValue);
            regValue &= 0x380;
            regValue = regValue >> 7;                 
            *pValue |= (regValue << 4);
        }
        else  
        {
            rtl8306e_reg_get(1, 28, 3, &regValue);
            regValue &= 0xe000;
            regValue = regValue >> 13;                 
            *pValue |= (regValue << 4);
        }                             
        break;
        
        case 6:     /*set 1, turn on, DSC*/
            if (RTL8306_QUEUE0 == queue) 
                reg = 24;
            else if (RTL8306_QUEUE1 == queue) 
                reg =25;
            else if (RTL8306_QUEUE2 == queue) 
                reg = 27;
            else  
                reg = 28;
            rtl8306e_reg_get(5, reg, 2, &regValue);
            *pValue = (regValue & 0x3F) >> shift;
        
             /*bit 6*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_regbit_get(5, 25, 7, 2, &QUEValue);
                *pValue |= (QUEValue << 6);
            }      
            else if (RTL8306_QUEUE1 == queue) 
            {
                 rtl8306e_regbit_get(5, 25, 15, 2, &QUEValue);
                 *pValue |= (QUEValue << 6);                
             }      
            else if (RTL8306_QUEUE2 == queue)
            {
                rtl8306e_regbit_get(5, 27, 7, 2, &QUEValue);
                *pValue |= (QUEValue << 6);                             
            }      
            else  
            {
                rtl8306e_regbit_get(5, 27, 15, 2, &QUEValue);
                *pValue |= (QUEValue << 6);                             
            }      
        
            break;
        
        case 7:      /*set 1, turn  on, QLEN*/
            if (RTL8306_QUEUE0 == queue) 
                reg = 24;
            else if (RTL8306_QUEUE1 == queue) 
                reg =25;
            else if (RTL8306_QUEUE2 == queue) 
                reg = 27;
            else  
                reg = 28;
            if (queue != RTL8306_QUEUE3) 
            {
                rtl8306e_reg_get(5, reg, 2, &regValue);
                *pValue = (regValue & 0x3F00) >> 8 ;
            } 
            else 
            {
                rtl8306e_reg_get(5, reg, 2, &regValue);
                *pValue = (regValue & 0xFC00) >> 10;
            }
             /*bit 6*/
            if (RTL8306_QUEUE0 == queue) 
            {
                rtl8306e_regbit_get(5, 25, 6, 2, &QUEValue);
                *pValue |= (QUEValue << 6);
            }      
            else if (RTL8306_QUEUE1 == queue) 
            {
                 rtl8306e_regbit_get(5, 25, 14, 2, &QUEValue);
                 *pValue |= (QUEValue << 6);                
            }      
            else if (RTL8306_QUEUE2 == queue)
            {
                rtl8306e_regbit_get(5, 27, 6, 2, &QUEValue);
                *pValue |= (QUEValue << 6);                             
            }      
            else  
            {
                rtl8306e_regbit_get(5, 27, 14, 2, &QUEValue);
                 *pValue |= (QUEValue << 6);                             
            }               
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

uint32 rtl8306e_qos_portFlcThr_set(uint32 port, uint32 onthr, uint32 offthr, uint32 direction ) 
{
    uint32 regValue;

    if ((port > RTL8306_PORT5) || (direction > 1))
        return FALSE;
    
    regValue = (offthr << 8) + onthr;

    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ;
    
    if (RTL8306_PORT_TX == direction) 
        rtl8306e_reg_set(port, 20, 2, regValue);
    else 
        rtl8306e_reg_set(port, 19, 3, regValue);
    return TRUE;
}

uint32 rtl8306e_qos_portFlcThr_get(uint32 port, uint32 *pOnthr, uint32 *pOffthr, uint32 direction) 
{
    uint16 regValue;

    if ((port > RTL8306_PORT5) || (NULL == pOnthr) || (NULL == pOffthr) || (direction > 1))
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ; 
    
    if (RTL8306_PORT_TX == direction) 
        rtl8306e_reg_get(port, 20, 2, &regValue);
    else 
        rtl8306e_reg_get(port, 19, 3, &regValue);
    *pOnthr = regValue & 0xFF;
    *pOffthr = (regValue & 0xFF00) >> 8;
    return TRUE;
}


uint32 rtl8306e_qos_portFlcMode_set(uint32 port, uint32 set) 
{
    if ((port > RTL8306_PORT5) || (set > RTL8306_FCO_SET1))
        return FALSE;
    
 //  zhangcong 2012 4 10    
    if (port < RTL8306_PORT5) { 
        rtl8306e_regbit_set(port, 16, 4, 0, set); //收方向
		rtl8306e_regbit_set(port, 16, 5, 0, set); //发方向
	}
    else 
        rtl8306e_regbit_set(6, 18, 12, 2, set);
    return TRUE;
}


uint32 rtl8306e_qos_portFlcMode_get(uint32 port , uint32 *set) 
{
    if ((port > RTL8306_PORT5) || (set == NULL))
        return FALSE;
    
    if (port < RTL8306_PORT5)
        rtl8306e_regbit_get(port, 18, 12, 2, set);
    else
        rtl8306e_regbit_get(6, 18, 12, 2, set);
    return TRUE;
}

uint32 rtl8306e_qos_queFlcEnable_set( uint32 port, uint32 queue, uint32 enabled) 
{

    if ((port > RTL8306_PORT5) ||(queue > RTL8306_QUEUE3))
        return FALSE;
    
    /*Enable/Disable Flow control of the specified queue*/
    switch (port) 
    {
        case RTL8306_PORT0:
            rtl8306e_regbit_set(6, 17, (4 + queue), 0, enabled ? 0:1);
            break;
        case RTL8306_PORT1:
            rtl8306e_regbit_set(6, 18, (4 + queue), 0, enabled ? 0:1);
            break;
        case RTL8306_PORT2:
            rtl8306e_regbit_set(6, 19, (4 + queue), 0, enabled ? 0:1);
            break;
        case RTL8306_PORT3:
            rtl8306e_regbit_set(6, 20, (4 + queue), 0, enabled ? 0:1);
            break;
        case RTL8306_PORT4:
            rtl8306e_regbit_set(6, 21, (4 + queue), 0, enabled ? 0:1);
            break;
        case RTL8306_PORT5:
            rtl8306e_regbit_set(6, 23, (4 + queue), 0, enabled ? 0:1);
            break;    
        default:
            return FALSE;
    }
    return TRUE;
}

uint32 rtl8306e_qos_queFlcEnable_get(uint32 port, uint32 queue, uint32 *pEnabled) 
{
    uint32 bitValue;

    if ((port > RTL8306_PORT5) || (queue > RTL8306_QUEUE3) || (NULL == pEnabled))
        return FALSE;
    
    switch (port) 
    {
        case RTL8306_PORT0:
            rtl8306e_regbit_get(6, 17, (4 + queue), 0, &bitValue);
            break;
        case RTL8306_PORT1:
            rtl8306e_regbit_get(6, 18, (4 + queue), 0, &bitValue);
            break;
        case RTL8306_PORT2:
            rtl8306e_regbit_get(6, 19, (4 + queue), 0, &bitValue);
            break;
        case RTL8306_PORT3:
            rtl8306e_regbit_get(6, 20, (4 + queue), 0, &bitValue);
            break;
        case RTL8306_PORT4:
            rtl8306e_regbit_get(6, 21, (4 + queue), 0, &bitValue);
            break;
        case RTL8306_PORT5:
            rtl8306e_regbit_get(6, 23, (4 + queue), 0, &bitValue);
            break;    
        default:
            return FALSE;
    }
    *pEnabled = (bitValue ? FALSE : TRUE);
    
    return TRUE;
}


/* Function Name:
 *      rtl8306e_acl_entry_set
 * Description:
 *      Set Asic ACL table
 * Input:
 *      entryadd   - Acl entry address (0~15)
 *      phyport    -  Acl physical port
 *      action      -  Acl action 
 *      protocol   -  Acl protocol
 *      data        -  ether type value or TCP/UDP port
 *      priority     -  Acl priority
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      phyport could be 
 *            0~5:       port number, 
 *            RTL8306_ACL_INVALID: invalid entry,
 *            RTL8306_ACL_ANYPORT: any port.
 *      Acl action could be
 *          RTL8306_ACT_DROP,
 *          RTL8306_ACT_PERMIT, 
 *          RTL8306_ACT_TRAPCPU, 
 *          RTL8306_ACT_MIRROR
 *      Acl protocol could be
 *          RTL8306_ACL_ETHER(ether type), 
 *          RTL8306_ACL_TCP(TCP), 
 *          RTL8306_ACL_UDP(UDP),
 *          RTL8306_ACL_TCPUDP(TCP or UDP)
 *
 *      Acl priority:
 *          RTL8306_PRIO0~RTL8306_PRIO3
 *       
 */

uint32 rtl8306e_acl_entry_set(uint32 entryadd, uint32 phyport, uint32 action, uint32 protocol, uint32 data, uint32 priority) 
{
    uint16 regValue;
	uint32 value;
    uint32 pollcnt  ;
    uint32 bitValue;

    if ((entryadd > RTL8306_ACL_ENTRYNUM - 1) || (phyport > RTL8306_ACL_ANYPORT) || 
        (action > RTL8306_ACT_MIRROR) ||(protocol > RTL8306_ACL_TCPUDP) ||
        (priority > RTL8306_PRIO3))
        return FALSE;

    /*Enable CPU port function, Enable inserting CPU TAG, Enable removing CPU TAG */
    rtl8306e_reg_get(2, 21, 3, &regValue);
    regValue = (regValue & 0x7FFF) | (1 << 11) | (1<<12);
    rtl8306e_reg_set(2, 21, 3, regValue);
    
    /*set EtherType or TCP/UDP Ports, ACL entry access register 0*/
    rtl8306e_reg_set(3, 21, 3, data);
    
    /*set ACL entry access register 1*/
    rtl8306e_reg_get(3, 22, 3, &regValue);
    value = (1 << 14) | (entryadd << 9)  | (priority << 7) | (action << 5) | (phyport << 2) | protocol ;
    regValue = (regValue & 0x8000) | value  ;
    rtl8306e_reg_set(3, 22, 3, regValue);
    
    /*Polling whether the command is done*/
    for (pollcnt = 0; pollcnt < RTL8306_IDLE_TIMEOUT; pollcnt++) 
    {
        rtl8306e_regbit_get(3, 22, 14, 3, &bitValue);
        if (!bitValue)
            break;
    }
    if (pollcnt == RTL8306_IDLE_TIMEOUT)
        return FALSE;

#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.aclTbl[entryadd].phy_port = phyport;
    rtl8306_TblBak.aclTbl[entryadd].action = action;
    rtl8306_TblBak.aclTbl[entryadd].proto = protocol;
    rtl8306_TblBak.aclTbl[entryadd].data = data;
    rtl8306_TblBak.aclTbl[entryadd].pri = priority;
#endif  
    return TRUE;
}

/* Function Name:
 *      rtl8306e_acl_entry_get
 * Description:
 *      Get Asic ACL entry
 * Input:
 *      entryadd   - Acl entry address (0~15)
 * Output:
 *      pPhyport    -  Acl physical port 
 *      pAction      -  Acl action 
 *      pProtocol   -  Acl protocol
 *      pData        -  ether type value or TCP/UDP port
 *      pPriority     -  Acl priority
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      phyport could be 
 *            0~5:       port number, 
 *            RTL8306_ACL_INVALID: invalid entry,
 *            RTL8306_ACL_ANYPORT: any port.
 *      Acl action could be
 *          RTL8306_ACT_DROP,
 *          RTL8306_ACT_PERMIT, 
 *          RTL8306_ACT_TRAPCPU, 
 *          RTL8306_ACT_MIRROR
 *      Acl protocol could be
 *          RTL8306_ACL_ETHER(ether type), 
 *          RTL8306_ACL_TCP(TCP), 
 *          RTL8306_ACL_UDP(UDP),
 *          RTL8306_ACL_TCPUDP(TCP or UDP)
 *
 *      Acl priority:
 *          RTL8306_PRIO0~RTL8306_PRIO3
 *       
 */
uint32 rtl8306e_acl_entry_get(uint32 entryadd, uint32 *pPhyport, uint32 *pAction, uint32 *pProtocol, uint32  *pData, uint32 *pPriority)
{
    uint16 regValue;
    uint32 pollcnt  ;
    uint32 bitValue;

    if ((entryadd > RTL8306_ACL_ENTRYNUM - 1) || (NULL == pPhyport) || (NULL == pAction) || 
        (NULL == pProtocol) || (NULL == pData) || (NULL == pPriority))
        return FALSE;

    /*trigger a command to read ACL entry*/
    rtl8306e_reg_get(3, 22, 3, &regValue);
    regValue = (regValue & 0x81FF) | (0x3 << 13) | (entryadd << 9);
    rtl8306e_reg_set(3, 22, 3, regValue);
    
    /*Polling whether the command is done*/
    for (pollcnt = 0; pollcnt < RTL8306_IDLE_TIMEOUT ; pollcnt++) 
    {
        rtl8306e_regbit_get(3, 22, 14, 3, &bitValue);
        if (!bitValue)
            break;
    }
    if (pollcnt == RTL8306_IDLE_TIMEOUT)
        return FALSE;
    
    rtl8306e_reg_get(3, 21, 3, &regValue);
    *pData = regValue;
    rtl8306e_reg_get(3, 22, 3, &regValue);
    *pPriority = (regValue  >> 7) & 0x3;
    *pAction  = (regValue  >> 5) & 0x3;
    *pPhyport = (regValue >> 2) & 0x7;
    *pProtocol = regValue & 0x3;

    return TRUE;
}

/* Function Name:
 *      rtl8306e_mib_get
 * Description:
 *      Get the MIB counter for the specified port
 * Input:
 *      port         -  port number (0 ~ 5)
 *      counter    -  Specify counter type  
 * Output:
 *      pValue -  the pointer of counter value 
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      There are five MIB counter for each port, they are:
 *      RTL8306_MIB_CNT1 - TX count
 *      RTL8306_MIB_CNT2 - RX count
 *      RTL8306_MIB_CNT3 - RX Drop Count<nl>
 *      RTL8306_MIB_CNT4 - RX CRC error Count
 *      RTL8306_MIB_CNT5 - RX Fragment Count<nl>
 */
uint32 rtl8306e_mib_get(uint32 port, uint32 counter, uint32 *pValue) 
{
    uint16 regValue1, regValue2;

    if ((port > RTL8306_PORT5) || (counter > RTL8306_MIB_CNT5) ||
        (NULL == pValue))
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ;  
    
    switch(counter) 
    {
        case RTL8306_MIB_CNT1:            
            /*Must read low 16 bit first, then hight 16 bit*/
            rtl8306e_reg_get(port, 22, 2, &regValue1);
            rtl8306e_reg_get(port, 23, 2, &regValue2);
            *pValue = (regValue2 << 16) + regValue1;
            break;
            
        case RTL8306_MIB_CNT2:
            /*Must read low 16 bit first, then hight 16 bit*/
            rtl8306e_reg_get(port, 24, 2, &regValue1);
            rtl8306e_reg_get(port, 25, 2, &regValue2);
            *pValue = (regValue2 << 16) + regValue1;
            break;
            
        case RTL8306_MIB_CNT3:
            /*Must read low 16 bit first, then hight 16 bit*/
            rtl8306e_reg_get(port, 26, 2, &regValue1);
            rtl8306e_reg_get(port, 27, 2, &regValue2);
            *pValue = (regValue2 << 16) + regValue1;            
            break;
            
        case RTL8306_MIB_CNT4:
            /*Must read low 16 bit first, then hight 16 bit*/
            rtl8306e_reg_get(port, 28, 2, &regValue1);
            rtl8306e_reg_get(port, 29, 2, &regValue2);
            *pValue = (regValue2 << 16) + regValue1;            
            break;
            
        case RTL8306_MIB_CNT5:
            /*Must read low 16 bit first, then hight 16 bit*/
            rtl8306e_reg_get(port, 30, 2, &regValue1);
            rtl8306e_reg_get(port, 31, 2, &regValue2);
            *pValue = (regValue2 << 16) + regValue1;            
            break;
        default:
            return FALSE;
    }
    return TRUE;
}


/* Function Name:
 *      rtl8306e_mibUnit_set
 * Description:
 *      Set RX/Tx Mib counting unit: byte or packet
 * Input:
 *      port         -  port number (0 ~ 5)
 *      counter    -  Specify counter type  
 *      uint         -  Specify counting unit
 * Output:
 *      none  
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      1.There are five MIB counter for each port, they are:
 *      RTL8306_MIB_CNT1 - TX count
 *      RTL8306_MIB_CNT2 - RX count
 *      RTL8306_MIB_CNT3 - RX Drop Count<nl>
 *      RTL8306_MIB_CNT4 - RX CRC error Count
 *      RTL8306_MIB_CNT5 - RX Fragment Count<nl>
 *      2.Only RTL8306_MIB_CNT1 and RTL8306_MIB_CNT2 could set counting unit  
 *      RTL8306_MIB_PKT or RTL8306_MIB_BYTE, default is RTL8306_MIB_PKT.
 *      the other counters' counting uint is RTL8306_MIB_PKT
 */
uint32 rtl8306e_mibUnit_set(uint32 port, uint32 counter, uint32 unit) 
{

    if ((port > RTL8306_PORT5) ||(unit > RTL8306_MIB_PKT))
        return FALSE;
    /*Port 5 corresponding PHY6*/
    if (port == RTL8306_PORT5 )  
        port ++ ;  
    switch(counter) 
    {
        case RTL8306_MIB_CNT1:
            rtl8306e_regbit_set(port, 17, 3, 2, unit);
            break;
        case RTL8306_MIB_CNT2:
            rtl8306e_regbit_set(port, 17, 4, 2, unit);
            break;
        default :
            return FALSE;
    }
    return TRUE;
}

/* Function Name:
 *      rtl8306e_mibUnit_get
 * Description:
 *      Get Rx/Tx Mib counting unit
 * Input:
 *      port         -  port number (0 ~ 5)
 *      counter    -  Specify counter type  
 * Output:
 *      pUnit         -  the pointer of counting unit
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      1.There are five MIB counter for each port, they are:
 *      RTL8306_MIB_CNT1 - TX count
 *      RTL8306_MIB_CNT2 - RX count
 *      RTL8306_MIB_CNT3 - RX Drop Count<nl>
 *      RTL8306_MIB_CNT4 - RX CRC error Count
 *      RTL8306_MIB_CNT5 - RX Fragment Count<nl>
 *      2.Only RTL8306_MIB_CNT1 and RTL8306_MIB_CNT2 could set counting unit  
 *      RTL8306_MIB_PKT or RTL8306_MIB_BYTE, default is RTL8306_MIB_PKT.
 *      the other counters' counting uint is RTL8306_MIB_PKT
 */
uint32 rtl8306e_mibUnit_get(uint32 port, uint32 counter, uint32 *pUnit) 
{ 
    uint32 bitValue;
    if ((port > RTL8306_PORT5) ||(pUnit == NULL))
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (port == RTL8306_PORT5 )  
        port ++ ;  
    switch(counter) 
    {
        case RTL8306_MIB_CNT1:
            rtl8306e_regbit_get(port, 17, 3, 2, &bitValue);
            break;
        case RTL8306_MIB_CNT2:
            rtl8306e_regbit_get(port, 17, 4, 2, &bitValue);
            break;
        default:
            return FALSE;
    }
    *pUnit = (bitValue ? RTL8306_MIB_PKT : RTL8306_MIB_BYTE);
    return TRUE;
}

/* Function Name:
 *      rtl8306e_mib_reset
 * Description:
 *      reset MIB counter
 * Input:
 *      port         -  port number (0 ~ 5)
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */
uint32 rtl8306e_mib_reset(uint32 port) 
{

    if ((port > RTL8306_PORT5))
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ;  

    /*stop counting and clear Mib counter to 0*/
    rtl8306e_regbit_set(port, 17, 2, 2, 1);    
    
    /*Start counting*/
    rtl8306e_regbit_set(port, 17, 2, 2, 0);    
    return TRUE;
}

/* Function Name:
 *      rtl8306e_mirror_portBased_set
 * Description:
 *      Set asic Mirror port
 * Input:
 *      mirport         -  Specify mirror port 
 *      rxmbr           -  Specify Rx mirror port mask
 *      txmbr           -  Specify Tx mirror port mask
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      mirport could be 0 ~ 5, represent physical port number, 
 *      7 means that no port has mirror ability. rxmbr and txmbr
 *      is 6 bit value, each bit corresponds one port. ingress packet
 *      of port in rxmbr will be mirrored to mirport, egress packet 
 *      of port in txmbr will be mirrored to mirport.
 */
uint32 rtl8306e_mirror_portBased_set(uint32 mirport, uint32 rxmbr, uint32 txmbr) 
{
    uint16 regValue;

    if ((mirport > 7) ||(rxmbr > 0x3F) || (txmbr > 0x3F) )
        return FALSE;

    /*Set Mirror Port*/
    rtl8306e_reg_get(2, 22, 3, &regValue);
    regValue = (regValue & 0xC7FF) | (mirport << 11);
    rtl8306e_reg_set(2, 22, 3, regValue);
    
    /*enable mirror port to filter the mirrored packet sent from itself */
    rtl8306e_regbit_set(6, 21, 7, 3, 1);
        
    /*Set Ports Whose RX Data are Mirrored */
    rtl8306e_reg_get(6, 21, 3, &regValue);
    regValue = (regValue & 0xFFC0) | rxmbr ;
    rtl8306e_reg_set(6, 21, 3, regValue);
    
    /*Set Ports Whose TX Data are Mirrored */
    rtl8306e_reg_get(6, 21, 3, &regValue);
    regValue = (regValue & 0xC0FF) | (txmbr << 8);
    rtl8306e_reg_set(6, 21, 3, regValue);

#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.mir.mirPort = (uint8)mirport;
    rtl8306_TblBak.mir.mirRxPortMask = (uint8)rxmbr;
    rtl8306_TblBak.mir.mirTxPortMask = (uint8)txmbr;
#endif
    return TRUE;
}

/* Function Name:
 *      rtl8306e_mirror_portBased_get
 * Description:
 *      Get asic Mirror port
 * Input:
 *      none 
 * Output:
 *      pMirport     -  the pointer of mirror port
 *      pRxmbr       -  the pointer of  Rx mirror port mask
 *      pTxmbr       -  the pointer of Tx mirror port mask 
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      mirport could be 0 ~ 5, represent physical port number, 
 *      7 means that no port has mirror ability. rxmbr and txmbr
 *      is 6 bit value, each bit corresponds one port. ingress packet
 *      of port in rxmbr will be mirrored to mirport, egress packet 
 *      of port in txmbr will be mirrored to mirport.
 */
uint32 rtl8306e_mirror_portBased_get(uint32 *pMirport, uint32 *pRxmbr, uint32* pTxmbr) 
{
    uint16 regValue;

    if ((NULL == pMirport) ||(NULL == pRxmbr) || (NULL == pTxmbr)) 
        return FALSE;

    /*Get Mirror Port*/
    rtl8306e_reg_get(2, 22, 3, &regValue);
    *pMirport = (regValue & 0x3800) >> 11;
    
    /*Get Ports Whose RX Data are Mirrored*/
    rtl8306e_reg_get(6, 21, 3, &regValue);
    *pRxmbr = regValue & 0x3F;
    
    /*Get Ports Whose TX Data are Mirrored */
    rtl8306e_reg_get(6, 21, 3, &regValue);
    *pTxmbr = (regValue & 0x3F00) >> 8;
    return TRUE;
}

/* Function Name:
 *      rtl8306e_mirror_macBased_set
 * Description:
 *      Set Mac address for mirror packet
 * Input:
 *      macAddr  - mirrored mac address, it could be SA or DA of the packet 
 *      enabled   - enable mirror packet by mac address
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *
 */
uint32 rtl8306e_mirror_macBased_set(uint8 *macAddr, uint32 enabled) 
{

    if (NULL == macAddr)
        return FALSE;

    if (!enabled) 
    {
        rtl8306e_regbit_set(6, 21, 14, 3, 0);
#ifdef RTL8306_TBLBAK
        rtl8306_TblBak.mir.enMirMac = (uint8)enabled;
#endif
    } 
    else 
    {
        rtl8306e_regbit_set(6, 21, 14, 3, 1);
        rtl8306e_reg_set(6, 22, 3, (macAddr[1] << 8) | macAddr[0]);
        rtl8306e_reg_set(6, 23, 3, (macAddr[3] << 8) | macAddr[2]);
        rtl8306e_reg_set(6, 24, 3, (macAddr[5] << 8) | macAddr[4]);
#ifdef RTL8306_TBLBAK
        rtl8306_TblBak.mir.enMirMac = (uint8)enabled;
        rtl8306_TblBak.mir.mir_mac[0] = macAddr[0];
        rtl8306_TblBak.mir.mir_mac[1] = macAddr[1];
        rtl8306_TblBak.mir.mir_mac[2] = macAddr[2];
        rtl8306_TblBak.mir.mir_mac[3] = macAddr[3];
        rtl8306_TblBak.mir.mir_mac[4] = macAddr[4];
        rtl8306_TblBak.mir.mir_mac[5] = macAddr[5];   
#endif
    }

    return TRUE;
}

/* Function Name:
 *      rtl8306e_mirror_macBased_set
 * Description:
 *      Set Mac address for mirror packet
 * Input:
 *      none 
 * Output:
 *      macAddr   - mirrored mac address, it could be SA or DA of the packet 
 *      pEnabled   - the pointer of enable mirror packet by mac address 
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 * 
 */
uint32 rtl8306e_mirror_macBased_get(uint8 *macAddr, uint32 *pEnabled) 
{
    uint16 regValue;
    uint32 bitValue;

    if (NULL == macAddr)
        return FALSE;
    
    rtl8306e_regbit_get(6, 21, 14, 3, &bitValue);
    *pEnabled = (bitValue  ? TRUE : FALSE);
    rtl8306e_reg_get(6, 22, 3, &regValue);
    macAddr[0] = regValue & 0xFF;
    macAddr[1] = (regValue & 0xFF00) >> 8;
    rtl8306e_reg_get(6, 23, 3, &regValue);
    macAddr[2] = regValue & 0xFF;
    macAddr[3] = (regValue & 0xFF00) >> 8;
    rtl8306e_reg_get(6, 24, 3, &regValue);
    macAddr[4] = regValue & 0xFF;
    macAddr[5] = (regValue & 0xFF00) >> 8;
    return TRUE;
    
}


/* Function Name:
 *      rtl8306e_l2_MacToIdx_get
 * Description:
 *      get L2 table hash value from mac address
 * Input:
 *      macAddr        -  mac address
 * Output:
 *      pIndex           -  mac address table index   
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      when a mac address is learned into mac address table, 
 *      9 bit index value is got from the mac address by hashing 
 *      algorithm, each index corresponds to 4 entry, it means
 *      the table could save 4 mac addresses at the same time
 *      whose index value is equal, so switch mac address table 
 *      has 2048 entry. the API could get hash index from 
 *      a specified mac address.
 */
uint32 rtl8306e_l2_MacToIdx_get(uint8 *macAddr, uint32* pIndex)
{
    uint32 tmp_index;
    uint32 status;

    if ((NULL == macAddr) || (NULL == pIndex))
        return FALSE;


    rtl8306e_regbit_get(1, 23, 12, 0, &status);    
    *pIndex = 0;
    
    if (status) 
    {  
        /* xor hash algorithm*/
        
        /* Index 0 = 4 ^ 11 ^ 18 ^ 25 ^ 32 */
        *pIndex |= ((macAddr[5] & 0x8) >> 3) ^ ((macAddr[4] & 0x10) >> 4) ^ ((macAddr[3] & 0x20) >> 5) ^ ((macAddr[2] & 0x40) >> 6) ^  ((macAddr[1] & 0x80) >> 7); 

        /* Index_1 = 3 ^ 10 ^ 17 ^ 24 ^ 47 */
        tmp_index = ((macAddr[5] & 0x10) >> 4) ^ ((macAddr[4] & 0x20) >> 5) ^ ((macAddr[3] & 0x40) >> 6) ^ ((macAddr[2] & 0x80) >> 7) ^ ((macAddr[0] & 0x1) >> 0);
        *pIndex |= tmp_index << 1;

        /* Index_2 = 2 ^ 9 ^ 16 ^ 39 ^ 46 */
        tmp_index = ((macAddr[5] & 0x20) >> 5) ^ ((macAddr[4] & 0x40) >> 6) ^ ((macAddr[3] & 0x80) >> 7) ^ ((macAddr[1] & 0x1) >> 0) ^ ((macAddr[0] & 0x2) >> 1);
        *pIndex |= tmp_index << 2;

        /* Index_3 = 1 ^ 8 ^ 31 ^ 38 ^ 45 */
        tmp_index = ((macAddr[5] & 0x40) >> 6) ^ ((macAddr[4] & 0x80) >> 7) ^ ((macAddr[2] & 0x1) >> 0) ^ ((macAddr[1] & 0x2) >> 1) ^ ((macAddr[0] & 0x4) >> 2);
        *pIndex |= tmp_index << 3;

        /* Index_4 = 0 ^ 23 ^ 30 ^ 37 ^ 44 */
        tmp_index = ((macAddr[5] & 0x80) >> 7) ^ ((macAddr[3] & 0x1) >> 0) ^ ((macAddr[2] & 0x2) >> 1) ^ ((macAddr[1] & 0x4) >> 2) ^ ((macAddr[0] & 0x8) >> 3);
        *pIndex |= tmp_index << 4;

        /* Index_5 = 15 ^ 22 ^ 29 ^ 36 ^ 43 */
        tmp_index = ((macAddr[4] & 0x1) >> 0) ^ ((macAddr[3] & 0x2) >> 1) ^ ((macAddr[2] & 0x4) >> 2) ^ ((macAddr[1] & 0x8) >> 3) ^ ((macAddr[0] & 0x10) >> 4);
        *pIndex |= tmp_index << 5;

        /* Index_6 = 7 ^  14 ^ 21 ^ 28 ^ 35 ^ 42 */
        tmp_index = ((macAddr[5] & 0x1) >> 0) ^ ((macAddr[4] & 0x2) >> 1) ^ ((macAddr[3] & 0x4) >> 2) ^ ((macAddr[2] & 0x8) >> 3) ^ ((macAddr[1] & 0x10) >> 4) ^ ((macAddr[0] & 0x20) >> 5);
        *pIndex |= tmp_index << 6;

        /* Index_7 = 6 ^ 13 ^ 20 ^ 27 ^ 34 ^ 41 */
        tmp_index = ((macAddr[5] & 0x2) >> 1) ^ ((macAddr[4] & 0x4) >> 2) ^ ((macAddr[3] & 0x8) >> 3) ^ ((macAddr[2] & 0x10) >> 4) ^ ((macAddr[1] & 0x20) >> 5) ^ ((macAddr[0] & 0x40) >> 6);
        *pIndex |= tmp_index << 7;

        /* Index_8 = 5 ^ 12 ^ 19 ^ 26 ^ 33 ^ 40 */
        tmp_index = ((macAddr[5] & 0x4) >> 2) ^ ((macAddr[4] & 0x8) >> 3) ^ ((macAddr[3] & 0x10) >> 4) ^ ((macAddr[2] & 0x20) >> 5) ^ ((macAddr[1] & 0x40) >> 6)  ^ ((macAddr[0] & 0x80) >> 7);
        *pIndex |= tmp_index << 8;
    }
    else  
    {
        /*index direct from mac: LUT index MAC[13:15] + MAC[0:5]*/
        *pIndex = ((macAddr[4] & 0x7) << 6) | ((macAddr[5] & 0xFC) >> 2);
    }

    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_IdxToMac_get
 * Description:
 *      get Mac address for hash index
 * Input:
 *      pIndex        -  the pointer of address table index
 * Output:
 *      macAddr     -   the mac address   
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *   
 */ 
static uint32 rtl8306e_l2_IdxToMac_get(uint8 *macAddr, uint32* pIndex)
{
    uint32 tmp_index, status;
    uint16 regValue; 
    if ((NULL == macAddr) || (NULL == pIndex))
        return FALSE;

    rtl8306e_regbit_get(1, 23, 12, 0, &status);
    
    if (status) 
    {
        /* xor hash algorithm*/

        /*Read Data[47:32]*/
        rtl8306e_reg_get(4, 18, 0, &regValue);
        macAddr[5] = (regValue & 0x300) >> 8; 
        macAddr[4] = regValue & 0xF8;            
  
        /*Read Data[31:16]*/
        rtl8306e_reg_get(4, 19, 0, &regValue);
        macAddr[3] = (regValue & 0xFF00) >> 8; 
        macAddr[2] = regValue & 0xFF;

        /*Read Data[15:0]*/
        rtl8306e_reg_get(4, 20, 0, &regValue);
        macAddr[1] = (regValue & 0xFF00) >> 8;
        macAddr[0] = regValue & 0xFF;

        /* bit 4 =  Index_0 ^ 11 ^ 18 ^ 25 ^ 32; */
        tmp_index = ((*pIndex & 0x4) >> 2) ^ ((macAddr[4] & 0x10) >> 4) ^ ((macAddr[3] & 0x20) >> 5) ^ ((macAddr[2] & 0x40) >> 6) ^  ((macAddr[1] & 0x80) >> 7); 
        macAddr[5] |= (uint8)(tmp_index << 3);
        /* bit 3 =  Index_1 ^ 10 ^ 17 ^ 24 ^ 47 */
        tmp_index = ((*pIndex & 0x8) >> 3) ^ ((macAddr[4] & 0x20) >> 5) ^ ((macAddr[3] & 0x40) >> 6) ^ ((macAddr[2] & 0x80) >> 7) ^ ((macAddr[0] & 0x1) >> 0);
        macAddr[5] |= (uint8)(tmp_index << 4);
        /* bit 2 =  Index_2 ^ 9 ^ 16 ^ 39 ^ 46 */
        tmp_index = ((*pIndex & 0x10) >> 4) ^ ((macAddr[4] & 0x40) >> 6) ^ ((macAddr[3] & 0x80) >> 7) ^ ((macAddr[1] & 0x1) >> 0) ^ ((macAddr[0] & 0x2) >> 1);
        macAddr[5] |= (uint8)(tmp_index << 5);

        /* bit 1 = Index_3 ^ 8 ^ 31 ^ 38 ^ 45 */
        tmp_index = ((*pIndex & 0x20) >> 5) ^ ((macAddr[4] & 0x80) >> 7)  ^ ((macAddr[2] & 0x1) >> 0) ^ ((macAddr[1] & 0x2) >> 1) ^ ((macAddr[0] & 0x4) >> 2);
        macAddr[5] |= (uint8)(tmp_index << 6);

        /* bit 0 = Index_4 ^ 23 ^ 30 ^ 37 ^ 44 */
        tmp_index = ((*pIndex & 0x40) >> 6) ^ ((macAddr[3] & 0x1) >> 0)  ^ ((macAddr[2] & 0x2) >> 1) ^ ((macAddr[1] & 0x4) >> 2) ^ ((macAddr[0] & 0x8) >> 3);
        macAddr[5] |= (uint8)(tmp_index << 7);

        /* bit 15 = Index_5 ^ 22 ^ 29 ^ 36 ^ 43 */
        tmp_index = ((*pIndex & 0x80) >> 7) ^ ((macAddr[3] & 0x2) >> 1) ^ ((macAddr[2] & 0x4) >> 2) ^ ((macAddr[1] & 0x8) >> 3) ^ ((macAddr[0] & 0x10) >> 4);
        macAddr[4] |= (uint8)(tmp_index << 0);
        
        /* bit 14 =  Index_6 ^ 7 ^ 21 ^ 28 ^ 35 ^ 42 */
        tmp_index = ((*pIndex & 0x100) >> 8) ^ ((macAddr[5] & 0x1) >> 0) ^ ((macAddr[3] & 0x4) >> 2) ^ ((macAddr[2] & 0x8) >> 3) ^ ((macAddr[1] & 0x10) >> 4) ^ ((macAddr[0] & 0x20) >> 5);
        macAddr[4] |= (uint8)(tmp_index << 1);

        /* bit 13 =  Index_7 ^ 6 ^ 20 ^ 27 ^ 34 ^ 41 */
        tmp_index = ((*pIndex & 0x200) >> 9) ^ ((macAddr[5] & 0x2) >> 1) ^ ((macAddr[3] & 0x8) >> 3) ^ ((macAddr[2] & 0x10) >> 4) ^ ((macAddr[1] & 0x20) >> 5) ^ ((macAddr[0] & 0x40) >> 6);
        macAddr[4] |= (uint8)(tmp_index << 2);
        
        /* bit 5 =  Index_8 ^ 12 ^ 19 ^ 26 ^ 33 ^ 40 */
        tmp_index = ((*pIndex & 0x400) >> 10) ^ ((macAddr[4] & 0x8) >> 3) ^ ((macAddr[3] & 0x10) >> 4) ^ ((macAddr[2] & 0x20) >> 5) ^ ((macAddr[1] & 0x40) >> 6)  ^ ((macAddr[0] & 0x80) >> 7);
        macAddr[5] |= (uint8)(tmp_index << 2);
 
    }
    else  
    {
        /*Read Data[47:32]*/
      rtl8306e_reg_get(4, 18, 0, &regValue);
      macAddr[5] = ((regValue & 0x300) >> 8) | (*pIndex & 0xFC);
      macAddr[4] = (regValue & 0xF8) | ((*pIndex >> 8) & 0x7);

      /*Read Data[31:16]*/
      rtl8306e_reg_get(4, 19, 0, &regValue);
      macAddr[3] = (regValue & 0xFF00) >> 8;
      macAddr[2] = regValue & 0xFF;

      /*Read Data[15:0]*/
      rtl8306e_reg_get(4, 20, 0, &regValue);
      macAddr[1] = (regValue & 0xFF00) >> 8;
      macAddr[0] = regValue & 0xFF;
    }
    
    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_unicastEntry_set
 * Description:
 *      write an unicast mac address into L2 table
 * Input:
 *      macAddress        -  Specify the unicast Mac address(6 bytes) to be written into LUT
 *      entry                 -  Specify the 4-way entry to be written (0~3)
 *      age                   -  Specify age time
 *      isStatic              -  TRUE(static entry), FALSE(dynamic entry)
 *      isAuth                -  Whether the mac address is authorized by IEEE 802.1x
 *      port                  -   Specify the port number to be forwarded to  
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      Age time has 4 value :
 *          RTL8306_LUT_AGEOUT, 
 *          RTL8306_LUT_AGE100(100s)
 *          RTL8306_LUT_AGE200(200s)
 *          RTL8306_LUT_AGE300(300s)
 */ 

uint32 rtl8306e_l2_unicastEntry_set(uint8 *macAddress, uint32 entry, uint32 age, uint32 isStatic, uint32 isAuth, uint32 port) 
{
    uint32 regValue, index, pollcnt;
    uint32 bitValue;

    if ((NULL == macAddress) || (entry > RTL8306_LUT_ENTRY3) || (age > RTL8306_LUT_AGE300) ||
        (port > RTL8306_PORT5))
        return FALSE;

    /*For unicast entry, MAC[47] is 0  */
    if (macAddress[0] & 0x1)
        return FALSE;
    
    /*Enable lookup table access*/
    rtl8306e_regbit_set(0, 16, 13, 0, 1);
    
    /*Write Data[55:48]*/
    if (RTL8306_LUT_AGE300 == age) 
        age = 0x2;
    else if (RTL8306_LUT_AGE200 == age)
        age = 0x3;
    else if (RTL8306_LUT_AGE100 == age)
        age = 0x1;
    else 
        age = 0;

    regValue = ((isAuth ? 1:0 ) << 7) | ((isStatic ? 1:0) << 6) | (age << 4) | port;
    rtl8306e_reg_set(4, 17, 0, regValue & 0xFF);
    /*write Data[47:32]*/
    rtl8306e_reg_set(4, 18, 0, macAddress[5] << 8 | macAddress[4]);
    /*wrtie Data[31:16]*/
    rtl8306e_reg_set(4, 19, 0, macAddress[3] << 8 | macAddress[2]);
    /*wrtie Data[15:0]*/
    rtl8306e_reg_set(4, 20, 0, macAddress[1] << 8 | macAddress[0]);

    /*LUT index */
    rtl8306e_l2_MacToIdx_get(macAddress, &index);

    /*Write Command, 2-bit indicating four-way lies in highest bit of Entry_Addr[10:0]*/
    regValue = (entry << 13) | (index << 4) | 0x0;
    rtl8306e_reg_set(4, 16, 0, regValue);
    rtl8306e_regbit_set(4, 16, 1, 0, 1);
    
    /*Waiting for write command done and prevent polling dead loop*/
    for (pollcnt = 0; pollcnt < RTL8306_IDLE_TIMEOUT; pollcnt ++) 
    {
        rtl8306e_regbit_get(4, 16, 1, 0, &bitValue);
        if (!bitValue)
            break;
    }
    if (pollcnt == RTL8306_IDLE_TIMEOUT)
        return FALSE;

    /*Disable lookup table access*/
    rtl8306e_regbit_set(0, 16, 13, 0, 0);
 #ifdef RTL8306_LUT_CACHE
     memcpy(rtl8306_LutCache[ (index << 2) | entry].mac, macAddress, 6);
     rtl8306_LutCache[ (index << 2) | entry].un.unicast.auth = isAuth;
     rtl8306_LutCache[ (index << 2) | entry].un.unicast.spa= port;
     rtl8306_LutCache[ (index << 2) | entry].un.unicast.isStatic= isStatic;
     rtl8306_LutCache[ (index << 2) | entry].un.unicast.age= age;
 #endif
    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_unicastEntry_get
 * Description:
 *      read an unicast mac address into L2 table
 * Input:
 *      entry               -  Specify the entry address to be read (0 ~ 2047), not four-way entry
 * Output:
 *      macAddress      -  the mac to be saved in the entry  
 *      pAge               -  the pointer of the age time
 *      pIsStatic         -   the pointer of static or dynamic entry
 *      pIsAuth           -   the pointer of IEEE 802.1x authorized status
 *      pPort              -   the pointer of the port the mac belongs to   
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      Age time has 4 value :
 *          RTL8306_LUT_AGEOUT
 *          RTL8306_LUT_AGE100(100s)
 *          RTL8306_LUT_AGE200(200s)
 *          RTL8306_LUT_AGE300(300s)
 */ 
 
uint32 rtl8306e_l2_unicastEntry_get(uint8 *macAddress, uint32 entryAddr, uint32 *pAge, uint32 *pIsStatic, uint32 *pIsAuth, uint32 *pPort) 
{
    uint32 entryAddrHd;
    uint16 regValue;
	uint32 pollcnt;
    uint32 bitValue;

    if ((NULL == macAddress) || (entryAddr > 0x7FF) || (NULL == pAge) || (NULL == pIsStatic) ||
        (pIsAuth == NULL) || (pPort == NULL))
        return FALSE;
    
    /*Hardware data format, four-way info is the highest 2 bits of 11-bit entry info*/
    entryAddrHd = (entryAddr >> 2) | ((entryAddr & 0x3) << 9);
    
    /*Enable lookup table access*/
    rtl8306e_regbit_set(0, 16, 13, 0, 1);
    /*Read Command*/
    regValue = (entryAddrHd << 4) | 0x1;
    rtl8306e_reg_set(4, 16, 0, regValue);
    rtl8306e_regbit_set(4, 16, 1, 0, 1);
    
    /*Waiting for Read command done and prevent polling dead loop*/
    for (pollcnt = 0; pollcnt < RTL8306_IDLE_TIMEOUT; pollcnt ++) 
    {
        rtl8306e_regbit_get(4, 16, 1, 0, &bitValue);
        if (!bitValue)
            break;
    }
    if (pollcnt == RTL8306_IDLE_TIMEOUT)
        return FALSE;
    
    /*Read Data[55:48]*/
    rtl8306e_reg_get(4, 17, 0, &regValue);
    *pIsAuth = (regValue & 0x80) ? TRUE: FALSE;
    *pIsStatic = (regValue & 0x40) ? TRUE:FALSE;
    *pAge = (regValue & 0x30) >> 4;
    if (*pAge == 0x2) 
        *pAge = RTL8306_LUT_AGE300;
    else if (*pAge == 0x3)
        *pAge = RTL8306_LUT_AGE200;
    else if (*pAge == 0x1 )
        *pAge = RTL8306_LUT_AGE100;
    else 
        *pAge = RTL8306_LUT_AGEOUT;
    *pPort = regValue & 0x7;

    rtl8306e_l2_IdxToMac_get(macAddress, &entryAddr);

    /*Disable lookup table access*/
    rtl8306e_regbit_set(0, 16, 13, 0, 0);
    return TRUE;
}

#ifdef RTL8306_LUT_CACHE
 
uint32 rtl8306e_fastGetAsicLUTUnicastEntry(uint8 *macAddress, uint32 entryAddr, uint32 *pAge, uint32 *pIsStatic, uint32 *pIsAuth, uint32 *pPort) 
{    
    if ((NULL == macAddress) || (entryAddr > 0x7FF) || (NULL == pAge) || (NULL == pIsStatic ) ||
        (NULL == pIsAuth) || (NULL == pPort))
        return FALSE;

    memcpy(macAddress, rtl8306_LutCache[entryAddr].mac, 6);

    *pIsStatic= rtl8306_LutCache[entryAddr].un.unicast.isStatic;
    *pIsAuth = rtl8306_LutCache[entryAddr].un.unicast.auth;
    *pPort   = rtl8306_LutCache[entryAddr].un.unicast.spa;
    *pAge     = rtl8306_LutCache[entryAddr].un.unicast.age;

    return TRUE;
}

uint32 rtl8306e_fastGetAsicLUTMulticastEntry(uint8 *macAddress, uint32 entryAddr, uint32 *pIsAuth, uint32 *pPortMask) 
{
    
    if ((NULL == macAddress) || (entryAddr > 0x7FF) ||(NULL == pIsAuth) || (NULL == pPortMask))
        return FALSE;
    memcpy(macAddress, rtl8306_LutCache[entryAddr].mac, 6);

    *pIsAuth = rtl8306_LutCache[entryAddr].un.multicast.auth;
    *pPortMask = rtl8306_LutCache[entryAddr].un.multicast.portMask;

    return TRUE;
}

#endif
/* Function Name:
 *      rtl8306e_l2_multicastEntry_set
 * Description:
 *      write an multicast mac address into L2 table
 * Input:
 *      macAddress      -  the mac to be saved in the entry  
 *      entry               -  Specify the 4-way entry to be written (0~3)
 *      isAuth              -  IEEE 802.1x authorized status
 *      portMask          -  switch received thepacket with the specified macAddress, 
 *                                and forward it to the member port of portMask
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      get 9-bit as index value of lookup table by hashing the mac address , for each index value, 
 *      there are 4-entry to save hash collision mac address, thus there are 2048 entries all together.
 *      the entry could save both unicast multicast mac address.  multicast entry has no age time and
 *      static bit, which has been set by software, unicast entry could be both auto learned and set by 
 *      software. you had better set isAuth TRUE for general application because  IEEE 802.1x is usually
 *      for unicast packet.portMask is 6-bit value, each bit represents one port, bit 0 corresponds to port 0
 *      and bit 5 corresponds port 5.
 */ 

uint32 rtl8306e_l2_multicastEntry_set(uint8 *macAddress, uint32 entry, uint32 isAuth, uint32 portMask) 
{
    uint32 regValue, index, pollcnt;
    uint32 bitValue;

    if ((NULL == macAddress) || (entry > RTL8306_LUT_ENTRY3) || (portMask > 0x3F ))
        return FALSE;

    /*For Muticast entry, MAC[47] is 1  */
    if (!(macAddress[0] & 0x1))
        return FALSE;
    
    /*Enalbe Lookup table access*/
    rtl8306e_regbit_set(0, 16, 13, 0, 1);
    
    /*Write Data[55:48]*/
    /*Multicast entry portmask bits is Data[54:52], Data[50:48]*/
    regValue = ((isAuth ? 1: 0) << 7) | (portMask & 0x38) << 1 | (portMask & 0x7); 
    rtl8306e_reg_set(4, 17, 0, regValue);
    /*Write Data[47:32]*/
    rtl8306e_reg_set(4, 18, 0, (macAddress[5] << 8) |macAddress[4]);
    /*Write Data[31:16]*/
    rtl8306e_reg_set(4, 19, 0, (macAddress[3] << 8) |macAddress[2]);
    /*Write Data[15:0]*/
    rtl8306e_reg_set(4, 20, 0, (macAddress[1] << 8) |macAddress[0]);

    /*LUT index */
    rtl8306e_l2_MacToIdx_get(macAddress, &index);

    /*Write Command, 2-bit indicating four-way lies in highest bit of Entry_Addr[10:0]*/
    regValue = (entry << 13) | (index << 4) | 0x2;
    rtl8306e_reg_set(4, 16, 0, regValue);
    
    /*Waiting for write command done and prevent polling dead loop*/
    for (pollcnt = 0; pollcnt < RTL8306_IDLE_TIMEOUT; pollcnt ++)
    {
        rtl8306e_regbit_get(4, 16, 1, 0, &bitValue);
        if (!bitValue)
          break;
    }
    
    if (pollcnt == RTL8306_IDLE_TIMEOUT)
        return FALSE;
    
    /*Disable Lookup table access*/
    rtl8306e_regbit_set(0, 16, 13, 0, 0);
    /*record it in software cache if define RTL8306_LUT_CACHE*/
 #ifdef RTL8306_LUT_CACHE
     memcpy(rtl8306_LutCache[ (index << 2) | entry].mac, macAddress, 6);
     rtl8306_LutCache[ (index << 2) | entry].un.multicast.auth = isAuth;
     rtl8306_LutCache[ (index << 2) | entry].un.multicast.portMask= portMask;
 #endif
    return TRUE;
}

/* Function Name:
 *      rtl8306_getAsicLUTMulticastEntry
 * Description:
 *      Get LUT multicast entry
 * Input:
 *      entryAddr         -  Specify the LUT entry address(0~2047)

 * Output:
 *      macAddress      -  The read out multicast Mac address  
 *      pIsAuth            -  the pointer of IEEE 802.1x authorized status
 *      portMask          -  port mask 
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      Get multicast entry
 */ 

uint32 rtl8306e_l2_multicastEntry_get(uint8 *macAddress, uint32 entryAddr, uint32 *pIsAuth, uint32 *pPortMask) 
{
    uint32 entryAddrHd;
    uint16 regValue;
	uint32 pollcnt;
    uint32 bitValue;

    if ((NULL == macAddress) || (entryAddr > 0x7FF) ||(NULL == pIsAuth) || (NULL == pPortMask))
        return FALSE;

    /*Hardware data format, four-way info is the highest 2 bits of 11-bit entry info*/
    entryAddrHd = (entryAddr >> 2) | ((entryAddr & 0x3) << 9);
    
    /*Enalbe Lookup table access*/
    rtl8306e_regbit_set(0, 16, 13, 0, 1);
    
    /*Write Command*/
    regValue = (entryAddrHd << 4) | 0x3;
    rtl8306e_reg_set(4, 16, 0, regValue);
    
    /*Waiting for Read command done and prevent polling dead loop*/
    for (pollcnt = 0; pollcnt < RTL8306_IDLE_TIMEOUT; pollcnt ++) 
    {
        rtl8306e_regbit_get(4, 16, 1, 0, &bitValue);
        if (!bitValue)
            break;
    }
    if (pollcnt == RTL8306_IDLE_TIMEOUT)
        return FALSE;
    
    /*Read Data[55:48]*/
    rtl8306e_reg_get(4, 17, 0, &regValue);
    *pIsAuth = (regValue & 0x80 ? 1:0);
    
    /*Multicast entry portmask bits is Data[54:52], Data[50:48]*/
    *pPortMask = ((regValue & 0x70) >> 4) << 3 | (regValue & 0x7);

    rtl8306e_l2_IdxToMac_get(macAddress, &entryAddr);

    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_unicastMac_add
 * Description:
 *     Add an unicast mac address, software will detect empty entry
 * Input:
 *      macAddress      -  the mac to be saved in the entry  
 *      age                 -  Specify age time
 *      isStatic            -  TRUE(static entry), FALSE(dynamic entry)
 *      isAuth              -  IEEE 802.1x authorized status
 *      port                 -  the port which the mac address belongs to  
 * Output:
 *      pEntryaddr        -   the entry address (0 ~2047) which the unicast mac address is written into
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      Age time has 4 value :RTL8306_LUT_AGEOUT, RTL8306_LUT_AGE100(100s), 
 *      RTL8306_LUT_AGE200(200s), RTL8306_LUT_AGE300(300s)
 *      The lut has a 4-way entry of an index. If the macAddress has existed in the lut, it will update the entry,
 *      otherwise the function will find an empty entry to put it.
 *      When the index is full, it will find a dynamic & unauth unicast macAddress entry to replace with it. 
 *      If the mac address has been written into LUT, function return value is TRUE,  *pEntryaddr is recorded the
 *      entry address of the Mac address stored.
 *      If all the four entries can not be replaced, it will return a  RTL8306_LUT_FULL error, you can delete one of them 
 *      and rewrite the unicast address.  
 */ 

int32 rtl8306e_l2_unicastMac_add(uint8 *macAddress, uint32 age, uint32 isStatic, uint32 isAuth, uint32 port, uint32 *pEntryaddr)
{
    int32 i;
    uint8 macAddr[6];
    uint32 index,entryaddr;
    uint32 isStatic1,isAuth1,age1,port1;

    /*check for macAddress. must be unicast address*/
    if( (NULL == macAddress) || (macAddress[0] & 0x1))
        return FALSE;

    /*check port*/
    if (port > 5)
        return FALSE;

    rtl8306e_l2_MacToIdx_get(macAddress, &index);

    /*
      *First scan four-ways, if the unicast entry has existed, only update the entry, that could 
      *prevent two same Mac in four-ways; if the mac was not written into entry before, then scan 
      *four-ways again, to Find an dynamic & unauthorized unicast entry which is auto learned, then  
      *replace it with the multicast Mac addr. scanning sequence is from entry 3 to entry 0, because 
      *priority of four way is entry 3 > entry 2 > entry 1 > entry 0
      */
    for (i = 3; i >= 0; i--) 
    {
        entryaddr = (index << 2) | (uint32)i;
        if (rtl8306e_l2_unicastEntry_get(macAddr, entryaddr, &age1, &isStatic1, &isAuth1, &port1) != TRUE)
        {
            return FALSE;
        }
        else if ((macAddress[0] == macAddr[0]) && (macAddress[1] == macAddr[1]) && 
                   (macAddress[2] == macAddr[2]) && (macAddress[3] == macAddr[3]) &&
                    (macAddress[4] == macAddr[4]) && (macAddress[5] == macAddr[5])) 
        {
            rtl8306e_l2_unicastEntry_set(macAddress, (uint32)i , age, isStatic, isAuth, port);
            *pEntryaddr = entryaddr;
            return TRUE;
        }
    }
    
    for (i = 3; i >= 0; i--) 
    {
        entryaddr = (index << 2) | (uint32)i ;
        if (rtl8306e_l2_unicastEntry_get(macAddr, entryaddr, &age1, &isStatic1, &isAuth1, &port1) != TRUE)
        {
            return FALSE;
        }
        else if (((macAddr[0] & 0x1) == 0) && (!isStatic1) && (!isAuth1))  
        {
            rtl8306e_l2_unicastEntry_set(macAddress, (uint32)i , age, isStatic, isAuth, port);
            *pEntryaddr = entryaddr;
            return TRUE;
        }
    }

    /* four way are all full, return RTL8306_LUT_FULL*/
    return RTL8306_LUT_FULL;
}


/* Function Name:
 *      rtl8306e_l2_multicastMac_add
 * Description:
 *     Add an multicast mac address, software will detect empty entry
 * Input:
 *      macAddress      -  the mac to be saved in the entry  
 *      isAuth              -  IEEE 802.1x authorized status
 *      portMask          -  switch received the packet with the specified macAddress, 
 *                                and forward it to the member port of portMask
 * Output:
 *      pEntryaddr        -   the entry address (0 ~2047) which the multicast mac address is written into
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      Add an multicast entry, it need not specify the 4-way like function rtl8306e_l2_multicastEntry_set,
 *      if the mac address has written into LUT, function return value is TRUE,  *pEntryaddr is recorded the
 *      entry address of the Mac address stored, if  4-way entries are all written by cpu, this mac address could 
 *      not written into LUT and the function return value is  RTL8306_LUT_FULL, but if the Mac address has exist, 
 *      the port mask will be updated. When function return value is RTL8306_LUT_FULL, you can delete one of them 
 *      and rewrite the multicast address. 
 */ 
int32  rtl8306e_l2_multicastMac_add(uint8 *macAddr,uint32 isAuth, uint32 portMask, uint32 *pEntryaddr) 
{
    int32  i;
    uint8 macAddress[4][6];
    uint32 index, entryAddress[4], age[4];
    uint32 isStatic[4], isAuthority[4];
    uint32 port[4];
    uint32 isFull = TRUE;


    if ((NULL == macAddr) || (!(macAddr[0] & 0x1)) || (NULL == pEntryaddr))
        return FALSE;

    rtl8306e_l2_MacToIdx_get(macAddr, &index);

    /*
      *First scan four-ways, if the multicast entry has existed, only update the entry, that could 
      *prevent two same Mac in four-ways; if the mac was not written into entry before, then scan 
      *four-ways again, to Find an dynamic & unauthorized unicast entry which is auto learned, then  
      *replace it with the multicast Mac addr. scanning sequence is from entry 3 to entry 0, because priority
      *of four way is entry 3 > entry 2 > entry 1 > entry 0
      */
    for (i = 3; i >= 0; i--) 
    {
        entryAddress[i] = (index << 2) | (uint32)i;
#ifdef RTL8306_LUT_CACHE
        if (rtl8306e_fastGetAsicLUTUnicastEntry(macAddress[i], entryAddress[i], &age[i], &isStatic[i], &isAuthority[i], &port[i]) != TRUE)
#else
        if (rtl8306e_l2_unicastEntry_get(macAddress[i], entryAddress[i], &age[i], &isStatic[i], &isAuthority[i], &port[i]) != TRUE)
#endif
        {
            return FALSE;
        }
        else if ((macAddr[0] == macAddress[i][0]) && (macAddr[1] == macAddress[i][1]) && 
                    (macAddr[2] == macAddress[i][2]) && (macAddr[3] == macAddress[i][3]) &&
                    (macAddr[4] == macAddress[i][4]) && (macAddr[5] == macAddress[i][5])) 
        {
            rtl8306e_l2_multicastEntry_set(macAddr, (uint32)i, isAuth, portMask);
            *pEntryaddr = entryAddress[i];
            isFull = FALSE;
            return TRUE;
        }
    }
    
    for (i = 3; i >= 0; i--) 
    {
        if (((macAddress[i][0] & 0x1) == 0) && (!isStatic[i]) && (!isAuthority[i])) 
        {
            rtl8306e_l2_multicastEntry_set(macAddr, (uint32)i , isAuth, portMask);
            *pEntryaddr = entryAddress[i];
            isFull = FALSE;
            break;
        }
    }

    /*If four way are all full, return RTL8306_LUT_FULL*/
    if (isFull) 
    {
        *pEntryaddr = 10000;
        return RTL8306_LUT_FULL;
    }
    return TRUE;

}

/* Function Name:
 *      rtl8306e_l2_mac_get
 * Description:
 *      Get an mac address information
 * Input:
 *      macAddress         -   the mac to be find in LUT  
 * Output:
 *      pIsStatic             -   the pointer of static or dynamic entry, for unicast mac address
 *      pIsAuth               -   the pointer of IEEE 802.1x authorized status
 *      pPortInfo             -   for unicast mac, it is the pointer of the port the mac belongs to;
 *                                    for multicast mac, it is the pointer of portmask the mac forwarded to;
 *      pEntryaddr           -   the entry address (0 ~2047) which the mac address is written into
 * Return:
 *      TRUE
 *      FALSE
 *      RTL8306_LUT_NOTEXIST
 * Note:
 *      use this API to get a mac address information in LUT.
 */ 
int32 rtl8306e_l2_mac_get(uint8 *macAddr, uint32 *pIsStatic, uint32 *pIsAuth, uint32 *pPortInfo, uint32 *pEntryaddr) 
{
    int32  i;
    uint8 macAddress[6];
    uint32 index, entryAddress, age;
    uint32 isStatic, isAuth;
    uint32 port, portmask;
    uint32 isHit ;

    if((NULL == macAddr) || (NULL == pIsAuth) || (NULL == pPortInfo) || (NULL == pEntryaddr))
        return FALSE;
    
    isHit = FALSE;
    
    rtl8306e_l2_MacToIdx_get(macAddr, &index);

    /*scanning sequence is from entry 3 to entry 0, because priority
      *of four way is entry 3 > entry 2 > entry 1 > entry 0
      */
    for (i = 3; i >= 0; i--) 
    {
        entryAddress = (index << 2) |(uint32) i;
        if (rtl8306e_l2_unicastEntry_get(macAddress, entryAddress, &age, &isStatic, &isAuth, &port) != TRUE)
        {
            return FALSE;
        }
        else if ((macAddr[0] == macAddress[0]) && (macAddr[1] == macAddress[1]) && 
                    (macAddr[2] == macAddress[2]) && (macAddr[3] == macAddress[3]) &&
                    (macAddr[4] == macAddress[4]) && (macAddr[5] == macAddress[5])) 
        {
            if(macAddr[0] & 0x1)
            {
                rtl8306e_l2_multicastEntry_get(macAddress, entryAddress, &isAuth, &portmask);
                *pIsStatic = TRUE;
                *pIsAuth = isAuth;
                *pPortInfo = portmask;
            }
            else 
            {
                *pIsStatic = isStatic;
                *pIsAuth = isAuth;
                *pPortInfo = port;
                if ((RTL8306_LUT_AGEOUT == age) && !isStatic && !isAuth)
                    return  RTL8306_LUT_NOTEXIST;                                                                  
            }

            *pEntryaddr = entryAddress;
            isHit = TRUE;
            return TRUE;
        }
    }

    if(!isHit)
        return RTL8306_LUT_NOTEXIST;

    return TRUE;
}
    

/* Function Name:
 *      rtl8306e_l2_mac_del
 * Description:
 *     Delete the specified Mac address, could be both unicast and multicast 
 * Input:
 *      macAddress      -  the Mac address(unicast or multicast) to be delete  
 *                                and forward it to the member port of portMask
 * Output:
 *      pEntryaddr        -  entry address from which the Mac address is deleted
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      Use this function to delete a Mac address, it does not require to specify the 
 *      entry address, if the Mac has existed in the LUT, it will be deleted and function
 *      return value is TRUE, *pEntryaddr is recorded the entry address of the Mac
 *      address stored. if the Mac does not existed in the LUT, function return value is
 *      RTL8306_LUT_NOTEXIST, and *pEntryaddr equals 10000.
 */ 
int32 rtl8306e_l2_mac_del(uint8 *macAddr, uint32 *pEntryaddr)
{
    uint32  i, port, portmask;
    uint8 macAddr1[6];
    uint32 index, entryaddr1, age;
    uint32 isStatic, isAuth;
    uint32 isHit = FALSE;
    uint32 hashStatus;
    
    if ((NULL == macAddr) || (NULL == pEntryaddr))
        return FALSE;

    rtl8306e_l2_MacToIdx_get(macAddr, &index);
    
    if (!(macAddr[0] & 0x1)) 
    {  
        /*Delete an unicast entry*/
        for (i = 4; i >= 1; i --) 
        {
            entryaddr1 = (index << 2) | (i - 1);
            if(rtl8306e_l2_unicastEntry_get(macAddr1, entryaddr1, &age, &isStatic, &isAuth, &port) != TRUE)
                return FALSE;
            else if (macAddr[0] ==macAddr1[0] && macAddr[1] ==macAddr1[1] 
                       && macAddr[2] ==macAddr1[2] && macAddr[3] ==macAddr1[3]
                       && macAddr[4] ==macAddr1[4] && macAddr[5] ==macAddr1[5]) 
            {  
                rtl8306e_l2_unicastEntry_set(macAddr, i -1, 0, FALSE, FALSE, port);
                *pEntryaddr = entryaddr1;
                isHit = TRUE;
            } 
        }
    }
    else 
    {
        /*Delet an multicast entry*/
        for (i = 4; i >= 1; i --)
        {
            entryaddr1 = (index << 2) | (i - 1);
#ifdef RTL8306_LUT_CACHE
            if(rtl8306e_fastGetAsicLUTMulticastEntry(macAddr1, entryaddr1, &isAuth, &portmask) == FALSE)
#else
            if(rtl8306e_l2_multicastEntry_get(macAddr1, entryaddr1, &isAuth, &portmask) != TRUE)
#endif
                return FALSE;
            else if (macAddr[0] ==macAddr1[0] && macAddr[1] ==macAddr1[1] 
                       && macAddr[2] ==macAddr1[2] && macAddr[3] ==macAddr1[3]
                       && macAddr[4] ==macAddr1[4] && macAddr[5] ==macAddr1[5]) 
            {  
               /*
                 * Turn multicast address to unicast address. If new hash is used 
                 * bit 24 will be performed not operation to make the Index unchange
                 */
                rtl8306e_regbit_get(1, 23, 12, 0, &hashStatus);            

                if (hashStatus) 
                {
                    macAddr1[0] = macAddr1[0] & 0xFE; 
                    macAddr1[2] ^= 0x80;
                } 
                else 
                {
                    macAddr1[0] = macAddr1[0] & 0xFE; 
                }
                
                if (rtl8306e_l2_unicastEntry_set(macAddr1, (uint32)(i -1), 0, FALSE, FALSE, 0) != TRUE)
                    return FALSE;
                *pEntryaddr = entryaddr1;
                isHit = TRUE;
            } 
        }

    }

    if (!isHit) 
    {
        *pEntryaddr = 10000;
        return RTL8306_LUT_NOTEXIST;
    }
    else 
        return TRUE;

}

/* Function Name:
 *      rtl8306e_l2_portMacLimit_set
 * Description:
 *      Set per port mac limit ability and auto learning limit number
 * Input:
 *      port         -  port number (0 ~ 5)  
 *      enabled    - TRUE of FALSE  
 *      macCnt    - auto learning MAC limit number
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */ 
uint32 rtl8306e_l2_portMacLimit_set(uint32 port, uint32 enabled, uint32 macCnt) 
{
    uint16 regValue;

    if (port > RTL8306_PORT5)
        return FALSE;
    if (5 == port)
        port ++;

    if (0 == port)
    {
        rtl8306e_regbit_set(0, 26, 12, 3, enabled ? 1 : 0);
        rtl8306e_reg_get(0, 27, 3, &regValue);
        regValue &= ~(0x1F << 11);
        regValue |= ((macCnt & 0x1F) << 11);
        rtl8306e_reg_set(0, 27, 3, regValue);
    }
    else
    {
        rtl8306e_regbit_set(port, 30, 15, 1, enabled ? 1 : 0);
        rtl8306e_reg_get(port, 31, 1, &regValue);
        regValue &= ~(0x1F << 11);
        regValue |= ((macCnt & 0x1F) << 11);
        rtl8306e_reg_set(port, 31, 1, regValue);
    }
 
    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_portMacLimit_get
 * Description:
 *      Get per port mac limit ability and auto learning limit number
 * Input:
 *      port         -  port number (0 ~ 5)  
 * Output:
 *      pEnabled    -  enabled or disabled the port mac limit
 *      pMacCnt     -  auto learning MAC limit number
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */ 
uint32 rtl8306e_l2_portMacLimit_get(uint32 port, uint32 *pEnabled, uint32 *pMacCnt) 
{
    uint16 regValue;
    uint32 bitValue;

    if (port > RTL8306_PORT5 || NULL == pEnabled || NULL == pMacCnt)
        return FALSE;
    if (5 == port)
        port ++;

    if (0 == port)
    {
        rtl8306e_regbit_get(0, 26, 12, 3, &bitValue);
        *pEnabled = bitValue ? TRUE : FALSE;
        rtl8306e_reg_get(0, 27, 3, &regValue);
        *pMacCnt = (regValue & (0x1F << 11)) >> 11;
    }
    else
    {
        rtl8306e_regbit_get(port, 30, 15, 1, &bitValue);
        *pEnabled = bitValue ? TRUE : FALSE;
        rtl8306e_reg_get(port, 31, 1, &regValue);
        *pMacCnt = (regValue & (0x1F << 11)) >> 11;
    }
 
    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_systemMacLimit_set
 * Description:
 *      Set the system mac limit ability and auto learning limit number
 * Input:
 *      enabled    - TRUE of FALSE  
 *      macCnt    - system auto learning MAC limit number
 *      mergMask  -  port mask for the ports merged to system mac limit
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      Besides per port mac limit function, 8306E also supports system MAC limit function.
 *      mergMask is to decide whitch ports are limited by system MAC limit function.
 *      For example, when system mac limit is enabled, and mergMask is 0x15(0b010101),
 *      that means the auto learning MAC number of port 0, port 2 and port 4 will also be
 *      influenced by system MAC limit.    
 */ 
uint32 rtl8306e_l2_systemMacLimit_set(uint32 enabled, uint32 macCnt, uint32 mergMask) 
{
    uint16 regValue;

    rtl8306e_regbit_set(0, 26, 11, 3, enabled ? 1 : 0);
    
    rtl8306e_reg_get(0, 31, 0, &regValue);
    regValue &= ~(0x7F);
    regValue |= (macCnt & 0x7F) ;
    rtl8306e_reg_set(0, 31, 0, regValue);
    
    rtl8306e_reg_get(0, 31, 0, &regValue);
    regValue &= ~(0x3F << 10);
    regValue |= ((mergMask & 0x3F) << 10);
    rtl8306e_reg_set(0, 31, 0, regValue);
 
    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_systemMacLimit_get
 * Description:
 *      Get the system mac limit ability and auto learning limit number
 * Input:
 *      none
 * Output:
 *      pEnabled    -  enabled or disabled the system mac limit
 *      pMacCnt    -   system auto learning MAC limit number
 *      pMergMask  -  port mask for the ports merged to system mac limit
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */ 
uint32 rtl8306e_l2_systemMacLimit_get(uint32 *pEnabled, uint32 *pMacCnt, uint32 *pMergMask) 
{
    uint16 regValue;
    uint32 bitValue;

    rtl8306e_regbit_get(0, 26, 11, 3, &bitValue);
    *pEnabled = bitValue ? TRUE : FALSE;
    
    rtl8306e_reg_get(0, 31, 0, &regValue);
    *pMacCnt = (regValue & 0x7F);
    
    rtl8306e_reg_get(0, 31, 0, &regValue);
    *pMergMask = (regValue & (0x3F << 10)) >> 10;
    
    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_macLimitAction_set
 * Description:
 *      Set the action taken by switch when auto learning MAC reach to the limit number
 * Input:
 *      action      -  the action taken when auto learning MAC reach to the max value 
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */ 
uint32 rtl8306e_l2_macLimitAction_set(uint32 action) 
{
    if (RTL8306_ACT_DROP == action)
        rtl8306e_regbit_set(0, 31, 9, 0, 0);
    else if (RTL8306_ACT_TRAPCPU == action)
        rtl8306e_regbit_set(0, 31, 9, 0, 1);
    else
        return FALSE;

    return TRUE;
}

/* Function Name:
 *      rtl8306e_l2_macLimitAction_get
 * Description:
 *      Get the action taken by switch when auto learning MAC reach to the limit number
 * Input:
 *      pAction      -  the action taken when auto learning MAC reach to the max value
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 */ 
uint32 rtl8306e_l2_macLimitAction_get(uint32 *pAction) 
{
    uint32 bitValue;

    if (NULL == pAction)
        return FALSE;
    
    rtl8306e_regbit_get(0, 31, 9, 0, &bitValue);
    if (bitValue)
        *pAction = RTL8306_ACT_TRAPCPU;
    else
        *pAction = RTL8306_ACT_DROP;

    return TRUE;
}

/* Function Name:
 *      rtl8306e_stp_set
 * Description:
 *      Set IEEE 802.1d port state
 * Input:
 *      port   -  Specify port number (0 ~ 5)
 *      state -   Specify port state
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *     There are 4 port state:
 *         RTL8306_SPAN_DISABLE   - Disable state
 *         RTL8306_SPAN_BLOCK      - Blocking state
 *         RTL8306_SPAN_LEARN      - Learning state
 *         RTL8306_SPAN_FORWARD - Forwarding state
 */ 
uint32 rtl8306e_stp_set(uint32 port, uint32 state) 
{
    uint16 regValue;

    if ((port > RTL8306_PORT5) || (state > RTL8306_SPAN_FORWARD))
        return FALSE;

    /*Enable BPDU to trap to cpu, BPDU could not be flooded to all port*/
    rtl8306e_regbit_set(2, 21, 6, 3, 1);
    rtl8306e_reg_get(4, 21, 3, &regValue);
    regValue = (regValue & (~(0x3 << (2*port)))) | (state << (2*port));
    rtl8306e_reg_set(4, 21, 3, regValue);

#ifdef RTL8306_TBLBAK
    rtl8306_TblBak.dot1DportCtl[port] = (uint8)state;
#endif
    return TRUE;
}

/* Function Name:
 *      rtl8306e_stp_get
 * Description:
 *      Get IEEE 802.1d port state
 * Input:
 *      port    -  Specify port number (0 ~ 5)
 * Output:
 *      pState -  get port state
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *     There are 4 port state:
 *         RTL8306_SPAN_DISABLE   - Disable state
 *         RTL8306_SPAN_BLOCK      - Blocking state
 *         RTL8306_SPAN_LEARN      - Learning state
 *         RTL8306_SPAN_FORWARD - Forwarding state
 */ 
uint32 rtl8306e_stp_get(uint32 port, uint32 *pState) 
{
    uint16 regValue;

    if ((port > RTL8306_PORT5) || (NULL == pState))
        return FALSE;
    
    rtl8306e_reg_get(4, 21, 3, &regValue);
    *pState = (regValue & (0x3 << (2*port))) >> (2*port);
    return TRUE;
}

/* Function Name:
 *      rtl8306e_dot1x_portBased_set
 * Description:
 *      Set IEEE802.1x port-based access control
 * Input:
 *      port         -  Specify port number (0 ~ 5)
 *      enabled    -   enable port-based access control
 *      isAuth      -   Authorized or unauthorized state 
 *      direction   -    set IEEE802.1x port-based control direction
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *     There are two IEEE802.1x port state:
 *         RTL8306_PORT_AUTH      - authorized
 *         RTL8306_PORT_UNAUTH  - unauthorized
 *
 *     There are also two 802.1x port-based control direction:
 *         RTL8306_PORT_BOTHDIR - if port-base access control is enabled, 
 *                                              forbid forwarding this port's traffic to unauthorized port
 *         RTL8306_PORT_INDIR     - if port-base access control is enabled, permit forwarding this
 *                                              port's traffic to unauthorized port
 */ 
uint32 rtl8306e_dot1x_portBased_set(uint32 port, uint32 enabled, uint32 isAuth, uint32 direction)
{

    if (port > RTL8306_PORT5)
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ;  
    
    if (!enabled) 
    {
        rtl8306e_regbit_set(port, 17, 8, 2, 0);
        rtl8306e_regbit_set(port, 17, 6, 2, isAuth == RTL8306_PORT_AUTH ? 1:0);
        rtl8306e_regbit_set(port, 17, 7, 2, direction == RTL8306_PORT_BOTHDIR ? 0:1);
    } 
    else 
    {
        rtl8306e_regbit_set(port, 17, 8, 2, 1);
        rtl8306e_regbit_set(port, 17, 6, 2, isAuth == RTL8306_PORT_AUTH ? 1:0);
        rtl8306e_regbit_set(port, 17, 7, 2, direction == RTL8306_PORT_BOTHDIR ? 0:1);
    }

    return TRUE;
}

/* Function Name:
 *      rtl8306e_dot1x_portBased_set
 * Description:
 *      Set IEEE802.1x port-based access control
 * Input:
 *      port         -  Specify port number (0 ~ 5)
 * Output:
 *      pEnabled    - the pointer of port-based access control status
 *      pIsAuth      - the pointer of authorized or unauthorized state 
 *      pDirection   - the pointer of IEEE802.1x port-based control direction
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *     There are two IEEE802.1x port state:
 *         RTL8306_PORT_AUTH      - authorized
 *         RTL8306_PORT_UNAUTH  - unauthorized
 *
 *     There are also two 802.1x port-based control direction:
 *         RTL8306_PORT_BOTHDIR - if port-base access control is enabled, 
 *                                              forbid forwarding this port's traffic to unauthorized port
 *         RTL8306_PORT_INDIR     - if port-base access control is enabled, permit forwarding this
 *                                              port's traffic to unauthorized port
 */ 

uint32 rtl8306e_dot1x_portBased_get(uint32 port, uint32 *pEnabled, uint32 *pIsAuth, uint32 *pDirection) 
{
    uint32 bitValue;

    if ((port > RTL8306_PORT5) || (NULL == pEnabled) || (NULL == pIsAuth) || (NULL == pDirection)) 
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (port == RTL8306_PORT5 )  
        port ++ ;  
    
    rtl8306e_regbit_get(port, 17, 8, 2, &bitValue);
    *pEnabled = (bitValue ? TRUE : FALSE);
    rtl8306e_regbit_get(port, 17, 6, 2, &bitValue);
    *pIsAuth = (bitValue ? RTL8306_PORT_AUTH : RTL8306_PORT_UNAUTH);
    rtl8306e_regbit_get(port, 17, 7, 2, &bitValue);
    *pDirection = (bitValue ? RTL8306_PORT_INDIR : RTL8306_PORT_BOTHDIR);
    return TRUE;
} 

/* Function Name:
 *      rtl8306e_dot1x_macBased_set
 * Description:
 *      Set IEEE802.1x port-based access control
 * Input:
 *      port         -  Specify port number (0 ~ 5)
 * Output:
 *      enabled    - Enable the port Mac-based access control ability
 *      direction   -  IEEE802.1x mac-based access control direction
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      the mac address authentication status is saved in L2 table entry,
 *      it should be set by software.
 *      there are also two mac-based control directions which are not per 
 *      port but global configurtion:
 *      RTL8306_MAC_BOTHDIR - if Mac-based access control is enabled, packet with 
 *      unauthorized DA will be dropped.
 *      RTL8306_MAC_INDIR   - if Mac-based access control is enabled, packet with 
 *      unauthorized DA will pass mac-based access control igress rule.
 */ 
uint32 rtl8306e_dot1x_macBased_set(uint32 port, uint32 enabled, uint32 direction)
{

    if (port > RTL8306_PORT5)
        return FALSE;
    
    /*Port 5 corresponding PHY6*/
    if (RTL8306_PORT5 == port)  
        port ++ ;  
    
    if (!enabled) 
    {
        rtl8306e_regbit_set(port, 17, 9, 2, 0);
        return TRUE;
    } 
    else 
    {
        rtl8306e_regbit_set(port, 17, 9, 2, 1);
        rtl8306e_regbit_set(2, 22, 7, 3, direction == RTL8306_MAC_BOTHDIR ?  0 : 1 );
    }
    return TRUE;
}


/* Function Name:
 *      rtl8306e_dot1x_macBased_set
 * Description:
 *      Set IEEE802.1x port-based access control
 * Input:
 *      port         -  Specify port number (0 ~ 5)
 * Output:
 *      enabled    - Enable the port Mac-based access control ability
 *      direction   -  IEEE802.1x mac-based access control direction
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      the mac address authentication status is saved in L2 table entry,
 *      it should be set by software.
 *      there are also two mac-based control directions which are not per 
 *      port but global configurtion:
 *      RTL8306_MAC_BOTHDIR - if Mac-based access control is enabled, packet with 
 *      unauthorized DA will be dropped.
 *      RTL8306_MAC_INDIR   - if Mac-based access control is enabled, packet with 
 *      unauthorized DA will pass mac-based access control igress rule.
 */ 
 
uint32 rtl8306e_dot1x_macBased_get(uint32 port, uint32 *pEnabled, uint32 *pDirection) 
{
    uint32 bitValue;

    if ((port > RTL8306_PORT5) || (NULL == pEnabled) || (NULL == pDirection))
        return FALSE;
    
    if (port  < RTL8306_PORT5 ) 
        rtl8306e_regbit_get(port, 17, 9, 2, &bitValue);
    else 
        rtl8306e_regbit_get(6, 17, 9, 2, &bitValue);
    *pEnabled = (bitValue ? TRUE : FALSE) ; 
    rtl8306e_regbit_get(2, 22, 7, 3, &bitValue);
    *pDirection = (bitValue ? RTL8306_PORT_INDIR : RTL8306_PORT_BOTHDIR);
    return TRUE;
}

/* Function Name:
 *      rtl8306e_trap_igmpCtrlPktAction_set
 * Description:
 *      Set IGMP/MLD trap function
 * Input:
 *      type         -  Specify IGMP/MLD or PPPOE
 *      action       -  Action could be normal forward or trap
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *     type could be:
 *          RTL8306_IGMP   - igmp packet without pppoe header 
 *          RTL8306_MLD    - mld packet  without pppoe header
 *          RTL8306_PPPOE - pppoe packet if enable trap RTL8306_IGMP 
 *                                   or RTL8306_MLD whether pppoe packet 
 *                                   should be trapped. In some application,
 *                                   igmp and mld message is encapsulated in pppoed
 *                                   packet.
 *         
 *      action could be:
 *          RTL8306_ACT_PERMIT    - normal forward
 *          RTL8306_ACT_TRAPCPU  - trap to cpu
 */ 

uint32 rtl8306e_trap_igmpCtrlPktAction_set(uint32 type, uint32 action)
{    
    switch(type)
    {
        case RTL8306_IGMP:
            if (RTL8306_ACT_PERMIT == action)
            {
                rtl8306e_regbit_set(2, 21, 14, 3, 0);
            }
            else if (RTL8306_ACT_TRAPCPU == action)
            {
                rtl8306e_regbit_set(2, 21, 14, 3, 1);                
            }
            else
            {
                return FALSE;
            }            
            break;
            
        case RTL8306_MLD:
            if (RTL8306_ACT_PERMIT == action)
            {
                rtl8306e_regbit_set(2, 21, 13, 3, 0);
            }
            else if (RTL8306_ACT_TRAPCPU == action)
            {
                rtl8306e_regbit_set(2, 21, 13, 3, 1);                
            }
            else
            {
                return FALSE;
            }            
            
            break;

         case RTL8306_PPPOE:
            if (RTL8306_ACT_PERMIT == action)
            {
                rtl8306e_regbit_set(2, 22, 4, 3, 1);
            }
            else if (RTL8306_ACT_TRAPCPU == action)
            {
                rtl8306e_regbit_set(2, 22, 4, 3, 0);                
            }
            else
            {
                return FALSE;
            }                        
            break;
            
         default:
            return FALSE;
           
    }

    return TRUE;
}


/* Function Name:
 *      rtl8306e_trap_igmpCtrlPktAction_get
 * Description:
 *      Get IGMP/MLD trap setting
 * Input:
 *      type         -  Specify IGMP/MLD or PPPOE
 * Output:
 *      pAction     -  the pointer of action could be normal forward or trap
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *     type could be:
 *          RTL8306_IGMP   - igmp packet without pppoe header 
 *          RTL8306_MLD    - mld packet  without pppoe header
 *          RTL8306_PPPOE - pppoe packet if enable trap RTL8306_IGMP 
 *                                   or RTL8306_MLD whether pppoe packet 
 *                                   should be trapped. In some application,
 *                                   igmp and mld message is encapsulated in pppoed
 *                                   packet.
 *      action could be:
 *          RTL8306_ACT_PERMIT    - normal forward
 *          RTL8306_ACT_TRAPCPU  - trap to cpu
 */ 

uint32 rtl8306e_trap_igmpCtrlPktAction_get(uint32 type, uint32 *pAction)
{
    uint32 regval;

    if (NULL == pAction)
        return FALSE;
    
    switch(type)
    {
        case RTL8306_IGMP:
            rtl8306e_regbit_get(2, 21, 14, 3, &regval);
            *pAction = regval ? RTL8306_ACT_TRAPCPU : RTL8306_ACT_PERMIT;
            break;            
        case RTL8306_MLD:
            rtl8306e_regbit_get(2, 21, 13, 3, &regval);
            *pAction = regval ? RTL8306_ACT_TRAPCPU : RTL8306_ACT_PERMIT;            
            break;
         case RTL8306_PPPOE:
            rtl8306e_regbit_get(2, 22, 4, 3, &regval);
            *pAction = regval ?  RTL8306_ACT_PERMIT : RTL8306_ACT_TRAPCPU;
            break;            
         default:
            return FALSE;
    }
    return TRUE;
}


/* Function Name:
 *      rtl8306e_trap_unknownIPMcastPktAction_set
 * Description:
 *      Set unknown ip multicast drop or normal forward
 * Input:
 *      type         -  Specify ipv4 or ipv6 unkown multicast
 *      action       -  drop or normal forward
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      type coulde be:
 *          RTL8306_IPV4_MULTICAST - ipv4 unknown multicast
 *          RTL8306_IPV6_MULTICAST - ipv6 unknown multicast
 *      action could be:
 *          RTL8306_ACT_DROP      - drop 
 *          RTL8306_ACT_PERMIT   - normal forward
 */  
uint32 rtl8306e_trap_unknownIPMcastPktAction_set(uint32 type, uint32 action)
{    
    switch(type)
    {
        case RTL8306_IPV4_MULTICAST:
            if(RTL8306_ACT_DROP == action)
                rtl8306e_regbit_set(4, 21, 9, 0, 1);
            else if (RTL8306_ACT_PERMIT == action)
                rtl8306e_regbit_set(4, 21, 9, 0, 0);
            break;
            
        case RTL8306_IPV6_MULTICAST:
            if(RTL8306_ACT_DROP == action)
                rtl8306e_regbit_set(4, 21, 8, 0, 1);
            else if (RTL8306_ACT_PERMIT == action)
                rtl8306e_regbit_set(4, 21, 8, 0, 0);                                                
            break;
            
        default:
            return FALSE;
    }

    return TRUE;
}


/* Function Name:
 *      rtl8306e_trap_unknownIPMcastPktAction_get
 * Description:
 *      Get unknown ip multicast drop or normal forward
 * Input:
 *      type         -  Specify ipv4 or ipv6 unkown multicast
 * Output:
 *      pAction     -  the pointer of drop or normal forward
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      type coulde be:
 *          RTL8306_IPV4_MULTICAST - ipv4 unknown multicast
 *          RTL8306_IPV6_MULTICAST - ipv6 unknown multicast
 *      action could be:
 *          RTL8306_ACT_DROP      - drop
 *          RTL8306_ACT_PERMIT   - normal forward
 */ 

uint32 rtl8306e_trap_unknownIPMcastPktAction_get(uint32 type, uint32 *pAction)
{
    uint32 regval;
    
    if (NULL == pAction)
        return FALSE;

    switch(type)
    {
        case RTL8306_IPV4_MULTICAST:
            rtl8306e_regbit_get(4, 21, 9, 0, &regval);
            *pAction = regval ? RTL8306_ACT_DROP: RTL8306_ACT_PERMIT;
            break;
        case RTL8306_IPV6_MULTICAST:
            rtl8306e_regbit_get(4, 21, 8, 0, &regval);
            *pAction = regval ? RTL8306_ACT_DROP: RTL8306_ACT_PERMIT;            
            break;
         default:
            return FALSE;
    }

    return TRUE;
}

/* Function Name:
 *      rtl8306e_trap_abnormalPktAction_set
 * Description:
 *      set abnormal packet action 
 * Input:
 *      type         -  abnormal packet type
 *      action       -  drop or trap to cpu
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      type coulde be:
 *          RTL8306_UNMATCHVID   - vlan-tagged packet, vid dismatch vlan table 
 *          RTL8306_DOT1XUNAUTH - 802.1x authentication fail packet
 *      action could be:
 *          RTL8306_ACT_DROP       - drop 
 *          RTL8306_ACT_TRAPCPU  - trap to cpu
 */ 

uint32 rtl8306e_trap_abnormalPktAction_set(uint32 type,  uint32 action)
{
    switch(type)
    {
        case RTL8306_UNMATCHVID:            
            if(RTL8306_ACT_DROP == action)
                rtl8306e_regbit_set(2, 22, 6, 3, 1);
            else if (RTL8306_ACT_TRAPCPU == action)
                rtl8306e_regbit_set(2, 22, 6, 3, 0);            
            break;
            
        case RTL8306_DOT1XUNAUTH:
            if(RTL8306_ACT_DROP == action)
                rtl8306e_regbit_set(2, 22, 5, 3, 0);
            else if (RTL8306_ACT_TRAPCPU == action)
                rtl8306e_regbit_set(2, 22, 5, 3, 1);                        
            break;
        default:
            return FALSE;
    }
    
    return TRUE;
}


/* Function Name:
 *      rtl8306e_trap_abnormalPktAction_get
 * Description:
 *      get abnormal packet action 
 * Input:
 *      type         -  abnormal packet type
 * Output:
 *      pAction     -  the pointer of action
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      type coulde be:
 *          RTL8306_UNMATCHVID   - vlan-tagged packet, vid dismatch vlan table 
 *          RTL8306_DOT1XUNAUTH - 802.1x authentication fail packet
 *      action could be:
 *          RTL8306_ACT_DROP       - drop 
 *          RTL8306_ACT_TRAPCPU  - trap to cpu
 */ 

uint32 rtl8306e_trap_abnormalPktAction_get(uint32 type,  uint32 *pAction)
{
    uint32 regval;

    if (NULL ==pAction)
        return FALSE;
    
    switch(type)
    {
        case RTL8306_UNMATCHVID:
            rtl8306e_regbit_get(2, 22, 6, 3, &regval);
            *pAction = regval ? RTL8306_ACT_DROP: RTL8306_ACT_TRAPCPU;
            break;
        case RTL8306_DOT1XUNAUTH:
            rtl8306e_regbit_get(2, 22, 5, 3, &regval);
            *pAction = regval ? RTL8306_ACT_TRAPCPU : RTL8306_ACT_DROP;
            break;
        default:
            return FALSE;
    }

    return TRUE;
}

/* Function Name:
 *      rtl8306e_trap_rmaAction_set
 * Description:
 *      Set reserved multicast Mac address forwarding behavior
 * Input:
 *      type         -  reserved Mac address type
 *      action       -  forwarding behavior for the specified mac address
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      There are eight types  reserved addresses which user can set asic to determine 
 *       how to forwarding them:
 *            RTL8306_RESADDRXX   - reserved address 01-80-c2-00-00-xx 
 *                                              (exclude 00, 01, 02, 03, 10, 20, 21)
 *            RTL8306_RESADDR21   -  reserved address 01-80-c2-00-00-21(GVRP address)
 *            RTL8306_RESADDR20   -  reserved address 01-80-c2-00-00-20(GMRP Address)
 *            RTL8306_RESADDR10   -  reserved address 01-80-c2-00-00-10(All LANs Bridge Management Group Address)
 *            RTL8306_RESADDR03   -  reserved address 01-80-c2-00-00-03(IEEE Std 802.1X PAE address)
 *            RTL8306_RESADDR02   -  reserved address 01-80-c2-00-00-02(IEEE Std 802.3ad Slow_Protocols-Multicast address)
 *            RTL8306_RESADDR00   -  reserved address 01-80-c2-00-00-00(Bridge Group Address)
 *            RTL8306_RESADDR01   -  reserved address 01-80-c2-00-00-01(Pause frame)
 *       Actions are :
 *            TL8306_ACT_DROP      - Drop the packet
 *            TL8306_ACT_TRAPCPU - Trap the packet to cpu
 *            RTL8306_ACT_FLOOD   - Flood the packet
 */ 

uint32 rtl8306e_trap_rmaAction_set(uint32 type, uint32 action)
{
    if ((type > RTL8306_RESADDR01) || (action > RTL8306_ACT_FLOOD)) 
        return FALSE;
    
    switch (type) 
    {
        case RTL8306_RESADDR21:
        case RTL8306_RESADDR20:
        case RTL8306_RESADDR10:
        case RTL8306_RESADDR03:
        case RTL8306_RESADDR00: 
            
            /*Above cases have same action*/
            if (RTL8306_ACT_FLOOD == action) 
                rtl8306e_regbit_set(2, 21, type, 3, 0);
            else if (RTL8306_ACT_TRAPCPU == action)
                rtl8306e_regbit_set(2, 21, type, 3, 1);
            else 
                return FALSE;
            break;
            
        case RTL8306_RESADDR02:
            if (RTL8306_ACT_FLOOD == action) 
            {
                rtl8306e_regbit_set(1, 23, 4, 0, 0); 
                rtl8306e_regbit_set(2, 21, type, 3, 0);
            }
            else if (RTL8306_ACT_TRAPCPU == action) 
            {
                rtl8306e_regbit_set(1, 23, 4, 0, 0);
                rtl8306e_regbit_set(2, 21, type, 3, 1);
            }
            else if (RTL8306_ACT_DROP == action) 
                rtl8306e_regbit_set(1, 23, 4, 0, 1); 
            else 
                return FALSE;
            break;
        
        case RTL8306_RESADDRXX:
            if (RTL8306_ACT_FLOOD == action) 
            {
                rtl8306e_regbit_set(0, 18, 12, 0, 1); 
                rtl8306e_regbit_set(2, 21, type, 3, 0);
            } 
            else if (RTL8306_ACT_TRAPCPU == action) 
            {
                rtl8306e_regbit_set(0, 18, 12, 0, 1);
                rtl8306e_regbit_set(2, 21, type, 3, 1);
            }
            else if (RTL8306_ACT_DROP == action) 
                rtl8306e_regbit_set(0, 18, 12, 0, 0);
            else 
                return FALSE;
            break;
        
        case RTL8306_RESADDR01:
            if (RTL8306_ACT_FLOOD == action) 
                rtl8306e_regbit_set(0, 22, 14, 0, 1); 
            else if (RTL8306_ACT_DROP == action)
                rtl8306e_regbit_set(0, 22, 14, 0, 0);
            else 
                return FALSE;
            break;
        default :
            return FALSE;
    }
    return TRUE;
}

/* Function Name:
 *      rtl8306e_trap_rmaAction_get
 * Description:
 *      Get reserved multicast Mac address forwarding behavior
 * Input:
 *      type         -  reserved Mac address type
 * Output:
 *      pAction     -  the pointer of action
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      There are eight types  reserved addresses which user can set asic to determine 
 *       how to forwarding them:
 *            RTL8306_RESADDRXX   - reserved address 01-80-c2-00-00-xx 
 *                                              (exclude 00, 01, 02, 03, 10, 20, 21)
 *            RTL8306_RESADDR21   -  reserved address 01-80-c2-00-00-21(GVRP address)
 *            RTL8306_RESADDR20   -  reserved address 01-80-c2-00-00-20(GMRP Address)
 *            RTL8306_RESADDR10   -  reserved address 01-80-c2-00-00-10(All LANs Bridge Management Group Address)
 *            RTL8306_RESADDR03   -  reserved address 01-80-c2-00-00-03(IEEE Std 802.1X PAE address)
 *            RTL8306_RESADDR02   -  reserved address 01-80-c2-00-00-02(IEEE Std 802.3ad Slow_Protocols-Multicast address)
 *            RTL8306_RESADDR00   -  reserved address 01-80-c2-00-00-00(Bridge Group Address)
 *            RTL8306_RESADDR01   -  reserved address 01-80-c2-00-00-01(Pause frame)
 *       Actions are :
 *            TL8306_ACT_DROP      - Drop the packet
 *            TL8306_ACT_TRAPCPU - Trap the packet to cpu
 *            RTL8306_ACT_FLOOD   - Flood the packet
 */ 

uint32 rtl8306e_trap_rmaAction_get(uint32 type, uint32 *pAction)
{
    uint32 bitValue1, bitValue2;

    if ((type > RTL8306_RESADDR01) || (NULL == pAction )) 
        return FALSE;

    switch (type)
    {
        case RTL8306_RESADDR21:
        case RTL8306_RESADDR20:
        case RTL8306_RESADDR10:
        case RTL8306_RESADDR03:
        case RTL8306_RESADDR00: 
            /*Above cases have same action*/
            rtl8306e_regbit_get(2, 21, type, 3, &bitValue1);
            if (bitValue1) 
                *pAction = RTL8306_ACT_TRAPCPU; 
            else
                *pAction = RTL8306_ACT_FLOOD; 
            break;
        case RTL8306_RESADDR02:
            rtl8306e_regbit_get(1, 23, 4, 0, &bitValue1);  
            rtl8306e_regbit_get(2, 21, type, 3, &bitValue2);
            if (bitValue1)
                *pAction = RTL8306_ACT_DROP;
            else if (bitValue2)
                *pAction = RTL8306_ACT_TRAPCPU;
            else
                *pAction = RTL8306_ACT_FLOOD;
            break;
        case RTL8306_RESADDRXX:
            rtl8306e_regbit_get(0, 18, 12, 0, &bitValue1); 
            rtl8306e_regbit_get(2, 21, type, 3, &bitValue2);
            if (!bitValue1)
                *pAction = RTL8306_ACT_DROP;
            else if (bitValue2)
                *pAction = RTL8306_ACT_TRAPCPU;
            else
                *pAction = RTL8306_ACT_FLOOD;
            break;
        case RTL8306_RESADDR01:
            rtl8306e_regbit_get(0, 22, 14, 0, &bitValue1); 
            if (bitValue1)
                *pAction = RTL8306_ACT_FLOOD;
            else
                *pAction = RTL8306_ACT_DROP;
            break;
       default :
            return FALSE;
    }
    return TRUE;
}

/* Function Name:
 *      rtl8306e_int_control_set
 * Description:
 *      Set asic interrupt 
 * Input:
 *      enInt        -  Enable interrupt cpu
 *      intmask     -  interrupt event  mask
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      enInt is global setting and  intmask  has 12 bits totally, each bit 
 *      represents one interrupt event, 
 *      - bit0 ~bit4 represent port 0 ~ port 4 link change, 
 *      - bit 5 represents port 4 MAC link change
 *      - bit 6 represents port 5 link change, 
 *      - bit 7 represents storm filter interrupt,
 *      - bit 8 represents loop event 
 *      - bit 9 represents wake up frame interrupt
 *      - bit 10 represents unmatched SA interrupt
 *      - bit 11 represents Tx meter interrupt
 *      write 1 to the bit to enable the interrupt and 0 will disable the interrupt. 
 *
 */ 
uint32 rtl8306e_int_control_set(uint32 enInt, uint32 intmask)
{
    uint16 regValue;

    if (intmask > 0xFFF)
        return FALSE;

    if (!enInt) 
    {
        /*CPU interrupt disable, do not change interrupt port mask*/
        rtl8306e_regbit_set(2, 22, 15, 3, 1);
        return TRUE;
    } 
    
    /*CPU interrupt enable*/
    rtl8306e_regbit_set(2, 22, 15, 3, 0);
    
    /*Set link change interrupt mask*/
    rtl8306e_reg_get(4, 23, 3, &regValue);
    regValue = (regValue & 0xF000) | (intmask & 0xFFF);
    rtl8306e_reg_set(4, 23, 3, regValue);
    return TRUE;
}

/* Function Name:
 *      rtl8306e_int_control_get
 * Description:
 *      Get Asic interrupt
 * Input:
 *      none 
 * Output:
 *      pEnInt       -  the pointer of  interrupt global enable bit
 *      pIntmask    -  the pointer of interrupt event  mask 
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      enInt is global setting and  intmask  has 12 bits totally, each bit 
 *      represents one interrupt event, 
 *      - bit0 ~bit4 represent port 0 ~ port 4 link change, 
 *      - bit 5 represents port 4 MAC link change
 *      - bit 6 represents port 5 link change, 
 *      - bit 7 represents storm filter interrupt,
 *      - bit 8 represents loop event 
 *      - bit 9 represents wake up frame interrupt
 *      - bit 10 represents unmatched SA interrupt
 *      - bit 11 represents Tx meter interrupt
 *      write 1 to the bit to enable the interrupt and 0 will disable the interrupt. 
 *
 */ 
uint32 rtl8306e_int_control_get(uint32 *pEnInt, uint32 *pIntmask) 
{
    uint16 regValue;
    uint32 bitValue;

    if ((NULL == pEnInt) || (NULL == pIntmask))
        return FALSE;
    
    rtl8306e_regbit_get(2, 22, 15, 3, &bitValue);
    *pEnInt = (bitValue ? FALSE : TRUE);
    rtl8306e_reg_get(4, 23, 3, &regValue);
    *pIntmask = regValue & 0xFFF;
    return TRUE;
}

/* Function Name:
 *      rtl8306e_int_control_get
 * Description:
 *      Get Asic interrupt
 * Input:
 *      none 
 * Output:
 *      pEnInt       -  the pointer of  interrupt global enable bit
 *      pIntmask    -  the pointer of interrupt event  mask 
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      enInt is global setting and  intmask  has 12 bits totally, each bit 
 *      represents one interrupt event, 
 *      - bit0 ~bit4 represent port 0 ~ port 4 link change, 
 *      - bit 5 represents port 4 MAC link change
 *      - bit 6 represents port 5 link change, 
 *      - bit 7 represents storm filter interrupt,
 *      - bit 8 represents loop event 
 *      - bit 9 represents wake up frame interrupt
 *      - bit 10 represents unmatched SA interrupt
 *      - bit 11 represents Tx meter interrupt
 *      write 1 to the bit to enable the interrupt and 0 will disable the interrupt. 
 *
 */ 
uint32 rtl8306e_int_status_get(uint32 *pStatusMask) 
{
    uint16 regValue;

    if (NULL == pStatusMask)
        return FALSE;
    
    rtl8306e_reg_get(4, 22, 3, &regValue);
    *pStatusMask = regValue & 0xFFF;
    return TRUE;
}

/* Function Name:
 *      rtl8306e_storm_filterEnable_set
 * Description:
 *      Enable Asic storm filter 
 * Input:
 *      type      -  specify storm filter type
 *      enabled  -  TRUE or FALSE
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      There are 3 kinds of storm filter:
 *      (1) RTL8306_BROADCASTPKT - storm filter for broadcast packet
 *      (2) RTL8306_MULTICASTPKT - storm filter for multicast packet
 *      (3) RTL8306_UDAPKT           - storm filter for unknown DA packet
 */ 
uint32 rtl8306e_storm_filterEnable_set(uint32 type, uint32 enabled) 
{

   /*enable new storm filter*/
   rtl8306e_regbit_set(6, 17, 1, 1, enabled ? 1:0);
   
    switch(type) 
    {
        case RTL8306_BROADCASTPKT:
            rtl8306e_regbit_set(0, 18, 2, 0, enabled ? 0:1);
            break;
        case RTL8306_MULTICASTPKT:
            rtl8306e_regbit_set(2, 23, 9, 3, enabled ? 0:1);
            break;
        case RTL8306_UDAPKT:
            rtl8306e_regbit_set(2, 23, 8, 3, enabled ? 0:1);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

/* Function Name:
 *      rtl8306e_storm_filterEnable_get
 * Description:
 *      Get Asic storm filter enabled or disabled 
 * Input:
 *      type        -  specify storm filter type
 * Output:
 *      pEnabled  -  the pointer of enabled or disabled
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      There are 3 kinds of storm filter:
 *      (1) RTL8306_BROADCASTPKT - storm filter for broadcast packet
 *      (2) RTL8306_MULTICASTPKT - storm filter for multicast packet
 *      (3) RTL8306_UDAPKT           - storm filter for unknown DA packet
 */ 

uint32 rtl8306e_storm_filterEnable_get(uint32 type, uint32 *pEnabled) 
{
    uint32 bitValue;

    if (pEnabled == NULL)
        return FALSE;
    
    switch(type) 
   {
        case RTL8306_BROADCASTPKT:
            rtl8306e_regbit_get(0, 18, 2, 0, &bitValue);
            break;
        case RTL8306_MULTICASTPKT:
            rtl8306e_regbit_get(2, 23, 9, 3, &bitValue);
            break;
        case RTL8306_UDAPKT:
            rtl8306e_regbit_get(2, 23, 8, 3, &bitValue);
            break;
        default:
            return FALSE;

    }

    *pEnabled = (bitValue ? FALSE : TRUE);
    return TRUE;
}

/* Function Name:
 *      rtl8306e_storm_filter_set
 * Description:
 *      Set storm filter parameter
 * Input:
 *      trigNum        -  set packet threshold which trigger storm filter
 *      filTime         -   set time window 
 *      enStmInt     -   enable storm filter to interrupt cpu
 * Output:
 *      none
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      there are 6 value for trigNum:
 *      - RTL8306_STM_FILNUM64, 64 pkts
 *      - RTL8306_STM_FILNUM32, 32 pkts           
 *      - RTL8306_STM_FILNUM16, 16 pkts           
 *      - RTL8306_STM_FILNUM8,   8 pkts              
 *      - RTL8306_STM_FILNUM128, 128 pkts          
 *      - RTL8306_STM_FILNUM256, 256 pkts     
 *      there are 4 value for filTime:
 *      - RTL8306_STM_FIL800MS,  800ms 
 *      - RTL8306_STM_FIL400MS,  400ms 
 *      - RTL8306_STM_FIL200MS,  200ms
 *      - RTL8306_STM_FIL100MS,  100ms
 */ 

uint32 rtl8306e_storm_filter_set(uint32 trigNum, uint32 filTime, uint32 enStmInt) 
{
    uint16 regval;
    
    if ( (trigNum >= RTL8306_STM_FILNUM_END) || (filTime >= RTL8306_STM_FILTIM_END))
        return FALSE;
    
    if(RTL8306_STM_FILNUM128 == trigNum)
    {
        rtl8306e_reg_get(6, 25, 0, &regval);
        regval &= 0xFC1F;
        regval |= (filTime << 5); 
        rtl8306e_reg_set(6, 25, 0 , regval);        
        rtl8306e_regbit_set(6, 17, 0, 1, 1);
    }
    else if(RTL8306_STM_FILNUM256 == trigNum)
    {
        rtl8306e_reg_get(6, 25, 0, &regval);
        regval &= 0xFC1F;
        regval |= (0x1 << 8) | (filTime << 5); 
        rtl8306e_reg_set(6, 25, 0 , regval);        
        rtl8306e_regbit_set(6, 17, 0, 1, 1);
    }
    else
    {
        rtl8306e_reg_get(6, 25, 0, &regval);
        regval &= 0xFC1F;
        regval |= (trigNum << 8) | (filTime << 5);
        rtl8306e_reg_set(6, 25, 0 , regval);
        rtl8306e_regbit_set(6, 17, 0, 1, 0);        
    }
        
    /*Set whether storm filter interrupt cpu*/
    rtl8306e_regbit_set(4, 23, 7, 3, enStmInt ? 1:0);
    
    /*CPU interrupt enable when enable storm filter interrupt*/
    rtl8306e_regbit_set(2, 22, 15, 3, enStmInt ? 0:1);

    return TRUE;

}


/* Function Name:
 *      rtl8306e_storm_filter_get
 * Description:
 *      Get storm filter parameter
 * Input:
 *      none 
 * Output:
 *      pTrigNum        -  the pointer of packet threshold which trigger storm filter
 *      pFilTime          -  the pointer of filter time window 
 *      pEnStmInt       -  the pointer of enable storm filter to interrupt cpu
 * Return:
 *      TRUE
 *      FALSE
 * Note:
 *      there are 6 value for trigNum:
 *      - RTL8306_STM_FILNUM64, 64 pkts
 *      - RTL8306_STM_FILNUM32, 32 pkts           
 *      - RTL8306_STM_FILNUM16, 16 pkts           
 *      - RTL8306_STM_FILNUM8,   8 pkts              
 *      - RTL8306_STM_FILNUM128, 128 pkts          
 *      - RTL8306_STM_FILNUM256, 256 pkts     
 *      there are 4 value for filTime:
 *      - RTL8306_STM_FIL800MS,  800ms 
 *      - RTL8306_STM_FIL400MS,  400ms 
 *      - RTL8306_STM_FIL200MS,  200ms
 *      - RTL8306_STM_FIL100MS,  100ms
 */ 

uint32 rtl8306e_storm_filter_get(uint32 *pTrigNum, uint32 *pFilTime, uint32 *pEnStmInt) 
{
    uint32 bitval;
	uint16 regval;
    
    if ((NULL == pTrigNum) || (NULL == pFilTime) || (NULL == pEnStmInt))
        return FALSE;

    rtl8306e_regbit_get(6, 17, 0, 1, &bitval);

    if(bitval)
    {
        rtl8306e_reg_get(6, 25, 0, &regval);
        *pTrigNum = ((regval >> 8) & 0x3) ? RTL8306_STM_FILNUM256 : RTL8306_STM_FILNUM128;
        *pFilTime = (regval >> 5) & 0x3;
    }
    else
    {
        rtl8306e_reg_get(6, 25, 0, &regval);
        *pTrigNum = (regval >> 8) & 0x3;
        *pFilTime = (regval >> 5) & 0x3;
    }
    rtl8306e_regbit_get(4, 23, 7, 3, pEnStmInt);
    
    return TRUE;
}





