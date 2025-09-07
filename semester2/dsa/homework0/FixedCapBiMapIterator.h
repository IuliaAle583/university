#pragma once
#include "FixedCapBiMap.h"
class FixedCapBiMapIterator
{
	//DO NOT CHANGE THIS PART
	friend class FixedCapBiMap;
private:
	FixedCapBiMap& map;
	int currentPosition;
	//TODO - Representation

	FixedCapBiMapIterator( FixedCapBiMap& m);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
	
	//iterator bidirectional - iterator invalid => arunca o exceptie
	//iterator valid => schimbam current elem din iterator pe cel anterior
	//elem curent e primul-> nu setam pe cel anterior - setam iteratorul ca fiind invalid
	void previous();

	//iterator invalid => exceptie
	//stearga si returneze => tip TElem (un elem) - elem current din iterator
	//dupa stergere, currnet elem din iterator trb mutat pe urmatorul element
	//sterg ultimul elem, iterator invalid
	TElem remove();
};



