/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **
 **                                 http://www.ezwell-tech.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** Created by:				Liu Weifeng
 ** Created date:			2011-05-19
 ** Version:				    1.0
 ** Descriptions:			��NandFlash�����ĳ�������
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
	static const uint32 uiConstDefineBase = 0x00200000; //�����������ֵ
public:
	/*  NandFlash����  */
	static const uint32 uiMaxBlock 			= 200; 					//  �˴���ʾ��������
	static const uint32 uiMinBlock			= 10;						//	�˴���ʾ����С��
	static const uint32 uiMaxAddr 			= (256 * 1024 * 1024 - 1);
	static const uint32 uiBytePerSector 	= 2048; 					//  ÿ���������ֽ���
	static const uint32 uiSectorPerBlock 	= 64; 						//  ÿ�����������

	/*  ��NandFlash���ʵķ���ֵ*/
	//WangChangRong�޸ģ�ʹ��CErrorValueDefine����ʧ�ܺͳɹ��Ķ���
	//       static const uint32 uiFailed    = 0x00;     //  ����ʧ��
	//       static const uint32 uiSuccess   = 0x01;     //  �����ɹ�
	static const uint32 uiBadBlock 			= uiConstDefineBase + 0x02; //  ����
	static const uint32 uiBusy 				= CErrorValueDefine::uiConstReturnDeviceBusy; //  Flash��æ
	static const uint32 uiReady             = CErrorValueDefine::uiConstReturnDeviceReady;   //  Flash��æ
	static const uint32 uiParaError 		= uiConstDefineBase + 0x04; //  ��������

	static const uint32 uiMainSlaveStartSector	= 0x16;		//  ���ؿ�Main�������ļ��ص�ַ

    /*  Flash�ռ����  */
    static const uint32 uiDeviceAttriMasterSSector    = 0x30;   //  �豸����������ʼ������
    static const uint32 uiDeviceAttriSlaveSSector     = 0x33;   //  �豸���Ա�����ʼ������
    static const uint32 uiDeviceAttriReserveSectorNum = 0x02;   //  �豸���Ա�����������
    
    static const uint32 uiSecurityAttriMasterSSector    = 0x36;   //  ��ȫ����������ʼ������
    static const uint32 uiSecurityAttriSlaveSSector     = 0x39;   //  ��ȫ���Ա�����ʼ������
    static const uint32 uiSecurityAttriReserveSectorNum = 0x02;   //  ��ȫ���Ա�����������
    
    static const uint32 uiSlotMasterSSectorBase = 0x40;     //  ��λ��������������ʼ��������
    static const uint32 uiSlotSlaveSSectorBase  = 0x43;     //  ��λ�������ݱ�����ʼ��������
    static const uint32 uiSlotReserveSectorNum  = 0x02;     //  ��λ�������ݱ�����������
    
    static const uint32 uiSlot1MasterSSector    = (uiSlotMasterSSectorBase + 0x00) ;    //  ��λ0��������������ʼ������
    static const uint32 uiSlot1SlaveSSector     = (uiSlotSlaveSSectorBase + 0x00);      //  ��λ0�������ݱ�����ʼ������
    static const uint32 uiSlot1ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ0�������ݱ�����������

    static const uint32 uiSlot2MasterSSector    = (uiSlotMasterSSectorBase + 0x06);     //  ��λ1��������������ʼ������
    static const uint32 uiSlot2SlaveSSector     = (uiSlotSlaveSSectorBase + 0x06);      //  ��λ1�������ݱ�����ʼ������
    static const uint32 uiSlot2ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ1�������ݱ�����������

    static const uint32 uiSlot3MasterSSector    = (uiSlotMasterSSectorBase + 0x0C);     //  ��λ2��������������ʼ������
    static const uint32 uiSlot3SlaveSSector     = (uiSlotSlaveSSectorBase + 0x0C);      //  ��λ2�������ݱ�����ʼ������
    static const uint32 uiSlot3ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ2�������ݱ�����������

    
    static const uint32 uiSlot4MasterSSector    = (uiSlotMasterSSectorBase + 0x12);     //  ��λ3��������������ʼ������
    static const uint32 uiSlot4SlaveSSector     = (uiSlotSlaveSSectorBase + 0x12);      //  ��λ3�������ݱ�����ʼ������
    static const uint32 uiSlot4ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ3�������ݱ�����������

    static const uint32 uiSlot5MasterSSector    = (uiSlotMasterSSectorBase + 0x18);     //  ��λ4��������������ʼ������
    static const uint32 uiSlot5SlaveSSector     = (uiSlotSlaveSSectorBase + 0x18);      //  ��λ4�������ݱ�����ʼ������
    static const uint32 uiSlot5ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ4�������ݱ�����������

    static const uint32 uiSlot6MasterSSector    = (uiSlotMasterSSectorBase + 0x1E);     //  ��λ5��������������ʼ������
    static const uint32 uiSlot6SlaveSSector     = (uiSlotSlaveSSectorBase + 0x1E);      //  ��λ5�������ݱ�����ʼ������
    static const uint32 uiSlot6ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ5�������ݱ�����������

    static const uint32 uiSlot7MasterSSector    = (uiSlotMasterSSectorBase + 0x24);     //  ��λ6��������������ʼ������(���濨)
    static const uint32 uiSlot7SlaveSSector     = (uiSlotSlaveSSectorBase + 0x24);      //  ��λ6�������ݱ�����ʼ������
    static const uint32 uiSlot7ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ6�������ݱ�����������
    
    static const uint32 uiSlot8MasterSSector    = (uiSlotMasterSSectorBase + 0x2A);     //  ��λ7��������������ʼ������(���濨)
    static const uint32 uiSlot8SlaveSSector     = (uiSlotSlaveSSectorBase + 0x2A);      //  ��λ7�������ݱ�����ʼ������
    static const uint32 uiSlot8ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ7�������ݱ�����������
    
    static const uint32 uiSlot9MasterSSector    = (uiSlotMasterSSectorBase + 0x30);     //  ��λ8��������������ʼ������
    static const uint32 uiSlot9SlaveSSector     = (uiSlotSlaveSSectorBase + 0x30);      //  ��λ8�������ݱ�����ʼ������
    static const uint32 uiSlot9ReserveSectorNum = uiDeviceAttriReserveSectorNum;        //  ��λ8�������ݱ�����������
    
    static const uint32 uiSlot10MasterSSector    = (uiSlotMasterSSectorBase + 0x36);    //  ��λ9��������������ʼ������
    static const uint32 uiSlot10SlaveSSector     = (uiSlotSlaveSSectorBase + 0x36);     //  ��λ9�������ݱ�����ʼ������
    static const uint32 uiSlot10ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ9�������ݱ�����������
    
    static const uint32 uiSlot11MasterSSector    = (uiSlotMasterSSectorBase + 0x3C);    //  ��λ10��������������ʼ������
    static const uint32 uiSlot11SlaveSSector     = (uiSlotSlaveSSectorBase + 0x3C);     //  ��λ10�������ݱ�����ʼ������
    static const uint32 uiSlot11ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ10�������ݱ�����������
    
    static const uint32 uiSlot12MasterSSector    = (uiSlotMasterSSectorBase + 0x42);    //  ��λ11��������������ʼ������
    static const uint32 uiSlot12SlaveSSector     = (uiSlotSlaveSSectorBase + 0x42);     //  ��λ11�������ݱ�����ʼ������
    static const uint32 uiSlot12ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ11�������ݱ�����������
    
    static const uint32 uiSlot13MasterSSector    = (uiSlotMasterSSectorBase + 0x48);    //  ��λ12��������������ʼ������
    static const uint32 uiSlot13SlaveSSector     = (uiSlotSlaveSSectorBase + 0x48);     //  ��λ12�������ݱ�����ʼ������
    static const uint32 uiSlot13ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ12�������ݱ�����������
    
    static const uint32 uiSlot14MasterSSector    = (uiSlotMasterSSectorBase + 0x4E);    //  ��λ13��������������ʼ������
    static const uint32 uiSlot14SlaveSSector     = (uiSlotSlaveSSectorBase + 0x4E);     //  ��λ13�������ݱ�����ʼ������
    static const uint32 uiSlot14ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ13�������ݱ�����������
    
    static const uint32 uiSlot15MasterSSector    = (uiSlotMasterSSectorBase + 0x54);    //  ��λ14��������������ʼ������(��̫��ۿ�)
    static const uint32 uiSlot15SlaveSSector     = (uiSlotSlaveSSectorBase + 0x54);     //  ��λ14�������ݱ�����ʼ������
    static const uint32 uiSlot15ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ14�������ݱ�����������
    
    static const uint32 uiSlot16MasterSSector    = (uiSlotMasterSSectorBase + 0x5A);    //  ��λ15��������������ʼ������(��̫��ۿ�)
    static const uint32 uiSlot16SlaveSSector     = (uiSlotSlaveSSectorBase + 0x5A);     //  ��λ15�������ݱ�����ʼ������
    static const uint32 uiSlot16ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ15�������ݱ�����������
    
    static const uint32 uiSlot17MasterSSector    = (uiSlotMasterSSectorBase + 0x60);    //  ��λ16��������������ʼ������(���ؿ�)
    static const uint32 uiSlot17SlaveSSector     = (uiSlotSlaveSSectorBase + 0x60);     //  ��λ16�������ݱ�����ʼ������
    static const uint32 uiSlot17ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ16�������ݱ�����������
    
    static const uint32 uiSlot18MasterSSector    = (uiSlotMasterSSectorBase + 0x66);    //  ��λ17��������������ʼ������(���ؿ�)
    static const uint32 uiSlot18SlaveSSector     = (uiSlotSlaveSSectorBase + 0x66);     //  ��λ17�������ݱ�����ʼ������
    static const uint32 uiSlot18ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ17�������ݱ�����������
    
    static const uint32 uiSlot19MasterSSector    = (uiSlotMasterSSectorBase + 0x6C);    //  ��λ18��������������ʼ������(���ȵ�Դ��)
    static const uint32 uiSlot19SlaveSSector     = (uiSlotSlaveSSectorBase + 0x6C);     //  ��λ18�������ݱ�����ʼ������
    static const uint32 uiSlot19ReserveSectorNum = uiDeviceAttriReserveSectorNum;       //  ��λ18�������ݱ�����������
        
    
    static const uint32 uiHisAlarmStartSector       = 0xC0; //  ��ʷ�澯�ı��濪ʼ����
    static const uint32 uiHisAlarmEffectiveSector   = 0x01; //  ��ʷ�澯�ı�����Ϣ����Ч����
    static const uint32 uiHisAlarmReserveSector     = 0x03; //  ��ʷ�澯�ı�����Ϣ�ı�����������
    
    static const uint32 uiAlarmPerproptyMasterSSector       = 0xC5; //  �澯����������ʼ������
    static const uint32 uiAlarmPerproptySlaveSSector        = 0xC8; //  �澯���Ա�����ʼ������
    static const uint32 uiAlarmPerproptyReserveSectorNum    = 0x02; //  �澯���Ա�����������
    
    static const uint32 uiHisPerfStartSector        = 0xD0; //  ��ʷ���ܵı��濪ʼ����
    static const uint32 uiHisPerfEffectiveSector    = 0x01; //  ��ʷ���ܵı�����Ϣ����Ч����
    static const uint32 uiHisPerfReserveSector      = 0x03; //  ��ʷ���ܵı�����Ϣ�ı�����������
    
    static const uint32 uiBitInfoMasterSSector		= 0x400;//  Bit�ļ���Ϣ������ʼ������
    static const uint32 uiBitInfoSlaveSSector		= 0x403;//  Bit�ļ���Ϣ������ʼ������
    static const uint32 uiBitInfoReserveSector		= 0x02;	//  Bit�ļ���Ϣ������������
    static const uint32 uiBitFileStartSector		= 0x406;//  Bit�ļ��ı��濪ʼ����
    static const uint32 uiBitFileEndSector			= 0x7FF;//  Bit�ļ��ı�����ֹ����
};

#endif
