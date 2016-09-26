/*
 * CUpE1Port_define.h
 *
 *  Created on: 2016��1��8��
 *      Author: Administrator
 */


#ifndef CUPE1PORT_DEFINE_H_
#define CUPE1PORT_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "AlarmElement_define.h"

typedef struct {
    uint32 bitMap; //dcnʱ��ʾtsʱ϶λͼ��dccʱ����ʾsabit��OH����ռ��
}NM_CH_ConfigData_T;

typedef struct {
    uint8 porten; //1 ���뽻����ϵ���������˿ڰ󶨡�ch�жϴ򿪣��� 0 �����뽻������������˿ڡ�ch�жϹرգ�
    uint8 type;   //0 dcc, 1 dcn;
    uint8 topodir; //��Ӧ�����˿�ID
    uint8 desc[32];
    uint8 descLen;
    NM_CH_ConfigData_T sabitCH;
    NM_CH_ConfigData_T dcnCH;
}FE1_NM_Config_Data_T;

typedef enum {
	UPE1_LOS,
	UPE1_AIS,
	UPE1_LOF,
//	UPE1_LOM,
	UPE1_type_size,
	UPE1_type_base = 1024
}UPE1_alarm_type_E;

typedef struct {
	Alarm_property_T alarm_property[UPE1_type_size];
	uint8 enable;
	uint8 mode;
	uint8 desc[32];
	uint8 dlen;
	FE1_NM_Config_Data_T nmcfg;
}UPE1_Config_Data_T;

#if defined (__cplusplus)
}
#endif
#endif /* CUPE1PORT_DEFINE_H_ */
