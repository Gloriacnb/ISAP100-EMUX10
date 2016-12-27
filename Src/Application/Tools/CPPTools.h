/*
 * CPPTools.h
 *
 *  Created on: 2013-4-12
 *      Author: Administrator
 */

#ifndef CPPTOOLS_H_
#define CPPTOOLS_H_

#include <string>
#include "EZ_types.h"
class CPPTools {
public:
	CPPTools();
	virtual ~CPPTools();

	static std::string number2string(uint32 i);
	static uint32 ezip_aton(std::string& s);
	static void ezip_aton(std::string& s, uint8* ip);
};

#endif /* CPPTOOLS_H_ */
