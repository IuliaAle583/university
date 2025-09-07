#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//BC=WC=TC=theta (1)
int MultiMap::hash(TKey c) const
{
		return abs(c) % capacity;
}

//BC=WC=TC=Theta(n)
void MultiMap::rehash()
{
		int old = capacity;
		capacity *= 2;
		Node** newTable = new Node * [capacity] {};

		for (int i = 0; i < old; i++) {
			Node* data = table[i];
			while (data != nullptr) {
				Node* next = data->next;
				int index = hash(data->key);
				//insert the node at the beginning of the linked list at the new index
				data->next = newTable[index];
				newTable[index] = data;
				data = next;
			}
		}

		delete[] table;
		table = newTable;
}

//BC=theta(1)
//Wc=theta(n)
//TC= O(n)
void MultiMap::Node::addNode(TValue val)
{
	if (count == capacity) {
		capacity *= 2;
		TValue* newValues = new TValue[capacity];
		for (int i = 0; i < count; i++) {
			newValues[i] = value[i];
		}
		delete[] value;
		value = newValues;
	}
	value[count++] = val;
}

//BC=WC=TC=Theta(capacity)
MultiMap::MultiMap() : capacity(10), nrElements(0) {
	table = new Node * [capacity] {};
}

//adds a key value pair to the multimap
//BC=Theta(1)
//WC=Theta(capacity)
//TC=O(capacity)
void MultiMap::add(TKey c, TValue v) {
	int i = hash(c);
	Node* data = table[i];
	//check if the node exists
	while (data != nullptr && data->key != c) {
		data = data->next;
	}
	//if no node with the key was found, create a new one
	if (data == nullptr) {
		data = new Node(c);
		data->next = table[i];	//insert at the begining
		table[i] = data;
	}
	//add the value to the node
	data->addNode(v);
	nrElements++;
	if (nrElements / capacity > 1) {
		rehash();
	}
}

//removes a key value pair from the multimap
//returns true if the pair was removed and false otherwise
//BC=Theta(1)
//WC=Theta(capacity)
//TC=O(capacity)
bool MultiMap::remove(TKey c, TValue v) {
	int i = hash(c);
	Node* data = table[i];
	Node* previous = nullptr;

	while (data != nullptr) {
		if (data->key == c) {
			for (int j = 0; j < data->count; ++j) {
				if (data->value[j] == v) {
					// shift elements left to remove the value
					for (int k = j; k < data->count - 1; ++k) {
						data->value[k] = data->value[k + 1];
					}
					data->count--;
					nrElements--;
					//if there are no more values for this key, remove the node 
					if (data->count == 0) {
						if (previous == nullptr) { 
							table[i] = data->next;	//head
						}
						else {
							previous->next = data->next;	//middle/end
						}
						delete data;
					}
					return true;
				}
			}
		}
		//move to the next node in the chain
		previous = data;
		data = data->next;
	}
	return false;

}

//returns a vector with all the values to which the key is mapped
//BC=Theta(1)
//WC=Theta(capacity)
//TC=O(capacity)
vector<TValue> MultiMap::search(TKey c) const {
	int index = hash(c);
	Node* data = table[index];
	while (data != nullptr) {
		if (data->key == c) {
			//if found, return a vector with all its values
			vector<TValue> values(data->value, data->value + data->count);
			return values;
		}
		data = data->next;
	}
	//empty vector
	return vector<TValue>();
}


//BC=Theta(1), WC=Theta(1), TC=Theta(1)
int MultiMap::size() const {
	return nrElements;
}

//BC=Theta(1), WC=Theta(1), TC=Theta(1)
bool MultiMap::isEmpty() const {
	return nrElements == 0;
}

//BC=Theta(1), WC=Theta(1), TC=Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//BC=WC=TC=Theta(capacity)
MultiMap::~MultiMap() {
	for (int i = 0; i < capacity; i++) {
		Node* current = table[i];	//get the head of the list
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] table;		//delete the array of pointers
}


//BC: theta(n) - all the elements are the same
//AC: O(m*n) - nr of elements * number of distinct values
//WC: theta(n^2) - all the values differ
TValue MultiMap::mostFrequent() const
{
	if (isEmpty()) {
		return NULL_TVALUE;
	}

	vector<pair<TValue, int>> freq;

	for (int i = 0; i < capacity; ++i) {
		Node* current = table[i];
		while (current != nullptr) {
			for (int j = 0; j < current->count; ++j) {
				TValue val = current->value[j];
				bool found = false;
				for (auto& entry : freq) {
					if (entry.first == val) {
						entry.second++;
						found = true;
						break;
					}
				}
				//does not exits => add it with freq 1
				if (!found) {
					freq.push_back(make_pair(val, 1));
				}
			}
			current = current->next;
		}
	}

	int maxFreq = 0;
	TValue mostFreqValue = NULL_TVALUE;

	for (const auto& entry : freq) {
		if (entry.second > maxFreq) {
			maxFreq = entry.second;
			mostFreqValue = entry.first;
		}
	}

	return mostFreqValue;
}

