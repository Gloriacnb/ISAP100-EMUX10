/*
 * CPowerCard.cpp
 *
 *  Created on: 2013-5-24
 *      Author: Administrator
 */

#include "CPowerCard.h"



CPowerCard::CPowerCard(uint8 slot, std::string& name) : CBaseCard(name, slot) {
	itsSlot = slot;

}

CPowerCard::~CPowerCard() {
	// TODO Auto-generated destructor stub
}

int CPowerCard::GetCartTypeID() {
	return TYPE_power;
}

int CPowerCard::getNextVersionIndex(uint8 sn) {
	return -1;
}
int CPowerCard::getVersion(uint8 id, STVersion&) {
	return -1;
}
