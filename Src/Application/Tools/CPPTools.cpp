/*
 * CPPTools.cpp
 *
 *  Created on: 2013-4-12
 *      Author: Administrator
 */

#include "CPPTools.h"
#include <string>
#include <sstream>
#include <stdio.h>

CPPTools::CPPTools() {
	// TODO Auto-generated constructor stub

}

CPPTools::~CPPTools() {
	// TODO Auto-generated destructor stub
}

std::string CPPTools::number2string(uint32 number) {
	std::ostringstream s;
	s << number;
	return s.str();

}

/*
 * �������ʽ��IP��ַת��Ϊ32λ����
 * ��"192.168.100.1" ת��Ϊ  IP = 0xC0A86401
 */
uint32 CPPTools::ezip_aton(std::string& s) {
    uint32 netIP = 0;
    uint8 p[4] = {0};
    ezip_aton(s, p);
    netIP = (p[0] << 24) |
            (p[1] << 16) |
            (p[2] <<  8) |
            (p[3] <<  0) ;
    return netIP;
}

/*
 * �������ʽ��IP��ַת��Ϊchar���飬
 * �磺"192.168.100.1" ת��Ϊ  ip[] = {192, 168, 100, 1}
 */
void CPPTools::ezip_aton(std::string& s, uint8* ip) {
    int p[4] = {0};
    sscanf(s.c_str(), "%d.%d.%d.%d", &p[0], &p[1], &p[2], &p[3]);
    for( int i = 0; i < 4; i++ ) {
        ip[i] = (uint8)p[i];
    }
}
