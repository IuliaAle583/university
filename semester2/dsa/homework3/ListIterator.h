#pragma once
#include "IteratedList.h"

//DO NOT CHANGE THIS PART
class IteratedList;
typedef int TElem;

class ListIterator {
	friend class IteratedList;
private:
	const IteratedList& list;   
	int current;                
	bool isValid;
	//const IteratedList& list;
	//ListIterator(const IteratedList& lista);
public:
	ListIterator(const IteratedList& list, int current = -1, bool isValid = false);
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;
	int getPosition() const;
	void setPosition(int position);
	void jumpBackward(int k);
};



