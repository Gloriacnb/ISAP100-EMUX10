/*
 * SysError.h
 *
 *  Created on: 2013-11-20
 *      Author: Administrator
 */

#ifndef SYSERROR_H_
#define SYSERROR_H_

#include <stdexcept>
#include <string>

class SysError : public std::runtime_error {
public:
    SysError(const std::string& msg = "") : runtime_error(msg) {};
};

#endif /* SYSERROR_H_ */
