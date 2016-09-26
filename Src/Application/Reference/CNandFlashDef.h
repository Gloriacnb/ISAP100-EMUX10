/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **
 **                                 http://www.ezwell-tech.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** Created by:				Liu Weifeng
 ** Created date:			2011-05-19
 ** Version:				    1.0
 ** Descriptions:			对NandFlash操作的常量定义
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Version:
 ** Descriptions:
 **
 **********************************************************************************************************************/
#ifndef CNandFlashDef_H
#define CNandFlashDef_H

#include "EZ_types.h"
#include "CErrorValueDefine.h"

class CNandFlashDef {
private:
	static const uint32 uiConstDefineBase = 0x00200000; //常量定义基础值
public:
	/*  NandFlash参数  */
	static const uint32 uiMaxBlock 			= 200; 					//  此处表示的是最大块
	static const uint32 uiMinBlock			= 10;						//	此处表示的最小块
	static const uint32 uiMaxAddr 			= (256 * 1024 * 1024 - 1);
	static const uint32 uiBytePerSector 	= 2048; 					//  每个扇区的字节数
	static const uint32 uiSectorPerBlock 	= 64; 						//  每个块的扇区数

	/*  对NandFlash访问的返回值*/
	//WangChangRong修改，使用CErrorValueDefine类中失败和成功的定义
	//       static const uint32 uiFailed    = 0x00;     //  操作失败
	//       static const uint32 uiSuccess   = 0x01;     //  操作成功
	static const uint32 uiBadBlock 			= uiConstDefineBase + 0x02; //  坏块
	static const uint32 uiBusy 				= CErrorValueDefine::uiConstReturnDeviceBusy; //  Flash正忙
	static const uint32 uiReady             = CErrorValueDefine::uiConstReturnDeviceReady;   //  Flash不忙
	static const uint32 uiParaError 		= uiConstDefineBase + 0x04; //  参数错误

	static const uint32 uiMainSlaveStartSector	= 0x16;		//  主控卡Main程序备区的加载地址

    /*  Flash空间分配  */
    static const uint32 uiDeviceAttriMasterSSector    = 0x30;   //  设备属性主区开始扇区号
    static const uint32 uiDeviceAttriSlaveSSector     = 0x33;   //  设备属性备区开始扇区号
    static const uint32 uiDeviceAttriReserveSectorNum = 0x02;   //  设备属性保留扇区个数
    
    static const uint32 uiSecurityAttriMasterSSector    = 0x36;   //  安全属性主区开始扇区号
    static const uint32 uiSecurityAttriSlaveSSector     = 0x39;   //  安全属性备区开始扇区号
    static const uint32 uiSecurityAttriReserveSectorNum = 0x02;   //  安全属性保留扇区个数
    
    static const uint32 uiSlotMasterSSectorBase = 0x40;     //  槽位保存数据主区开始基扇区号
    static const uint32 uiSlotSlaveSSectorBase  = 0x43;     //  槽位保存数据备区开始基扇区号
    static const uint32 uiSlotReserveSectorNum  = 0x02;     //  槽位保存数据保留扇区个数
    
    static const uint32 uiSlot1MasterSSector    = (uiSlotMasterSSectorBase + 0x00) ;    //  槽位0保存数据主区开始扇区号
    static const uint32 uiSlot1SlaveSSector     = (uiSlotSlaveSSectorBase + 0x00);      //  槽位0保存数据备区开始扇区号
    static const uint32 uiSlot1ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位0保存数据保留扇区个数

    static const uint32 uiSlot2MasterSSector    = (uiSlotMasterSSectorBase + 0x06);     //  槽位1保存数据主区开始扇区号
    static const uint32 uiSlot2SlaveSSector     = (uiSlotSlaveSSectorBase + 0x06);      //  槽位1保存数据备区开始扇区号
    static const uint32 uiSlot2ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位1保存数据保留扇区个数

