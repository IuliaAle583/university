#include "Matrix.h"
#include "MatrixIterator.h"
#include <exception>
using namespace std;


// Constructor - initializing a new MAtrix object (dimension is specified)
// time complexity:
//BC: theta(1) constant time operations no matter the size
//WC: theta(1) same as BC, operations do not depend on the size
//AC: theta(1) same as BC and WC
Matrix::Matrix(int nrLines, int nrCols) {

	this->numberLines = nrLines;
	this->numberColums = nrCols;
	this->size = 0;
	this->capacity = 1;
	this->tripl = new Triple[capacity];
}

// Find the number of rows in the matrix
// time complexity:
//BC: theta(1) by directly accessing the variable
//WC: theta(1) the same as the BC
//AC: theta(1) the same by having constant execution time no matter the input
int Matrix::nrLines() const {
	//TODO - Implementation
	return this->numberLines;
}

/*
find the number of colums in the matrix
time complexity:
BC: theta(1) by directly accessing the variable
WC: theta(1) same as BC
AC: theta(1) the same by having constant execution time no matter the input
*/
int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->numberColums;
}

/*
Returns an element found at a specified position, throw exception is out of bounds
time complexity:
BC: theta(1) - the position given for the element was the first one
WC: theta(n) - the element was on the last position or not into the matrix
AC: O(n) - by assuming the elements are evenly distributed in the matrix
*/
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->numberLines || j < 0 || j >= this->numberColums) {
		throw exception();
	}
	for (int k = 0; k < this->size; k++) {
		if (this->tripl[k].first.first == i && this->tripl[k].first.second == j) {
			return this->tripl[k].second;
		}
	}
	return NULL_TELEM;
}

/*
Modifies or inserts an element at a specified position
time complexity:
BC: theta(1) - the element to be modified is the first one found
WC: theta(n) - the element is added or its the last one checked
AC: O(n) - by assuming uniformity in distribution of elements
*/
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= this->numberLines || j < 0 || j >= this->numberColums) {
		throw out_of_range("Position is out of range.");
	}

	int position = 0;
	while (position < size && (tripl[position].first.first < i ||
		(tripl[position].first.first == i && tripl[position].first.second < j))) {
		position++;
	}

	if (position < size && tripl[position].first.first == i && tripl[position].first.second == j) {
		TElem old = tripl[position].second;
		if (e == NULL_TELEM) {
			for (int k = position; k < size - 1; k++) {
				tripl[k] = tripl[k + 1];
			}
			size--;
		}
		else {
			tripl[position].second = e;
		}
		return old;  
	}
	else if (e != NULL_TELEM) {
		if (this->size == this->capacity) {
			resize();
		}
		for (int k = size; k > position; k--) {
			tripl[k] = tripl[k - 1];
		}
		tripl[position] = { {i, j}, e };
		size++;
	}

	return NULL_TELEM;
}


/*
Doubles the capacity of the array if new space is needed
time complexity:
BC: theta(n) - proportional to the current size because of the copys of the elements\
WC: theta(n) - same as BC
AC: theat(n) - because the copying of elements is compulsory
*/
void Matrix::resize() {
	this->capacity *= 2;
	Triple* newTripl = new Triple[capacity];
	for (int i = 0; i < size; i++) {
		newTripl[i] = this->tripl[i];
	}
	delete[] this->tripl;
	this->tripl = newTripl;
}


/*
finds the positon of an element
BC: theta(1) -  the element is found on the first position
WC: theta(n) - the element is on the last position or not in the array
AC: O(n) - the element is found in the middle or not found
*/
pair<int, int> Matrix::findPositon(TElem e) const {
	for (int k = 0; k < this->size; k++) {
		if (this->tripl[k].second == e) {
			return { this->tripl[k].first.first, this->tripl[k].first.second };
		}
	}
	return { -1,-1 };
}

/*
Destructor - clean up the dynamically allocated memory
time complexity:
BC: theta(1) deletion of the array is done in constant time
WC: theta(1) it does not depend on the size of the array
Ac: theta(1) by having a constant time execution
*/
Matrix::~Matrix() {
	delete[] this->tripl;
}

/*
time complexity:
BC: theta(1) - line exception is thrown immediatly when entering the function
WC: theta(n) - all the elements are checked
AC: O(n)
*/
int Matrix::numberOfZero(int line) const {
	if (line < 0 || line >= numberLines) {
		throw exception();
	}
	int nr = 0;
	for (int i = 0; i < size; i++) {
		if (tripl[i].first.first == line && tripl[i].second != NULL_TELEM) {
			++nr;
		}
	}
	return nr;
}

int Matrix::numberOfNonZeroElems() const{
	/*
	BC:Theta(1) - if the matrix is empty and all the elements are null_telem
	WC:Theta(n) - if all the elements are non zero
	AC:O(n)	 
	*/

	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (this->tripl[i].second != NULL_TELEM) {
			count++;
		}
	}
	return count;
}

MatrixIterator Matrix::iterator() const {
	return MatrixIterator(*this);
}