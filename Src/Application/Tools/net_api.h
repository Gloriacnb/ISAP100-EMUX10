/*
 * net_api.h
 *
 *  Created on: 2013-12-23
 *      Author: Administrator
 */

#ifndef NET_API_H_
#define NET_API_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"

void initNetApi(void);
/*
 * 设置设备IP，MAC地址
 */
void setNetIP(uint8* ip, uint8* mask);
void setNetGW(uint8* gw);
void setNetMAC(uint8* mac);

/*
 * IP tools
 */
int ifIPExist(uint8* ip);

void pingCallback(uint8 evt);

#if defined (__cplusplus)
}
#endif
#endif /* NET_API_H_ */
