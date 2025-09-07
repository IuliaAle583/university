#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <stdexcept>


//BC=WC=AC=Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c), currentIndex(0), currentNode(nullptr), valueIndex(0) {
	first();
}

//BC=WC=TC=Theta(capacity)
TElem MultiMapIterator::getCurrent() const {
	if (!valid())
		throw std::out_of_range("Iterator is not valid.");
	return std::make_pair(currentNode->key, currentNode->value[valueIndex]);
}

//BC=WC=AC=Theta(1)
bool MultiMapIterator::valid() const {
	return currentNode != nullptr;
}

//BC=WC=AC=Theta(1)
void MultiMapIterator::next() {
    if (!valid())
        throw std::exception();

    if (valueIndex < currentNode->count - 1) {
        valueIndex++;
    }
    else {
        valueIndex = 0;
        currentNode = currentNode->next;
        if (!currentNode) {  
            // no next node in the list => move to the next bucket
            currentIndex++;
            while (currentIndex < col.capacity && !col.table[currentIndex]) {
                currentIndex++;
            }
            if (currentIndex < col.capacity) {
                currentNode = col.table[currentIndex];
            }
            else {
                currentNode = nullptr;  
            }
        }
    }
}

//BC=WC=AC=Theta(1)
void MultiMapIterator::first() {
    currentIndex = 0;
    while (currentIndex < col.capacity && !col.table[currentIndex]) {
        currentIndex++;
    }

    if (currentIndex < col.capacity) {
        currentNode = col.table[currentIndex];
        valueIndex = 0;
    }
    else {
        currentNode = nullptr;
    }
}

