/*
 * InnerDCCManager.h
 *
 *  Created on: 2013-7-1
 *      Author: Administrator
 */

#ifndef INNERDCCMANAGER_H_
#define INNERDCCMANAGER_H_

#include "CMSSave.h"

typedef struct {
	uint8 portSn; 	//DCC通道所属内部虚拟端口号
	uint32 uid;		//标识DCC通道的统一编码
}DCC_CH_Config;

typedef struct {
	DCC_CH_Config ch_rcv[4];
	DCC_CH_Config ch_snd[4];
	uint8 chRNum;
	uint8 chSNum;

}Inner_DCC_Config;

typedef struct {
	Inner_DCC_Config port[2];
	uint8 portNum; //软交换口数量
	uint32 crc;
}Inner_Port_Config;

class InnerDCCManager {
	enum {InnerPort = 2, DCC_Per_Port = 4, InnerPortDefaultSn = 3};

public:
	InnerDCCManager();
	virtual ~InnerDCCManager();

private:
	CMSSave FlashDriver;
	Inner_Port_Config configData;
	void RestoreDefaultConfig(void);
};

#endif /* INNERDCCMANAGER_H_ */
