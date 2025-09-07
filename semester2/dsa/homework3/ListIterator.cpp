#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

//BC: theta(1)
//WC: theta(1)
//AC: theta(1) no logic based on variables
ListIterator::ListIterator(const IteratedList& list, int current, bool isValid)
	: list(list), current(current), isValid(isValid) {}


//BC: theta(1)
//WC: theta(1)
//AC: theta(1) no logic based on variables
void ListIterator::first() {
	current = list.head;
	isValid = (current != -1);
}

//BC: theta(1)
//WC: theta(1)
//AC: theta(1) no logic based on variables
void ListIterator::next() {
	if (current == -1 || !isValid) {
		throw std::exception("Iterator cannot move next from an invalid position");
	}
	current = list.next[current];
}

//BC: theta(1)
//WC: theta(1)
//AC: theta(1) no logic based on variables
bool ListIterator::valid() const {
	return current != -1 && isValid;
}

//BC: theta(1)
//WC: theta(1)
//AC: theta(1) no logic based on variables
TElem ListIterator::getCurrent() const {
	if (!isValid) {
		throw std::exception("Invalid iterator position");
	}
	if (valid()) {
		return list.elems[current];
	}
	throw std::exception("Invalid iterator position");
}

//BC: theta(1)
//WC: theta(1)
//AC: theta(1) no logic based on variables
int ListIterator::getPosition() const {
	return current;
}

//BC: theta(1)
//WC: theta(1)
//AC: theta(1) no logic based on variables
void ListIterator::setPosition(int position) {
	if (position < 0 || position >= list._size) {
		throw std::exception("Invalid position");
	}
	current = position;
}

//BC: theta(1)
//WC: theta(n)
//AC: O(n)
void ListIterator::jumpBackward(int k) {
    if (k <= 0 ) {
        throw std::exception("Invalid k. ");
    }
    if (!valid()) {
        throw std::exception("Invalid iterator.");
    }
    int pos = list.head;
    int previous = -1;
    int steps = 0;

    while (pos != -1 && pos != current) {
        previous = pos;
        pos = list.next[pos];
        steps++;
    }
    if (k > steps) {
        current = -1;
        isValid = false;
        return;
    }

    pos = list.head;
    for (int i = 0; i < steps - k; ++i) {
        pos = list.next[pos];
    }

    current = pos;
    isValid = true;
}

