/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			IDT821054RegisterMap.h
 ** File path:			/EMUX300M0/Src/HardwareDrivers/IDT821054RegisterMap.h
 ** Created by:          Shqp
 ** Created date:        2012-6-27
 ** Version:             V0.1
 ** Descriptions:        ²Î¿¼¡¶IDT_821054_DST_20030226.pdf¡·
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#ifndef IDT821054REGISTERMAP_H_
#define IDT821054REGISTERMAP_H_

/* Local Read/Write Register */
#define IDT_LREG_Coefficient_Selection	0x00		//filter enable/disable P31
#define IDT_LREG_LocalLoop_SLICInterrupt	0x01		//bit7~3 IE4~0//bit 2 Digital Loopback via Time Slots
//bit 1 Analog Loopback via Onebit
//bit 0 Digital Loopback via Onebit

#define IDT_LREG_DSH_GK_Debounce			0x02		//bit7~4 GK//bit3~0 DSH

#define IDT_LREG_Channel_IOData			0x03		//bit 7 Reserved//bit 6~5 SO2~1
//bit 4~2 SB3~1
//bit 1~0 SI2~1

#define IDT_LREG_Transmit_Timeslot		0x04   		//bit 7 0:DX1 1:DX2//bit 6~0 Ts0~Ts127

#define IDT_LREG_Recieve_Timeslot		0x05		//bit 7 0:DR1 1:DR2//bit 6~0 Ts0~Ts127

#define IDT_LREG_Gain_Powerdown_Cutoff	0x08		//bit 7 PD//bit 6 PCMCT
//bit 5 GAD
//bit 4 GDA
//bit 3~0 always 0

#define IDT_LREG_Tone_Generator			0x09		//bit 7~4 Reserved//bit 3~2 must 1
//bit 1 Tone1 enable
//bit 0 Tone0 enable

/* Local Read only Register */
#define IDT_LREG_PCM_Data_Low			0x06
#define IDT_LREG_PCM_Data_High			0x07

/* Global Read only Register */
#define IDT_GREG_Version_Number			0x20
#define IDT_GREG_SI_Data				0x28	//bit 7~4 debounced data (ground key status)//on the SI2 pins of Channel 4 to Channel 1
//bit 3~0 the debounced data (ground key status)
//on the SI2 pins of Channel 4 to Channel 1
/* Global write only Register */
#define IDT_GREG_Interrupt_Clear		0x21
#define IDT_GREG_Software_Reset			0x22
#define IDT_GREG_Hardware_Reset			0x23

/* Global Read/write Register */

#define IDT_GREG_Chopper_Clock			0x24	//bit 7~6 Reserved 	²Î¿¼P24//bit 5~4 Chclk2
//bit 3~0 Chclk1

#define IDT_GREG_MCLK_Channel_Program	0x25	//bit 7~4 Channel enable//bit 3~0 Clock Selection

#define IDT_GREG_CODEC_Parameter		0x26	//bit 7 A or u//bit 6 Voice Data Selection
//bit 5 Single or Double Clock
//bit 4~3 Clock Edges

#define IDT_GREG_Ring_Trip				0x27	//bit 7 Output Polarity Indicator//bit 6 Reserved
//bit 5 Input Polarity Indicator
//bit 4 Input Selection
//bit 3 Ring Trip Enable bit
//bit 2~0 Output Selection

#define IDT_GREG_SB1_Control_Status		0x29	//bit 7~4 determine the directions of the SB1 pins of Channel 4 to Channel 1//bit 3~0 When SB1 input,contain the status of these four SB1 pins
//		  When SB1 output,the control data is written to these four SB1 pins via
#define IDT_GREG_SB2_Control_Status		0x2A
#define IDT_GREG_SB3_Control_Status		0x2B
#define IDT_GREG_FSK_Flag_Length		0x2C
#define IDT_GREG_FSK_Data_Length		0x2D
#define IDT_GREG_FSK_Seizure_Length		0x2E
#define IDT_GREG_FSK_Mark_Length		0x2F
#define IDT_GREG_FSK_CommCTRL			0x30
#define IDT_GREG_Level_Meter_Result_Low	0x31
#define IDT_GREG_Level_Meter_Result_high	0x32
#define IDT_GREG_Level_Meter_Count_Number	0x33
#define IDT_GREG_Level_Meter_Ctrl		0x34
#define IDT_GREG_Loopback_PllPowerdown	0x35	//bit 7~6 Reserved//bit 5 PLL Power Down
//bit 4 Digital Loopback via Analog Interface
//bit 3 Analog Loopback via 8 kHz
//bit 2 Digital Loopback via 8 kHz
//bit 1 Digital Loopback from DR to DX
//bit 0 Analog Loopback from DX to DR

#define IDT_GREG_Over_Sampling_Timing	0x37

#endif /* IDT821054REGISTERMAP_H_ */