    static const uint32 uiSlot3MasterSSector    = (uiSlotMasterSSectorBase + 0x0C);     //  槽位2保存数据主区开始扇区号
    static const uint32 uiSlot3SlaveSSector     = (uiSlotSlaveSSectorBase + 0x0C);      //  槽位2保存数据备区开始扇区号
    static const uint32 uiSlot3ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位2保存数据保留扇区个数

    
    static const uint32 uiSlot4MasterSSector    = (uiSlotMasterSSectorBase + 0x12);     //  槽位3保存数据主区开始扇区号
    static const uint32 uiSlot4SlaveSSector     = (uiSlotSlaveSSectorBase + 0x12);      //  槽位3保存数据备区开始扇区号
    static const uint32 uiSlot4ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位3保存数据保留扇区个数

    static const uint32 uiSlot5MasterSSector    = (uiSlotMasterSSectorBase + 0x18);     //  槽位4保存数据主区开始扇区号
    static const uint32 uiSlot5SlaveSSector     = (uiSlotSlaveSSectorBase + 0x18);      //  槽位4保存数据备区开始扇区号
    static const uint32 uiSlot5ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位4保存数据保留扇区个数

    static const uint32 uiSlot6MasterSSector    = (uiSlotMasterSSectorBase + 0x1E);     //  槽位5保存数据主区开始扇区号
    static const uint32 uiSlot6SlaveSSector     = (uiSlotSlaveSSectorBase + 0x1E);      //  槽位5保存数据备区开始扇区号
    static const uint32 uiSlot6ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位5保存数据保留扇区个数

    static const uint32 uiSlot7MasterSSector    = (uiSlotMasterSSectorBase + 0x24);     //  槽位6保存数据主区开始扇区号(交叉卡)
    static const uint32 uiSlot7SlaveSSector     = (uiSlotSlaveSSectorBase + 0x24);      //  槽位6保存数据备区开始扇区号
    static const uint32 uiSlot7ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位6保存数据保留扇区个数
    
    static const uint32 uiSlot8MasterSSector    = (uiSlotMasterSSectorBase + 0x2A);     //  槽位7保存数据主区开始扇区号(交叉卡)
    static const uint32 uiSlot8SlaveSSector     = (uiSlotSlaveSSectorBase + 0x2A);      //  槽位7保存数据备区开始扇区号
    static const uint32 uiSlot8ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位7保存数据保留扇区个数
    
    static const uint32 uiSlot9MasterSSector    = (uiSlotMasterSSectorBase + 0x30);     //  槽位8保存数据主区开始扇区号
    static const uint32 uiSlot9SlaveSSector     = (uiSlotSlaveSSectorBase + 0x30);      //  槽位8保存数据备区开始扇区号
    static const uint32 uiSlot9ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  槽位8保存数据保留扇区个数
    
    static const uint32 uiSlot10MasterSSector    = (uiSlotMasterSSectorBase + 0x36);    //  槽位9保存数据主区开始扇区号
    static const uint32 uiSlot10SlaveSSector     = (uiSlotSlaveSSectorBase + 0x36);     //  槽位9保存数据备区开始扇区号
    static const uint32 uiSlot10ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位9保存数据保留扇区个数
    
    static const uint32 uiSlot11MasterSSector    = (uiSlotMasterSSectorBase + 0x3C);    //  槽位10保存数据主区开始扇区号
    static const uint32 uiSlot11SlaveSSector     = (uiSlotSlaveSSectorBase + 0x3C);     //  槽位10保存数据备区开始扇区号
    static const uint32 uiSlot11ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位10保存数据保留扇区个数
    
    static const uint32 uiSlot12MasterSSector    = (uiSlotMasterSSectorBase + 0x42);    //  槽位11保存数据主区开始扇区号
    static const uint32 uiSlot12SlaveSSector     = (uiSlotSlaveSSectorBase + 0x42);     //  槽位11保存数据备区开始扇区号
    static const uint32 uiSlot12ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位11保存数据保留扇区个数
    
    static const uint32 uiSlot13MasterSSector    = (uiSlotMasterSSectorBase + 0x48);    //  槽位12保存数据主区开始扇区号
    static const uint32 uiSlot13SlaveSSector     = (uiSlotSlaveSSectorBase + 0x48);     //  槽位12保存数据备区开始扇区号
    static const uint32 uiSlot13ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位12保存数据保留扇区个数
    
