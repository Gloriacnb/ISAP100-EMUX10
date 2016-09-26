
#ifndef PCM821054_H_
#define PCM821054_H_

#include "EZ_types.h"

#define DEF_MAX_VF_NUM	32
#define DEF_REGADDR_CPLD_UP_SIGNAL 0x0100	//WO
#define DEF_REGADDR_CPLD_DOWN_SIGNAL 0x0120 //RO
										//bit 3 a
										//bit 2 b
										//bit 1 c fix 1
										//bit 0 d fix 0
#define DEF_LED_ON 	0
#define DEF_LED_OFF 1

#define DEF_MT_Nomal 0
#define DEF_MT_Wave  1

#define DEF_VFType_MT	1
#define DEF_VFType_4W	2
#define DEF_VFType_FXS 	3
#define DEF_VFType_FXO	4
#define DEF_VFType_2W	5

typedef struct {
	uint8 State;			//0--unused, 1--normal
	uint8 ChipID;			//1~8
	uint8 ChannelID;		//1~4
	uint16 UpSignalAddr; 	//-- WO
	uint16 DownSignalAddr; 	//-- RO
	uint8 Type;				// 4--FXO, 3--FXS
	uint8 led;				//对应话路指示灯状态 0 亮，1灭
	uint8 BakSHK;			//bit1 shk1, bit0 shk2
	uint8 BakAB;			//bit1 a, bit0 b
	uint8 mode;				//0 自动电话 1 热线
	uint8 RCFlag;			//0 start; 1 ring; 2 idle
	uint32 startTime;		//振铃处理起始时间
}STVoiceChannel;

//void InitCPLDRegister();
void Init821054(uint8);
//void SignalProcess(int chipID);

int CountValidVoiceChannel(void);
int GetValidVF(int StartSN);
int GetVfMode(int vfSn);
void SetVfMode(int vfSn, int newMode);
void SetVFLED(int vfSn, int mode);

int setPowerDown(uint8 chipID, uint8 ch, uint8 pd);
int setLoopBackAnalogOnebit(uint8 chipID, uint8 ch, uint8 loop);
int setLoopBackDigitalOnebit(uint8 chipID, uint8 ch, uint8 loop);
//extern "C" uint8 GetVoiceChannelType(int chipID, int channelID);

extern STVoiceChannel stVC[DEF_MAX_VF_NUM];
#endif /* IDT821054RegisterMap_H_ */

