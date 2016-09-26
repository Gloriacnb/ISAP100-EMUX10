/*
 * CTMFactory.h
 *
 *  Created on: 2013-11-5
 *      Author: Administrator
 */

#ifndef CTMFACTORY_H_
#define CTMFACTORY_H_

#include "CISAP100Factory.h"


class CTMFactory : public CISAP100Factory {
public:
	CTMFactory();
	virtual ~CTMFactory();

	virtual void initChips(void);

};

#endif /* CTMFACTORY_H_ */
