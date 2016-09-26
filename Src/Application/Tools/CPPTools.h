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
};

#endif /* CPPTOOLS_H_ */