    static const uint32 uiSlot14MasterSSector    = (uiSlotMasterSSectorBase + 0x4E);    //  槽位13保存数据主区开始扇区号
    static const uint32 uiSlot14SlaveSSector     = (uiSlotSlaveSSectorBase + 0x4E);     //  槽位13保存数据备区开始扇区号
    static const uint32 uiSlot14ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位13保存数据保留扇区个数
    
    static const uint32 uiSlot15MasterSSector    = (uiSlotMasterSSectorBase + 0x54);    //  槽位14保存数据主区开始扇区号(以太汇聚卡)
    static const uint32 uiSlot15SlaveSSector     = (uiSlotSlaveSSectorBase + 0x54);     //  槽位14保存数据备区开始扇区号
    static const uint32 uiSlot15ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位14保存数据保留扇区个数
    
    static const uint32 uiSlot16MasterSSector    = (uiSlotMasterSSectorBase + 0x5A);    //  槽位15保存数据主区开始扇区号(以太汇聚卡)
    static const uint32 uiSlot16SlaveSSector     = (uiSlotSlaveSSectorBase + 0x5A);     //  槽位15保存数据备区开始扇区号
    static const uint32 uiSlot16ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位15保存数据保留扇区个数
    
    static const uint32 uiSlot17MasterSSector    = (uiSlotMasterSSectorBase + 0x60);    //  槽位16保存数据主区开始扇区号(主控卡)
    static const uint32 uiSlot17SlaveSSector     = (uiSlotSlaveSSectorBase + 0x60);     //  槽位16保存数据备区开始扇区号
    static const uint32 uiSlot17ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位16保存数据保留扇区个数
    
    static const uint32 uiSlot18MasterSSector    = (uiSlotMasterSSectorBase + 0x66);    //  槽位17保存数据主区开始扇区号(主控卡)
    static const uint32 uiSlot18SlaveSSector     = (uiSlotSlaveSSectorBase + 0x66);     //  槽位17保存数据备区开始扇区号
    static const uint32 uiSlot18ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位17保存数据保留扇区个数
    
    static const uint32 uiSlot19MasterSSector    = (uiSlotMasterSSectorBase + 0x6C);    //  槽位18保存数据主区开始扇区号(风扇电源卡)
    static const uint32 uiSlot19SlaveSSector     = (uiSlotSlaveSSectorBase + 0x6C);     //  槽位18保存数据备区开始扇区号
    static const uint32 uiSlot19ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  槽位18保存数据保留扇区个数
        
    
    static const uint32 uiHisAlarmStartSector       = 0xC0; //  历史告警的保存开始扇区
    static const uint32 uiHisAlarmEffectiveSector   = 0x01; //  历史告警的保存信息的有效扇区
    static const uint32 uiHisAlarmReserveSector     = 0x03; //  历史告警的保存信息的保留扇区个数
    
    static const uint32 uiAlarmPerproptyMasterSSector       = 0xC5; //  告警属性主区开始扇区号
    static const uint32 uiAlarmPerproptySlaveSSector        = 0xC8; //  告警属性备区开始扇区号
    static const uint32 uiAlarmPerproptyReserveSectorNum    = 0x02; //  告警属性保留扇区个数
    
    static const uint32 uiHisPerfStartSector        = 0xD0; //  历史性能的保存开始扇区
    static const uint32 uiHisPerfEffectiveSector    = 0x01; //  历史性能的保存信息的有效扇区
    static const uint32 uiHisPerfReserveSector      = 0x03; //  历史性能的保存信息的保留扇区个数
    
    static const uint32 uiBitInfoMasterSSector		= 0x400;//  Bit文件信息主区开始扇区号
    static const uint32 uiBitInfoSlaveSSector		= 0x403;//  Bit文件信息备区开始扇区号
    static const uint32 uiBitInfoReserveSector		= 0x02;	//  Bit文件信息保留扇区个数
    static const uint32 uiBitFileStartSector		= 0x406;//  Bit文件的保存开始扇区
    static const uint32 uiBitFileEndSector			= 0x7FF;//  Bit文件的保存终止扇区
};

#endif
