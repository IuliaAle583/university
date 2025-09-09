#pragma once

#include<typeinfo>
#include<fstream>
#include<iostream>
#include<random>
#include<string>

using namespace std;

template <class Type>
class Vector {
private:
	int size{};
	int capacity{};
	Type* elems;

public:
	explicit Vector(int capacity = 10);
	Vector(const Vector& theOneToCopy);
	~Vector();
	Vector<Type>& operator=(const Vector& something);
	void append(Type e);
	void remove(int i);
	void update(int index, Type element);

	Type operator[](int index);
	int getSize();
	int getCapacity();
	void clear();

	Type* begin() { return elems; }
	Type* end() { return elems + size; }
};

template <class Type>
inline Vector<Type>::Vector(int capacity) {
	// Constructor that initializes a vector with the given capacity.
	// size is initialized to 0 and elems is allocated with the given capacity.
	this->size = 0;
	this->capacity = capacity;
	this->elems = new Type[capacity];
}

template <class Type>
inline Vector<Type>::Vector(const Vector& theOneToCopy) {
	// Copy constructor that creates a new vector and copies elements from the given vector.
	// Allocates memory for the new vector and copies the elements.
	this->size = theOneToCopy.size;
	this->capacity = theOneToCopy.capacity;
	this->elems = new Type[this->capacity];
	for (int i = 0; i < this->size; i++) {
		this->elems[i] = theOneToCopy.elems[i];
	}
}

template <class Type>
inline Vector<Type>::~Vector() {
	// Destructor that deallocates the memory used for storing elements.
	delete[] this->elems;
}

template <class Type>
inline Vector<Type>& Vector<Type>::operator=(const Vector& something) {
	// Assignment operator that copies the elements from another vector.
	// Allocates new memory and copies the elements from the provided vector
	if (this == &something) return *this;

	this->size = something.size;
	this->capacity = something.capacity;
	if (this->elems != nullptr) {
		delete[] this->elems;
	}
	//delete[] this->elems;
	this->elems = new Type[something.capacity];
	for (int i = 0; i < something.size; i++) {		// am schimbat din capacity in size
		this->elems[i] = something.elems[i];
	}
	return *this;
}

template <class Type>
inline void Vector<Type>::append(Type e) {
	// Adds a new element to the end of the vector.
	// e: the element to append
	// If the vector is full, it doubles the capacity and reallocates the array.
	if (this->size == this->capacity) {
		this->capacity *= 2;
		Type* newElems = new Type[this->capacity];
		for (int j = 0; j < this->size; j++) {
			newElems[j] = this->elems[j];
		}
		delete[] this->elems;
		this->elems = newElems;
	}
	this->elems[this->size] = e;
	this->size++;
}

template <class Type>
inline void Vector<Type>::remove(int i) {
	// Removes the element at index i.
	// Shifts all subsequent elements to fill the gap.
	// If the index is invalid, no operation is performed.
	if (i < 0 || i >= this->size) {
		return;
	}
	for (int j = i; j < this->size - 1; j++) {
		this->elems[j] = this->elems[j + 1];
	}
	this->size--;
}

template <class Type>
inline void Vector<Type>::update(int index, Type element) {
	// Updates the element at the given index.
	// index: the index of the element updated
	// element: the element to update
	// Does nothing if the index is invalid.
	if (index < 0 || index >= this->size) {
		return;
	}
	this->elems[index] = element;

}

template<class Type>
inline Type Vector<Type>::operator[](int index) {
	// Returns the element at the specified index.
	// Throws an out_of_range exception if the index is invalid.
	if (index < 0 || index >= this->size) {
		throw out_of_range("Index out of bounds");
	}
	return this->elems[index];
}

template<class Type>
inline int Vector<Type>::getSize() {
	// Returns the number of elements in the vector.
	// Return type: int
	return this->size;
}

template<class Type>
inline int Vector<Type>::getCapacity() {
	// Returns the capacity of the vector (maximum number of elements it can hold).
	// Return type: int
	return this->capacity;
}

template <class Type>
void Vector<Type>::clear() {
	// Clears the vector by deleting all elements and resetting size and capacity.
	// Allocates a new array with the default capacity (10).
	delete[] this->elems;
	this->size = 0;
	this->capacity = 10;
	this->elems = new Type[this->capacity];
}