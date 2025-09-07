
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"


//BC: Theta(n), where n is the capacity of the list
//WC: Theta(n), where n is the capacity of the list
//AC: Theta(n), where n is the capacity of the list
IteratedList::IteratedList() : head(-1), tail(-1), firstFree(0), _size(0), capacity(10) {
	elems = new TElem[capacity];
	next = new int[capacity];
	previous = new int[capacity];

	for (int i = 0; i < capacity; i++) {
		next[i] = i + 1;
		previous[i] = i - 1;
	}
	next[capacity - 1] = -1;
	previous[0] = -1;
}

//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
int IteratedList::size() const {
	//TODO - Implementation
	return _size;
}


//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
bool IteratedList::isEmpty() const {
	//TODO -  Implementation
	return _size == 0;
}

//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
ListIterator IteratedList::first() const {
	if (_size > 0) {
		return ListIterator(*this, head, true);
	}
	return ListIterator(*this, -1, false);
}

//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
TElem IteratedList::getElement(ListIterator pos) const {
	//TODO - Implementation
	if (!pos.valid()) {
		throw std::exception("Invalid iterator");
	}
	return elems[pos.getPosition()];
}

//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
TElem IteratedList::remove(ListIterator& pos) {
	//TODO - Implementation
	if (head == -1) {
		tail = -1;
	}
	if (!pos.valid()) {
		throw std::exception("Invalid iterator position");
	}

	int currentPos = pos.getPosition();
	TElem removedElement = elems[currentPos];

	if (previous[currentPos] != -1) {
		next[previous[currentPos]] = next[currentPos];
	}
	else {
		head = next[currentPos];
	}

	if (next[currentPos] != -1) {
		previous[next[currentPos]] = previous[currentPos];
	}
	else {
		tail = previous[currentPos];
	}

	next[currentPos] = firstFree;
	previous[currentPos] = -1;
	firstFree = currentPos;

	_size--;

	if (currentPos == tail) {
		pos.setPosition(-1);
	}
	else {
		pos.next();
	}

	return removedElement;
}

//BC: Theta(1), where n is the capacity of the list
//WC: Theta(n), where n is the capacity of the list
//AC: O(n), where n is the capacity of the list
ListIterator IteratedList::search(TElem e) const {
	int current = head;
	while (current != -1) {
		if (elems[current] == e) {
			return ListIterator(*this, current, true);
		}
		current = next[current];
	}
	return ListIterator(*this, -1, false);
}

//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
TElem IteratedList::setElement(ListIterator pos, TElem e) {
	//TODO - Implementation
	if (!pos.valid()) {
		throw std::exception("Invalid iterator position");
	}
	int currentPos = pos.getPosition();
	TElem oldElem = elems[currentPos];
	elems[currentPos] = e;
	return oldElem;
}

//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (!pos.valid()) {
		throw std::exception("Invalid iterator position");
	}

	int current = pos.getPosition();
	int newPos = allocate();
	elems[newPos] = e;

	next[newPos] = next[current];
	previous[newPos] = current;

	if (next[current] != -1) {
		previous[next[current]] = newPos;
	}
	else {
		tail = newPos;
	}

	next[current] = newPos;

	_size++;
	pos.setPosition(newPos);
}


//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
void IteratedList::addToEnd(TElem e) {
	int newPos = allocate();
	elems[newPos] = e;
	next[newPos] = -1;
	previous[newPos] = tail;

	if (tail != -1) {
		next[tail] = newPos;
	}
	tail = newPos;

	if (head == -1) {
		head = newPos;
	}

	_size++;
}

//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
void IteratedList::addToBeginning(TElem e) {
	int newPos = allocate();
	elems[newPos] = e;
	previous[newPos] = -1;
	next[newPos] = head;

	if (head != -1) {
		previous[head] = newPos;
	}
	head = newPos;

	if (tail == -1) {
		tail = newPos;
	}

	_size++;
}


//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
IteratedList::~IteratedList() {
	delete[] elems;
	delete[] next;
	delete[] previous;
}


//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
int IteratedList::allocate() {
	if (firstFree == -1) {
		resize();
	}
	int position = firstFree;
	firstFree = next[firstFree];
	return position;
}


//BC: Theta(n), where n is the capacity of the list
//WC: Theta(n), where n is the capacity of the list
//AC: Theta(n), where n is the capacity of the list
void IteratedList::resize() {
	int newCapacity = capacity * 2;
	TElem* newElements = new TElem[newCapacity];
	int* newNext = new int[newCapacity];
	int* newPrev = new int[newCapacity];

	for (int i = 0; i < capacity; i++) {
		newElements[i] = elems[i];
		newNext[i] = next[i];
		newPrev[i] = previous[i];
	}

	for (int i = capacity; i < newCapacity - 1; i++) {
		newNext[i] = i + 1;
		newPrev[i] = -1;
	}
	newNext[newCapacity - 1] = -1;

	if (firstFree == -1) {
		firstFree = capacity;
	}

	delete[] elems;
	delete[] next;
	delete[] previous;

	elems = newElements;
	next = newNext;
	previous = newPrev;
	capacity = newCapacity;
}
