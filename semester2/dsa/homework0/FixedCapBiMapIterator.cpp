#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator( FixedCapBiMap& d) : map(d)
{
	this->currentPosition = 0;
}


void FixedCapBiMapIterator::first() {
	this->currentPosition = 0;
}


void FixedCapBiMapIterator::next() {
	if (this->currentPosition == this->map.mapSize)
		throw exception();
	this->currentPosition++;
}


TElem FixedCapBiMapIterator::getCurrent() {
	if (this->currentPosition == this->map.mapSize)
		throw exception();
	return this->map.elements[this->currentPosition];
	//return NULL_TELEM;
}


bool FixedCapBiMapIterator::valid() const {
	return this->currentPosition < this->map.mapSize;
	//return false;
}

void FixedCapBiMapIterator:: previous() {
	if (!this->valid()) {
		throw exception();  
	}
	if (this->currentPosition == 0) {
		this->currentPosition = -1;  
		return;
	}
	this->currentPosition--;  
}


TElem FixedCapBiMapIterator::remove() {
	if (!this->valid()) {
		throw exception();  
	}

	TElem removedElement = this->map.elements[this->currentPosition];  

	//for (int i = this->currentPosition; i < this->map.mapSize - 1; i++) {
	//	this->map.elements[i] = this->map.elements[i + 1];
	//}
	TElem lastPosition = this->map.elements[this->map.mapSize];
	this->map.elements[this->map.mapSize] = removedElement;

	if (this->currentPosition == this->map.mapSize) {
		this->currentPosition = -1;
	}
	else {
		this->map.mapSize--;
		this->currentPosition++;
	}

	return removedElement;
}



