/*
 * CPPTools.cpp
 *
 *  Created on: 2013-4-12
 *      Author: Administrator
 */

#include "CPPTools.h"
#include <string>
#include <sstream>
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

