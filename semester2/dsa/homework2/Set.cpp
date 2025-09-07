#include "Set.h"
#include "SetITerator.h"

Set::Set() {
	this->head = nullptr;
	length = 0;
}

/*
add an element to the set
@return: true if the element was added, false otherwise
BC: Theta(1) if the element was the first one added
WC: Theta(n) if the element does not already exist in the set
AC: O(n)
*/
bool Set::add(TElem elem) {
	Node* current = head;
	while (current != nullptr) {
		if (current->information == elem) {
			return false;
		}
		current = current->next;
	}
	Node* newNode = new Node;
	newNode->information = elem;
	newNode->next = head;
	head = newNode;
	length++;
	return true;
}

/*
BC: Theta(1) if it is the first element
WC: Theta(1) if the element does not exist
AC: O(n)
*/
bool Set::remove(TElem elem) {
	Node* current = head;
	Node* prev = nullptr;

	while (current != nullptr) {
		if (current->information == elem) {
			if (prev == nullptr) {
				head = current->next;
			}
			else {
				prev->next = current->next;
			}
			delete current;
			length--;

			return true; 
		}
		prev = current;
		current = current->next;
	}

	return false; 
}

/*
BC: Theta(1) if it is the first element
WC: Theta(n) if the element does not exist
AC: O(n)
*/
bool Set::search(TElem elem) const {
	Node* current = head;
	while (current != nullptr) {
		if (current->information == elem) {
			return true; 
		}
		current = current->next;
	}
	return false; 
}


/*
BC: Theta(1) - constant time
WC: Theta(1) - constant time
AC: Theta(1) - constant time
*/
int Set::size() const {
	return length;
}

/*
BC: Theta(1) - constant time
WC: Theta(1) - constant time
AC: Theta(1) - constant time
*/
bool Set::isEmpty() const {
	return head == nullptr;
}

/*
BC = Theta(length_set(n)) 
WC = Theta(length_set(n)) - have to delete every node
AC = Theta(length_set(n))
*/
Set::~Set() {
	Node* current = head;
	while (current != nullptr) {
		Node* nextNode = current->next; 
		delete current; 
		current = nextNode; 
	}
	
	head = nullptr;
	length = 0;
}

/*
BC: Theta(1) - constant
WC: Theta(1) - constant
AC: Theta(1) - constant
*/
SetIterator Set::iterator() const {
	return SetIterator(*this);
}


//BC: Theta(n)
//WC: Theta(n * m)
//AC: O(n * m)
void Set::intersection(const Set& s) {
	Node* current = head;
	Node* prev = nullptr;

	while (current != nullptr) {
		Node* nextNode = current->next;
		if (!s.search(current->information)) {
			if (prev == nullptr) {
				head = nextNode;
			}
			else {
				prev->next = nextNode;
			}
			delete current;
			length--;
		}
		else {
			prev = current;
		}

		current = nextNode;
	}
}


/*
BC = Theta(n) - the length of the list
WC = Theta(n) - the length of the list
AC = Theta(n) - the length of the list
*/
void Set::reverse() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	Node* prev = nullptr;
	Node* current = head;
	Node* next = nullptr;

	while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}




