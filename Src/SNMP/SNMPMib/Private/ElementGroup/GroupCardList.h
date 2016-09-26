/*
 * GroupCardList.h
 *
 *  Created on: 2013-7-8
 *      Author: Administrator
 */

#ifndef GROUPCARDLIST_H_
#define GROUPCARDLIST_H_


#include "CMibGroup.h"

enum {
	table_card,
	table_card_size
};

class GroupCardList : public CMibGroup {
	GroupCardList();
public:
	GroupCardList(uint32* oid, uint8 oidlen);
	virtual ~GroupCardList();

//	virtual table_info_T* getTableInfo(int sn);
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_card_size];
};

#endif /* GROUPCARDLIST_H_ */
