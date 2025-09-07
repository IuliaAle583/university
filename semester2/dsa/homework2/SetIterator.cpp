#include "SetIterator.h"
#include "Set.h"
#include <iostream>

SetIterator::SetIterator(const Set& m) : set(m), currentNode(m.head) {
	
}

//BC = Theta(1) - constant
//WC = Theta(1) - constant
//TC = Theta(1)	- constant
void SetIterator::first() {
	currentNode = set.head;
}

//BC = Theta(1) - constant
//WC = Theta(1) - constant
//TC = Theta(1)	- constant
void SetIterator::next() {
	if (currentNode == nullptr) {
		throw std::exception("Iterator is not valid.");
	}
	currentNode = currentNode->next;
}


//BC = Theta(1) - constant
//WC = Theta(1) - constant
//TC = Theta(1)	- constant
TElem SetIterator::getCurrent()
{
	if (currentNode == nullptr) {
		throw std::exception("Iterator is not valid.");
	}
	return currentNode->information;
}

//BC = Theta(1) - constant
//WC = Theta(1) - constant
//TC = Theta(1)	- constant
bool SetIterator::valid() const {
	return currentNode != nullptr;
}



