/*
 * net_api.c
 *
 *  Created on: 2013-12-23
 *      Author: Administrator
 */
#include "net_api.h"
#include <Net_Config.h>
#include <string.h>
#include <rtl.h>

extern LOCALM localm[];
extern U8 own_hw_adr[];

//void Ping(void*);
//OS_TID task_ping;
OS_SEM sem_ping;
OS_MUT mut_ping;
static uint8 IP_EXIST;

void initNetApi(void) {
    os_sem_init(sem_ping, 0);
    os_mut_init(mut_ping);
}

void setNetIP(uint8* ip, uint8* mask) {
    if( ip ) {
        memcpy (localm[NETIF_ETH].IpAdr, ip, 4 );
    }
    if( mask ) {
        memcpy (localm[NETIF_ETH].NetMask, mask, 4 );
    }
}


void setNetGW(uint8* gw) {
    if( gw ) {
        memcpy (localm[NETIF_ETH].DefGW, gw, 4 );
    }
}

void setNetMAC(uint8* mac) {
    memcpy (own_hw_adr, mac , 6);
}

/*
 * ͨ��Ping��֤IP�Ƿ����
 * ����ֵ 0�� ping��Ӧok
 *     1. ping��ʱ
 *     -1. icmp��������
 */
int ifIPExist(uint8* ip) {
    int rtn = -1;
    os_mut_wait(mut_ping, 0xffff);
    if( icmp_ping(ip, pingCallback) == __TRUE ) {
        os_sem_wait(sem_ping, 0xffff);
        rtn = IP_EXIST;
    }
    os_mut_release(mut_ping);
    return rtn;
}



void pingCallback(uint8 evt) {
    IP_EXIST = evt;
    os_sem_send(sem_ping);
}

